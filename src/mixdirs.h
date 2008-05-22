#ifndef MIXDIRS_H_
#define MIXDIRS_H_

/*
 * Cabeceras y definiciones del conjunto de operaciones efectuadas sobre directorios. 
 * 
 */

// Crear N directorios en un path
void crear_N_directorios(char *path, int N);

// Borrar N directorios dentro de un Path
void borrar_N_directorios(char *path, int N);


// c100000D: Crear 100000 directorios en un directorio.
void crear_100mil_directorios(char *path);

// b100000Dsup: Borrar el directorio que contiene los 100000 directorios.
void borrar_100mil_directorios(char *path);


#endif /*MIXDIRS_H_*/
