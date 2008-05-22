#ifndef PRIMITIVAS_H_
#define PRIMITIVAS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>


// Tamaño del buffer de E/S en bytes
#define IO_BUFF_SIZE 512

// Tamaño del buffer para path
#define PATH_BUFF_SIZE 256

/*
 * Buffer de escritura. 
 * Contiene el patrón de bytes que se escribirá 
 * en cada escritura que se realice.
 */
char OUTPUT_BUFFER[IO_BUFF_SIZE];

/*
 * Buffer de lectura. 
 * Aquí se cargarán todas las lecturas 
 * que se realicen.
 */
char INPUT_BUFFER[IO_BUFF_SIZE];

/*
 * Función que retorna el tiempo transcurrido
 * desde Epoch (ver time(2)).
 * La unidad de medida es "segundos" con
 * decimales hasta la precisión de microsegundos.
 */
double tiempo_seg();

/*
 * Función que retorna el tiempo transcurrido
 * desde Epoch (ver time(2)).
 * La unidad de medida es "milisegundos".
 */
long long tiempo_milis();

/* 
 * Función que verificamos que el path del directorio no sea 
 * muy largo.
 * Se asume que entre el patron y el numero agregado para la
 * creación archivos y directorios, no se superan los 50 
 * caracteres.
 */
void verificar_longitud_path(char *path);

/*
 * Función que se encarga de verificar la existencia
 * de una barra final en el path de un directorio,
 * Si no existe, retorna un caracter barra, en
 * caso contrario retorna el caracter vacío.
 */
char verificar_barra_final(char *path);

/*
 * Función que carga bytes en un buffer.
 */
void cargar_buffer(char *buffer, int tam);

/*
 * Función wrapper sobre la función "fopen", para el chequeo de posibles
 * errores en la apertura de archivos.
 */
FILE *abrir_archivo(char *path, char *modo);

/*
 * Función que determina el tamaño en bytes de un archivo. 
 * Se asume que el archivo está abierto al menos para escritura.
 */ 
int tam_archivo(FILE *arch);

/*
 * Función que crea "narch" archivos de "cbytes" cada uno en el directorio
 * "dir" (el cual debe existir).
 * El nombre de cada archivo creado será "patron-[1-narch]". 
 * La escritura de los archivos se realiza en bloques de "tam_bloque" bytes.
 */
void crear_archivo(char *dir, int narch, int cbytes, int tam_bloque, char *patron);

/*
 * Función que escribe secuencialmente "cbytes" por bloques de 
 * "tam_bloque" (como máximo IO_BUFF_SIZE) bytes en el archivo "arch", 
 * cuyo path se supone que está dado por "nombre" (esto es meramente 
 * para espeficar el archivo en caso de que hay un error de escritura). 
 * Se asume que "arch" fue abierto para escritura.
 */
void escribir_archivo(FILE *arch, char *nombre, int cbytes, int tam_bloque);

/*
 * Función que abre el archivo especificado por "arch", cuyo path se 
 * supone que está dado por "nombre" (esto es meramente para espeficar 
 * el archivo en caso de que hay un error de escritura), y realiza
 * la lectura del mismo de manera secuencial por bloque de "tam_bloque"
 * bytes. 
 * El parámetro "cbytes" indica hasta cuántos bytes se deberá leer del 
 * archivo. Se leerá el archivo completo si el valor para este parámetro 
 * es cero o mayor que el tamaño de archivo. Se asume que el archivo está 
 * abierto para lectura.
 */
void leer_archivo(FILE *arch, char *nombre, int cbytes, int tam_bloque);

/*
 * Función que realiza entrada/salida aleatoria sobre un determinado
 * archivo especificado por "arch", cuyo path se supone que está dado
 * por "nombre" (esto es meramente para espeficar el archivo en caso 
 * de que hay un error de escritura). 
 * La entrada/salida realizada se hace en bloques de tamaño igual a 
 * "tam_bloque" (se asume que este valor es lo suficientemente menor 
 * al tamaño del archivo como para que el acceso aleatorio se justifique;
 * además, será como máximo IO_BUFF_SIZE). 
 * Se asume que el archivo está abierto, para lectura o escritura, 
 * según sea el caso.
 * El penúltimo parámetro es un puntero a la función que realizará la 
 * operación de entrada o salida.
 * El último parámetro indica si debe realizarse una escritura, para
 * lo cual el valor debe ser distinto de cero. En caso contrario se
 * realizará una lectura.
 */
void io_aleatorio(FILE *arch, char *nombre, int cant, int tam_bloque, int escritura);

/*
 * Función que realiza la eliminación de un archivo, o de un grupo de 
 * archivos definidos por: 
 * 
 *   - *dir   : path del directorio donde se encuentran los archivos a borrar
 *   - narch  : cantidad de archivos a borrar
 *   - *patron: patron de nombramiento de los archivos
 */
void borrar_archivo(char *dir, int narch, char *patron);

/*
 * Función que realiza la creación de un directorio, o de un grupo de 
 * directorios definidos por: 
 * 
 *   - *path    : path del directorio donde se encuentran los directorios 
 *                a crear
 *   - *dirname : patrón de los nombres de directorios
 *   - cantidad : cantidad de directorios a crear
 */
void crear_directorio(char *path, char *dirname, int cantidad);

/*
 * Función que realiza la creación de un directorio, o de un grupo de 
 * directorios definidos por: 
 * 
 *   - *path    : path del directorio donde se encuentran los directorios 
 *                a borrar
 *   - *dirname : patrón de los nombres de directorios
 *   - cantidad : cantidad de directorios a crear
 */
void borrar_directorio(char *path, char *dirname, int cantidad);


#endif /*PRIMITIVAS_H_*/