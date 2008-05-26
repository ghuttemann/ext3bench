/*
 * 
 * Para Trabajar por separado, el esquema podría ser así: 
 * 
 * - Por cada operacion X, crear x.h y x.c
 * - Incluir x.h en operaciones.h
 * 
 * Obs: Para que esto funcione, se deben poner sentencias de preprocesador
 *      para evitar que nada se incluya dos veces
 * 
 *      Ej.: #ifndef PRIMITIVAS_H_
 *           #define PRIMITIVAS_H_
 */ 

#include "primitivas.h"
#include "salida-metricas.h"
#include "operaciones.h"

//OPERACIONES


/**
 * MLECT
 */
/* Funcion que crea "cant_archivos" archivos de tamaño "tamanho"
 * Luego lee y relee
 * "patron_archivos" es el patron de nombres de archivos
 * "subdir" directorio a crear
 */
void mLect(int cant_archivos, int tamanho, char * patron_archivos, char * subdir, FILE * log)
{
	char archcompleto[PATH_BUFF_SIZE + 1]; 
	int i = 0;
	long long t1,t2;
	
	//OPERACION - crear "veces" archivos
	printf("\tCreando %d arch de %d bytes. c1000A...", cant_archivos, tamanho);
	fflush(stdout);
	t1 = tiempo_milis();
	crear_archivo(subdir, cant_archivos, tamanho, IO_BUFF_SIZE, patron_archivos);
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	result_t res1 = {0};
	sprintf(res1.testId, "%s", "c1000A");
	res1.BEs = (tamanho * cant_archivos ) / ((t2 - t1)/1000.0);
	res1.LE = ((t2 - t1)/1000.0) / cant_archivos;
	print_test_result(log, &res1);


	//OPERACION  - leer los arch creados	
	printf("\tLectura de %d arch. de %d bytes. l1000A...", cant_archivos, tamanho);
	fflush(stdout);
	t1 = tiempo_milis();
	for(i=0; i<cant_archivos; i++){
		sprintf(archcompleto, "%s%s-%d",subdir, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r");
		leer_archivo(tmparch, archcompleto, tamanho, IO_BUFF_SIZE);
		fclose(tmparch);
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	result_t res2 = {0};
	sprintf(res2.testId, "%s", "l1000A");
	res2.BLs = (tamanho * cant_archivos ) / ((t2 - t1)/1000.0);
	res2.LL = ((t2 - t1)/1000.0) / cant_archivos;
	print_test_result(log, &res2);

	//OPERACION - RE-leer  los arch creados	
	printf("\tRe-lectura de %d arch. de %d bytes. rl1000A...", cant_archivos, tamanho);
	fflush(stdout);
	t1 = tiempo_milis();
	for(i=0; i<cant_archivos; i++){
		sprintf(archcompleto, "%s%s-%d",subdir, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r");
		leer_archivo(tmparch, archcompleto, tamanho, IO_BUFF_SIZE);
		fclose(tmparch);
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	result_t res3 = {0};
	sprintf(res3.testId, "%s", "rl1000A");
	res3.BLs = (tamanho * cant_archivos ) / ((t2 - t1)/1000.0);
	res3.LL = ((t2 - t1)/1000.0) / cant_archivos;
	print_test_result(log, &res3);
}

/**
 * MESCR
 */
/* Funcion que crea "cant_archivos" archivos de tamaño "tamanho"
 * Luego escribe aleatoriamente 
 * "patron_archivos" es el patron de nombres de archivos
 * "veces_aleatorio" cantidad de veces que se escribe
 * "subdir" directorio a crear
 */
void mEscr(int cant_archivos, int tamanho, char * patron_archivos, int veces_aleatorio, char * subdir, FILE * log)
{
	long long t1,t2;
	char archcompleto[PATH_BUFF_SIZE + 1]; 
	int i = 0;

	//OPERACION - crear "cant_archivos" archivos
	printf("\tCreacion de %d arch. de %d bytes. rl1000A...", cant_archivos, tamanho);
	fflush(stdout);
	t1 = tiempo_milis();
	crear_archivo(subdir, cant_archivos, tamanho, IO_BUFF_SIZE, patron_archivos);
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	result_t res1 = {0};
	sprintf(res1.testId, "%s", "c2000A2m");
	res1.BEs = (tamanho * cant_archivos ) / ((t2 - t1)/1000.0);
	res1.LE = ((t2 - t1)/1000.0) / cant_archivos;
	print_test_result(log, &res1);	

	//OPERACION - RE-escritura aleatoria de los arch creados	
	printf("\tEscritura aleatoria de %d arch. de %d bytes. rl1000A...", cant_archivos, tamanho);
	fflush(stdout);
	t1 = tiempo_milis();
	for(i=0; i<cant_archivos; i++){
		sprintf(archcompleto, "%s%s-%d",subdir, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r+");
		io_aleatorio(tmparch, archcompleto, veces_aleatorio, IO_BUFF_SIZE,1);
		fclose(tmparch);
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	result_t res2 = {0};
	sprintf(res2.testId, "%s", "re2000A2m");
	res2.BEs = (IO_BUFF_SIZE* veces_aleatorio* cant_archivos) / ((t2 - t1)/1000.0);
	res2.LE = ((t2 - t1)/1000.0) / cant_archivos;
	print_test_result(log, &res2);
}

/**
 * MLECT2
 */
void mLect2(FILE * output,char *path, char *patron, int cant, int cbytes, int tam) {

	result_t r = {0};      	/* estructura de resultados 		*/
	long long t1;
	long long t2; 
	long long t3; 	/* variables de medición de tiempo 	*/

	// Primero realizamos la prueba de Lectura Secuencial
	sprintf(r.testId,"lNSeq");
	printf("\tLectura secuencial de %d arch de %d bytes...", cant, cbytes);
	fflush(stdout);
	MEDICION ( leer_N_secuencial(path,patron,cant,tam) );
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	r.BLs = ( (tam*cant) / ( (double) t3) ) * 1000;
	r.LL =  (t3 / 1000.0) / ( (double) cant);
	print_test_result(output,&r);

	sprintf(r.testId,"lNAleat");
	printf("\tLectura aleatoria de %d arch de %d bytes...", cant, cbytes);
	fflush(stdout);
	MEDICION ( leer_N_aleatorio(path,patron,cant,cbytes) );
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	r.BLs = ( (cbytes*cant) / ( (double) t3) ) * 1000;
	r.LL = (t3 / 1000.0)/ ( (double) cant);
	print_test_result(output,&r);
}

/*
 *  Leer N archivos de manera secuencial
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  tam   : cantidad bytes de cada archivo
 */
void leer_N_secuencial(char *path, char *patron, int cant, int tam) {
	int i=0;
	char path_buff[PATH_BUFF_SIZE + 1];
	FILE *fd;

	// La longitud del patrón y la presencia de la barra al final
	// se verifican al inicio del benchmark

	for (i = 0; i < cant; ++i) {
		sprintf(path_buff, "%s%s-%d", path, patron, i);
		fd = abrir_archivo(path_buff,"r");
		leer_archivo(fd,path_buff,tam,IO_BUFF_SIZE);
		fclose(fd);
	}
}

/*  Leer N archivos de manera aleatoria
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  cbytes: cantidad bytes a leer aleatoriamente de cada archivo
 */
void leer_N_aleatorio(char *path, char *patron, int cant, int cbytes) {
	int i=0;
	char path_buff[PATH_BUFF_SIZE + 1];
	FILE *fd;

	// La longitud del patrón y la presencia de la barra al final
	// se verifican al inicio del benchmark

	for (i = 0; i < cant; ++i) {
		sprintf(path_buff, "%s%s-%d", path, patron, i);
		fd = abrir_archivo(path_buff,"r+");
		
		// siempre se trunca, por lo que nunca se lee más de cbytes
		int cantidad = cbytes / IO_BUFF_SIZE;
		io_aleatorio(fd,path_buff,cantidad,IO_BUFF_SIZE,0);
		fclose(fd);
	}
}

/* lS2000A2m: Leer 2000 archivos de 2m de forma secuencial.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_secuencial(char *path, char *patron) {
	leer_N_secuencial(path,patron,2000,2097152);	
}

/*
 * lA2000A2m: Leer 2000 archivos de 2m de forma aleatoria.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_aleatorio(char *path, char *patron) {
	leer_N_aleatorio(path,patron,2000,2097152);
}

/**
 * MDIR
 */
void mDirs(FILE * output, char *path, int cant) {
	result_t r = {0};      	/* estructura de resultados 		*/
	long long t1;
	long long t2; 
	long long t3; 	/* variables de medición de tiempo 	*/

	// Primero realizamos la prueba de Lectura Secuencial
	sprintf(r.testId,"cNDir");
	
	printf("\tCreando %d directorios...", cant);
	fflush(stdout);
	MEDICION ( crear_N_directorios(path,cant) );
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	r.tCD = ( (t3 / 1000.0) / ( (double) cant) );
	print_test_result(output,&r);

	sprintf(r.testId,"bNDir");
	printf("\tBorrando %d directorios...", cant);
	fflush(stdout);
	MEDICION ( borrar_N_directorios(path,cant) );
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	r.tCD = 0;
	r.tBD = ( (t3 / 1000.0) / ( (double) cant) );
	print_test_result(output,&r);
}

void crear_N_directorios(char *path, int N) {
	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];
    int cant = N / 4;
    
	// Se crean primero 4 subdirectorios para distribuir los directorios
	// porque cada directorio de ext3 puede tener hasta 2
	crear_directorio(path,"testDir",4);

	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		crear_directorio(path_buff,"test",cant);
	}
}

void borrar_N_directorios(char *path, int N) {
	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];
	int cant = N/4;

	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		borrar_directorio(path_buff,"test",cant);
	}

	borrar_directorio(path,"testDir",4);	
}


// c10000D: Crear 100000 directorios bajo un directorio.
void crear_100mil_directorios(char *path) {
	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];

	// Se crean primero 4 subdirectorios para distribuir los directorios
	// porque cada directorio de ext3 puede tener hasta 2
	crear_directorio(path,"testDir",4);

	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		crear_directorio(path_buff,"test",25000);
	}
}

