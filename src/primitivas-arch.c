#include "primitivas-arch.h"

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
		perror(NULL);
		exit(1);
	}
	
	return arch;
}

int tam_archivo(FILE *arch) {
	struct stat datos;
	int filedes = fileno(arch);
	
	if (fstat(filedes, &datos) == -1) {
		fprintf(stderr, "Error obteniendo tamaño de archivo\n");
		perror(NULL);
		exit(1);
	}
	
	return ((int) datos.st_size);
}

void crear_archivo(char *dir, int narch, int cbytes, int tam_bloque, char *patron) {
	int i=0;
	char path_buff[PATH_BUFF_SIZE + 1];
	FILE *tmp;
	
	/*
	 * Verificamos que el path del directorio no sea muy largo.
	 * Se asume que entre el patron y el numero agregado, no se
	 * superan los 50 caracteres.
	 */
	int maxlen = strlen(dir) + strlen(patron) + 15;
	if (maxlen > PATH_BUFF_SIZE) {
		fprintf(stderr, "Path '%s' demasiado largo (%d, max=%d)",
				dir, strlen(dir), 200);
		exit(1);
	}
	
	/*
	 * Creamos la cantidad de archivos especificados.
	 * Adicionalmente, si "cbytes" es mayor a cero, 
	 * escribimos dicha cantidad de bytes al archivo
	 * antes de cerrarlo.
	 */
	for (i=0; i < narch; i++) {
		sprintf(path_buff, "%s-%d", patron, i);
		
		printf("Creando el archivo '%s'...\n", path_buff);
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
			perror(NULL);
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
			fprintf(stderr, "Error leyendo el archivo '%s'\n", nombre);
			perror(NULL);
			exit(1);
		}
	}
}

void io_aleatorio(FILE *arch, char *nombre, int cant, int tam_bloque, int escritura) {
	int tam_arch, max_offset, i, pos, res;
	int filedes = fileno(arch);
	char *buffer = NULL;
	
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
		#define IO_FUNC write
		#define IO_OPER "escritura"
		
		buffer  = OUTPUT_BUFFER;
	}
	else {
		#ifndef IO_FUNC
			#define IO_FUNC read
		#endif
		
		#ifndef IO_OPER
			#define IO_OPER "lectura"
		#endif
		
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
		res = IO_FUNC(filedes, buffer, tam_bloque);
		
		// Verificamos error
		if (res == -1) {
			fprintf(stderr, "io_aleatorio(): Error de %s en archivo '%s'\n",
					IO_OPER, nombre);
			perror(NULL);
			exit(1);
		}
	}
}
