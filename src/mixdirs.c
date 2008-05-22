#include "mixdirs.h"
#include "primitivas.h"

void crear_N_directorios(char *path, int N) {
	
}

void borrar_N_directorios(char *path, int N) {
	
}


// c10000D: Crear 100000 directorios bajo un directorio.
void crear_100mil_directorios(char *path) {

	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];

	// Se crean primero 4 subdirectorios para distribuir los directorios
	// porque cada directorio de ext3 puede tener hasta 2
	crear_directorio(path,"testDir",4);
	
	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		crear_directorio(path_buff,"test",25000);
	}
	
}

// b10000Dsup: Borrar el directorio que contiene los 10000 directorios.
void borrar_100mil_directorios(char *path) {

	int var = 0;
	char path_buff[PATH_BUFF_SIZE + 1];
	
	for (var = 0; var < 4; ++var) {	
		// En cada subdirectorio, se crean 25000 directorios. 
		sprintf(path_buff, "%s%s-%d/", path, "testDir", var);		
		borrar_directorio(path_buff,"test",25000);
	}
	
	borrar_directorio(path,"testDir",4);	
	
}