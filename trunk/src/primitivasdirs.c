/*
 * Implementación de las primitivas par la manipulación básica de directorios
 */

#include "primitivasdirs.h"


int creardirs(const char *dirname, mode_t mode, int cantidad) {
	
	char *name = dirname;
	int result; 
	
	if (cantidad > 1) {
		int i;
		
		for (i = 0; i < cantidad; ++i) {
			
			char *sufix = (char *) i;
			
			strcat(name, sufix);			
			result = result + mkdir(name,mode);			
		}		
	} else {
		result = mkdir(dirname,mode);
	}
	return result;
}


void borrardirs(const char *dirname, int cantidad){
	char *name = dirname;
	int result; 
	
	if (cantidad > 1) {
		int i;
		
		for (i = 0; i < cantidad; ++i) {
			
			char *sufix = (char *) i;
			
			strcat(name, sufix);			
			result = rmdir(name);			
		}		
	} else {
		result = rmdir(name);
	}
	
	return result;
}

