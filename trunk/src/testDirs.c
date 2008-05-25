/* 
 * Pruebas básicas de las operaciones para crear y borrar directorios
 */
#include <stdio.h>
#include <time.h>
#include "primitivas.h" 
#include "operaciones.h"

int main_(int argc, char **argv) {
	char *dirname = "testDir";
	char *path = "/tmp/ext3bench/";
	
	// Prueba de crear un directorio.
	
	crear_directorio(path,dirname,1);

	borrar_directorio(path,dirname,1);
	
	// Prueba de crear muchos directorios.
	crear_directorio(path,dirname,20);
	
	borrar_directorio(path,dirname,20);
	
    printf("Creando 100.000 directorios...\n");
    long long t1 = tiempo_milis();
	crear_N_directorios(path,100000);	
	long long t2 = tiempo_milis();	
	long long t3 = t2 - t1;
	printf("--- Tiempo de creación de directorios: %lld\n",t3/100000);
	
	printf("100.000 directorios creados...");
	t1 = tiempo_milis();
	borrar_N_directorios(path,100000);
	t2 = tiempo_milis();
	t3 = t2 - t1;
	printf("--- Tiempo de borrado de directorios: %lld\n",t3/100000);
	
	//return result;
	return 0;
}

