#include "primitivas.h"

struct timeval obtener_tiempo() {
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1) {
		fprintf(stderr, "medir_tiempo(): Error al obtener el tiempo\n");
		perror("sys_msg");
		exit(1);
	}
	
	return tv;
}

double tiempo_seg() {
	double seg, mseg;
	struct timeval tv = obtener_tiempo();
	
	seg = tv.tv_sec;
	mseg += (tv.tv_usec / 1000000.0);
	
	return (seg + mseg);
}

long long tiempo_milis() {
	long long seg, mseg;
	struct timeval tv = obtener_tiempo();
	
	// Guardamos los tiempos en long long int
	seg  = tv.tv_sec;
	mseg = tv.tv_usec;
	
	// Convertimos los tiempos en milisegundos
	seg  = seg * 1000;
	mseg = mseg / 1000;
	
	// Retornamos el resultado
	return (seg + mseg);
}

void verificar_longitud_path(char *path) {
	int maxlen = strlen(path);
	
	if (maxlen > PATH_BUFF_SIZE) {
		fprintf(stderr, "Path '%s' demasiado largo (%d, max=%d)",
				path, strlen(path), 200);
		exit(1);
	}
}

char *verificar_barra_final(char *path) {
	int len = strlen(path);
	
	if (path[len - 1] == '/')
		return "";
	
	return "/";
}

void cargar_buffer(char *buffer, int tam) {
	int i;
	
	// Se carga el valor 65, caracter A
	for (i=0; i < tam; i++)
		buffer[i] = 65;
}

FILE *abrir_archivo(char *path, char *modo) {
	FILE *arch;
	
	if ((arch = fopen(path, modo)) == NULL) {
		fprintf(stderr, 
				"abrir_archivo(): Error abriendo archivo '%s' en modo '%s'\n", 
				path, modo);
		perror("sys_msg");
		exit(1);
	}
	
	return arch;
}

int tam_archivo(FILE *arch) {
	struct stat datos;
	int filedes = fileno(arch);
	
	if (fstat(filedes, &datos) == -1) {
		fprintf(stderr, "tam_archivo(): Error obteniendo tamaño de archivo\n");
		perror("sys_msg");
		exit(1);
	}
	
	return ((int) datos.st_size);
}

void crear_archivo(char *dir, int narch, int cbytes, int tam_bloque, char *patron) {
	int i=0;
	char path_buff[PATH_BUFF_SIZE + 1];
	FILE *tmp;
	
	/*
	 * Creamos la cantidad de archivos especificados.
	 * Adicionalmente, si "cbytes" es mayor a cero, 
	 * escribimos dicha cantidad de bytes al archivo
	 * antes de cerrarlo.
	 */
	for (i=0; i < narch; i++) {
		sprintf(path_buff, "%s%s-%d", dir, patron, i);
		
		tmp = abrir_archivo(path_buff, "w");
		
		if (cbytes > 0)
			escribir_archivo(tmp, path_buff, cbytes, tam_bloque);
		
		fclose(tmp);
	}
}

void escribir_archivo(FILE *arch, char *nombre, int cbytes, int tam_bloque) {
	int bytes_total  = 0;
	int bytes_actual = 0;
	int filedes = fileno(arch);
	
	/*
	 * El tamaño de bloque no puede
	 * ser mayor a IO_BUFF_SIZE
	 */
	if (tam_bloque > IO_BUFF_SIZE)
		tam_bloque = IO_BUFF_SIZE;
	
	while (bytes_total < cbytes) {
		bytes_actual = write(filedes, OUTPUT_BUFFER, tam_bloque);
		bytes_total += bytes_actual;
		
		/*
		 * Verificamos si hubo algún error en la escritura
		 * realizada. Si así fue, terminamos. En caso contrario,
		 * continuamos con la escritura.
		 */
		if (bytes_actual == -1) {
			fprintf(stderr, 
					"escribir_archivo(): Error en escritura del archivo '%s'\n",
					nombre);
			perror("sys_msg");
			exit(1);
		}
	}
}

void leer_archivo(FILE *arch, char *nombre, int cbytes, int tam_bloque) {
	int bytes_actual = 1;
	int bytes_total  = 0;
	int filedes = fileno(arch);
	
	/*
	 * El tamaño de bloque no puede
	 * ser mayor a IO_BUFF_SIZE
	 */
	if (tam_bloque > IO_BUFF_SIZE)
		tam_bloque = IO_BUFF_SIZE;
	
	/*
	 * No tiene sentido que "cbytes" sea
	 * mayor al tamaño de archivo.
	 */
	int tam_arch = tam_archivo(arch);
	if (cbytes > tam_arch || cbytes <= 0)
		cbytes = tam_arch;
	
	/*
	 * Leemos hasta el final del archivo en el caso más
	 * general. Si "cbytes" es menor que el tamaño de
	 * archivo, se leen solo dicha cantidad. También
	 * debemos comprobar que la cantidad de bytes leídos
	 * cada vez sea positivo (de lo contrario significa
	 * fin-de-archivo).
	 */
	while (bytes_total < cbytes && bytes_actual > 0) {
		bytes_actual = read(filedes, INPUT_BUFFER, tam_bloque);
		bytes_total += bytes_actual;
		
		if (bytes_actual == -1) {
			fprintf(stderr, "leer_archivo(): Error leyendo el archivo '%s'\n", nombre);
			perror("sys_msg");
			exit(1);
		}
	}
}

