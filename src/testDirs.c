/* 
 * Pruebas básicas de las operaciones para crear y borrar directorios
 */

#include "primitivas-arch.h" 

int main(int argc, char **argv) {
	
	char *dirname = "testDir";
	char *path = "/tmp/";
	
	// Prueba de crear un directorio.
	
	crear_directorio(path,dirname,1);

	//borrar_directorio(path,dirname,1);
	
	// Prueba de crear muchos directorios.
	crear_directorio(path,dirname,20);
	
	//borrar_directorio(path,dirname,20);
	
	
	//return result;
	return 0;
}