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



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PATH_BUFF_SIZE 256

/* 
 * Interfaces de funciones básicas sobre directorios. 
 */
int creardirs(char *dirname, mode_t mode, int cantidad);
void borrardirs(char *dirname, int cantidad);




