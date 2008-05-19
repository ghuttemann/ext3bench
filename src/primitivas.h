#ifndef PRIMITIVAS_H_
#define PRIMITIVAS_H_

#endif /*PRIMITIVAS_H_*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Camino donde se guardan los archivos creados

// ToDo: --> hacer que esto sea configurable
#define PATH "/root/benchmark/cosas/"


// Tamaño del buffer en MB
#define TAM_BUFFER 5 

/**
 Función que crea "n" archivos de "cbytes"-
 Si el archivo existe trunca a 0 bytes y luego empieza a llenar hasta "cbytes".

 Para el "llenado" de archivos se redirecciona /dev/zero
**/
void crear_archivos(int n, long long cbytes, char * patron);