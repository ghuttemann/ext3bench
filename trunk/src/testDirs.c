/* 
 * Pruebas básicas de las operaciones para crear y borrar directorios
 */

<<<<<<< .mine
#include "mixdirs.h" 
#include <stdio.h>
#include <time.h>
=======
#include "primitivas.h" 
>>>>>>> .r57

int main(int argc, char **argv) {
	
	char *dirname = "testDir";
	char *path = "/tmp/ext3bench/";
	clock_t t1,t2;
	
	// Prueba de crear un directorio.
	
	crear_directorio(path,dirname,1);

	borrar_directorio(path,dirname,1);
	
	// Prueba de crear muchos directorios.
	crear_directorio(path,dirname,20);
	
	borrar_directorio(path,dirname,20);
	
    printf("Creando 100.000 directorios...");	
	crear_100mil_directorios(path);
	
	printf("100.000 directorios creados...");
	borrar_100mil_directorios(path);
	
	
	//return result;
	return 0;
}