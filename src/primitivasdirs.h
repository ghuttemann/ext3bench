/**
 * Archivo de cabecera de funciones básicas para operar sobre directorios
 * 
 * Se proveen las siguientes funciones: 
 * 1. Crear Directorio
 * 2. Borrar Directorio
 * 3. Crear N directorios
 * 4. Borrar N directorios
 */

#ifndef PRIMITIVASDIRS_H_
#define PRIMITIVASDIRS_H_
#endif /*OPDIRS_H_*/


#ifndef STDIO_H_
#define STDIO_H_
#endif

#ifndef STRING_H_
#define STRING_H_
#endif

#ifndef STDLIB_H_
#define STDLIB_H_
#endif

#include <sys/types.h>
#include <sys/stat.h>


/* 
 * Interfaces de funciones básicas sobre directorios. 
 */
int creardirs(const char *dirname, mode_t mode, int cantidad);
void borrardirs(const char *dirname, int cantidad);