void io_aleatorio(FILE *arch, char *nombre, int cant, int tam_bloque, int escritura) {
	int tam_arch, max_offset, i, pos, res;
	int filedes = fileno(arch);
	char *buffer = NULL;
	char operacion[10];
	
	/*
	 * El tamaño de bloque no puede
	 * ser mayor a IO_BUFF_SIZE
	 */
	if (tam_bloque > IO_BUFF_SIZE)
		tam_bloque = IO_BUFF_SIZE;
	
	/*
	 * Calcular máxima posición desde
	 * la cual se puede leer, considerando
	 * el tamaño de bloque y el tamaño
	 * del archivo.
	 */
	tam_arch   = tam_archivo(arch);
	max_offset = tam_arch - tam_bloque;
	
	/*
	 * Seleccionamos la función de E/S
	 * y el buffer, según la operación
	 * sea de lectura o escritura.
	 */
	if (escritura) {
		sprintf(operacion, "escritura");
		buffer  = OUTPUT_BUFFER;
	}
	else {
		sprintf(operacion, "lectura");
		buffer  = INPUT_BUFFER;
	}
	
	/*
	 * Generamos los accesos aleatorios.
	 */
	for (i=0; i < cant; i++) {
		
		// Calculamos posición aleatoria
		pos = (int) (max_offset * (rand() / (RAND_MAX + 1.0)));
		
		// Nos movemos a dicha posición
		fseek(arch, pos, SEEK_SET);
		
		// Realizamos la operación de E/S
		if (escritura) {
			res = write(filedes, buffer, tam_bloque);
		}
		else {
			res = read(filedes, buffer, tam_bloque);
		}
		
		// Verificamos error
		if (res == -1) {
			fprintf(stderr, "io_aleatorio(): Error de %s en archivo '%s'\n",
					operacion, nombre);
			perror("sys_msg");
			exit(1);
		}
	}
}


void borrar_archivo(char *dir, int narch, char *patron) {
    int i=0;
	char path_buff[PATH_BUFF_SIZE + 1];
	int tmp;
	
	/*
	 * Borramos la cantidad de archivos especificados.
	 * 
	 */
	for (i=0; i < narch; i++) {
		sprintf(path_buff, "%s%s-%d", dir, patron, i);
		
		tmp = remove(path_buff);
		
		if (tmp == -1) {
			fprintf(stderr, "borrar_archivo(): Error en borrado de archivo '%s'\n",
					path_buff);
			perror("sys_msg");
			exit(1);
		}
	}
}

void crear_directorio(char *path, char *dirname, int cantidad) {
	char path_buff[PATH_BUFF_SIZE + 1];
	int i;
	
	for (i = 0; i < cantidad; ++i) {
		sprintf(path_buff, "%s%s-%d", path, dirname, i);
									
		int result = mkdir(path_buff, 0777);
		// Verificamos error
		if (result == -1) {
			fprintf(stderr, "crear_directorio(): Error al crear directorio '%s'\n",
					 dirname);
			perror("sys_msg");
			exit(1);
		}
	}
}

void crear_un_directorio(char *path, char *dirname) {
	char path_buff[PATH_BUFF_SIZE + 1];
	
	sprintf(path_buff, "%s%s", path, dirname);
	
	int result = mkdir(path_buff, 0777);
	// Verificamos error
	if (result == -1) {
		fprintf(stderr, "crear_directorio(): Error al crear directorio '%s'\n",
				 dirname);
		perror("sys_msg");
		exit(1);
	}

}

void borrar_directorio(char *path, char *dirname, int cantidad) {
	char path_buff[PATH_BUFF_SIZE + 1];
	int i;
		
	for (i = 0; i < cantidad; ++i) {
		sprintf(path_buff, "%s%s-%d", path, dirname, i);
								
		int result = rmdir(path_buff);
		// Verificamos error
		if (result == -1) {
			fprintf(stderr, "crear_directorio(): Error al crear directorio '%s'\n",
					 dirname);
			perror("sys_msg");
			exit(1);
		}
	}
}

void porcentaje_fragmentacion(char *path, frag_result *resultado) {
	char buffer[PATH_BUFF_SIZE + 1];
	DIR *directorio;
	struct dirent *entrada;
	struct stat info;
	int cant_archivos = 0;
	double porcentaje = 0;
	double division;
	double minimo = 2;
	
	if ((directorio = opendir(path)) == NULL) {
		fprintf(stderr, "Error al abrir directorio '%s'\n", path);
		perror("sys_msg");
		exit(1);
	}
	
	while (entrada = readdir(directorio), entrada != NULL) {
		sprintf(buffer, "%s%s", path, entrada->d_name);
		
		if (stat(buffer, &info) == -1) {
			fprintf(stderr, "Error al obtener informacion de '%s'\n", buffer);
			perror("sys_msg");
			exit(1);
		}
		
		if (S_ISREG(info.st_mode)) {
			++cant_archivos;
			division = info.st_size / ((double) (info.st_blocks * 512));
			
			if (division < minimo)
				minimo = division;
			
			porcentaje += division;
		}
	}
	
	if (errno == EBADF) {
		fprintf(stderr, "Error al leer directorio '%s'\n", path);
		perror("sys_msg");
		exit(1);
	}
	
	closedir(directorio);
	
	resultado->porcentaje = (porcentaje / cant_archivos) * 100;
	resultado->minimo     = minimo * 100;
	resultado->cant_arch  = cant_archivos;
}
