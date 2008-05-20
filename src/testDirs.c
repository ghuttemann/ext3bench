/* 
 * Pruebas básicas de las operaciones para crear y borrar directorios
 */

#include "primitivasdirs.h" 

int main(char *argv) {
	
	char *dirname = "testDir";
	
	// Prueba de crear un directorio.
	int result = creardirs(dirname,0777,1);

	// Prueba de crear muchos directorios.
	result = creardirs(dirname,0777,20);
	
	
	borrardirs(dirname,1);
	
    borrardirs(dirname,20);
	
	
	return result;
}