// b10000Dsup: Borrar el directorio que contiene los 10000 directorios.
void borrar_100mil_directorios(char *path) {
	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];

	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		borrar_directorio(path_buff,"test",25000);
	}

	borrar_directorio(path,"testDir",4);
}

/**
 * MFRAG
 */
void test_fragmentacion(char *path) {
	char PATRON[] = "mix_frag";
	char buffer[PATH_BUFF_SIZE + 1];
	FILE *arch;
	int i, j, CBYTES=600, tam;
	long long t1, t2, t3;

	// Crear archivos vacíos.
	printf("\tCreando 1000 archivos vacios...");
	fflush(stdout);
	t1 = tiempo_milis();
	crear_archivo(path, 1000, 0, 0, PATRON);
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	printf("\tEscribiendo 600 bytes en cada archivo (repetir 1000 veces)...");
	fflush(stdout);
	t1 = tiempo_milis();
	// Escribir 600 bytes en cada archivo (repetir 1000 veces).
	for (j=0; j < 1000; j++) {
		for (i=0; i < 1000; i++) {
			sprintf(buffer, "%s%s-%d", path, PATRON, i);
			arch = abrir_archivo(buffer, "w");
			escribir_archivo(arch, buffer, CBYTES, CBYTES / 2);
			fclose(arch);
		}
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	printf("\tTruncando cada archivo a la mitad de su longitud...");
	fflush(stdout);
	t1 = tiempo_milis();
	// Truncar cada archivo a la mitad de su longitud
	for (i=0; i < 1000; i++) {
		sprintf(buffer, "%s%s-%d", path, PATRON, i);
		arch = abrir_archivo(buffer, "w");
		tam  = tam_archivo(arch);

		if (ftruncate(fileno(arch), tam/2) == -1) {
			fprintf(stderr, 
					"test_fragmentacion(): Error al truncar '%s'",
					buffer);
			perror("sys_msg");
			exit(1);
		}

		fclose(arch);
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);

	printf("\tAgregando 600 bytes en cada archivo (repetir 1000 veces)...");
	fflush(stdout);
	t1 = tiempo_milis();
	// Agregar 600 bytes en cada archivo (repetir 1000 veces).
	for (j=0; j < 1000; j++) {
		for (i=0; i < 1000; i++) {
			sprintf(buffer, "%s%s-%d", path, PATRON, i);
			arch = abrir_archivo(buffer, "a");
			escribir_archivo(arch, buffer, CBYTES, CBYTES / 2);
			fclose(arch);
		}
	}
	t2 = tiempo_milis();
	printf("%lld ms.\n", t2 - t1);
	fflush(stdout);
}
