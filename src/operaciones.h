

#ifndef OPERACIONES_H_
#define OPERACIONES_H_

#define MEDICION(f) {   \
   t1 = tiempo_milis(), \
   f,                   \
   t2 = tiempo_milis(), \
   t3 = t2 -t1          \
}

//OPERACIONES
/**
 * MLECT
 */
/* Funcion que crea "cant_archivos" archivos de tamaño "tamanho"
 * Luego lee y relee
 * "patron_archivos" es el patron de nombres de archivos
 * "subdir" directorio a crear
 */
void mLect(int cant_archivos, int tamanho, char * patron_archivos, char * subdir);



/**
 * MESCR
 */
/* Funcion que crea "cant_archivos" archivos de tamaño "tamanho"
 * Luego escribe aleatoriamente 
 * "patron_archivos" es el patron de nombres de archivos
 * "veces_aleatorio" cantidad de veces que se escribe
 * "subdir" directorio a crear
 */
void mEscr(int cant_archivos, int tamanho, char * patron_archivos, int veces_aleatorio, char * subdir);



/**
 * MLECT2
 */
/* Wrapper de todas las operaciones de Lectura de este grupo
 * 
 */
void mLect2(FILE output,char *path, char *patron, int cant, int cbytes);

/*  Leer N archivos de manera secuencial
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  cbytes: cantidad bytes del archivos
 */
void leer_N_secuencial(char *path, char *patron, int cant, int cbytes);

/*  Leer N archivos de manera aleatoria
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  cbytes: cantidad bytes del archivos  
 */
void leer_N_aleatorio(char *path, char *patron, int cant, int cbytes);


// OPERACIONES ESPECÍFICAS PARA ESTE BENCHMARK
/* lS2000A2m: Leer 2000 archivos de 2m de forma secuencial.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_secuencial(char *path, char *patron);

/*
 * lA2000A2m: Leer 2000 archivos de 2m de forma aleatoria.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_aleatorio(char *path, char *patron);



/**
 * MDIR
 */
void mDirs(FILE fd, char *path, int cant);

void crear_N_directorios(char *path, int N);

void borrar_N_directorios(char *path, int N);

// c100000D: Crear 100000 directorios en un directorio.
void crear_100mil_directorios(char *path);

// b100000Dsup: Borrar el directorio que contiene los 100000 directorios.
void borrar_100mil_directorios(char *path);





/**
 * MFRAG
 */

/*
 * Función que realiza las pruebas operaciones
 * que inducen a la fragmentación de los archivos.
 */
void test_fragmentacion(char *path);



#endif /*OPERACIONES_H_*/

