#include "mixLect2.h"
#include <math.h>

/*
 *  Leer N archivos de manera secuencial
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  cbytes: cantidad bytes del archivos
 */
void leer_N_secuencial(char *path, char *patron, int cant, int cbytes) {
	int i=0;
    char path_buff[PATH_BUFF_SIZE + 1];
    FILE *fd;
    
	// La longitud del patrón y la presencia de la barra al final
	// se verifican al inicio del benchmark
	
	for (i = 0; i < cant; ++i) {
		
		sprintf(path_buff, "%s%s-%d", path, patron, i);
		
		fd = abrir_archivo(path_buff,"r");
	    
		leer_archivo(fd,path_buff,cbytes,IO_BUFF_SIZE);
	    
	    fclose(fd);
	}
}

/*  Leer N archivos de manera aleatoria
 * 
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 *  cant  : cantidad de archivos a leer 
 *  cbytes: cantidad bytes del archivos (debe ser múliplo de IO_BUFF_SIZE)  
 */
void leer_N_aleatorio(char *path, char *patron, int cant, int cbytes) {
	int i=0;
    char path_buff[PATH_BUFF_SIZE + 1];
    FILE *fd;
    
	// La longitud del patrón y la presencia de la barra al final
	// se verifican al inicio del benchmark
	
	for (i = 0; i < cant; ++i) {
		
		sprintf(path_buff, "%s%s-%d", path, patron, i);
		
		fd = abrir_archivo(path_buff,"r");
	    
		// siempre se trunca, por lo que nunca se lee más de cbytes
		int cantidad = cbytes / IO_BUFF_SIZE;
		
		io_aleatorio(fd,path_buff,cantidad,IO_BUFF_SIZE,0);
	    
	    fclose(fd);
	}
	
}


/* lS2000A2m: Leer 2000 archivos de 2m de forma secuencial.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_secuencial(char *path, char *patron) {
	leer_N_secuencial(path,patron,2000,2097152);	
}

/*
 * lA2000A2m: Leer 2000 archivos de 2m de forma aleatoria.
 *  path  : full path del directorio donde se encuentra el archivo
 *  patron: patron de nombre de los archivos.
 */
void leer_2000_aleatorio(char *path, char *patron) {
	leer_N_aleatorio(path,patron,2000,2097152);
}


