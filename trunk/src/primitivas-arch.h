#ifndef PRIMITIVAS_H_
#define PRIMITIVAS_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

#endif /*PRIMITIVAS_H_*/