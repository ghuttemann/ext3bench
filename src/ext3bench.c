/*
 ============================================================================
 Name        : ext3bench.c
 Author      : Cristhian Daniel Parra
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style                   b6z4q9r3
 ============================================================================
 */
#include "primitivas.h"

/* 
 * ToDo
 * ====
 * 
 * Cuerpo principal de las pruebas. Debe incluir: 
 *    - primitivas.h
 *    - operaciones.h
 * 
 * Luego se deben ejecutar las operaciones y sacar las estadísticas, algunas 
 * de ellas en la implementación de las operaciones: 
 * 
 */


#include "primitivas-arch.h"


//directorio donde se crean los archivos
char dirarchivos[PATH_BUFF_SIZE + 1]; 
void grupouno(int veces, int tamanho, char * patron_archivos);
void grupodos(int cant_archivos, int tamanho, char * patron_archivos, int veces_aleatorio);


int main(int argc, char **argv){

	char * subdir = "op-uno";  //subdirectorio de trabajo
	char dir[PATH_BUFF_SIZE + 1]; //directorio padre	


	//Creacion de los nombres de directorio
	sprintf(dir, "%s", argv[1] );
	sprintf(dirarchivos, "%s%s-0/", argv[1], subdir );
	crear_directorio(dir, subdir, 1);


	grupouno(10, IO_BUFF_SIZE*1000, "grupo-uno");
	grupodos(20, 2097152, "grupo-dos", 4);

	return 0; 
}



void grupouno(int veces, int tamanho, char * patron_archivos)
{
	char archcompleto[PATH_BUFF_SIZE + 1]; 
	int i = 0;

	//OPERACION - crear "veces" archivos
	crear_archivo(dirarchivos, veces, tamanho, IO_BUFF_SIZE, patron_archivos);
	

	//OPERACION  - leer los arch creados	
	for(i=0; i<veces; i++){

		sprintf(archcompleto, "%s%s-%d",dirarchivos, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r");
		leer_archivo(tmparch, archcompleto, tamanho, IO_BUFF_SIZE);
		fclose(tmparch);
	}

	//OPERACION - RE-leer  los arch creados	
	for(i=0; i<veces; i++){

		sprintf(archcompleto, "%s%s-%d",dirarchivos, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r");
		leer_archivo(tmparch, archcompleto, tamanho, IO_BUFF_SIZE);
		fclose(tmparch);
	}
}


void grupodos(int cant_archivos, int tamanho, char * patron_archivos, int veces_aleatorio)
{
	char archcompleto[PATH_BUFF_SIZE + 1]; 
	int i = 0;

	//OPERACION - crear "cant_archivos" archivos
	crear_archivo(dirarchivos, cant_archivos, tamanho, IO_BUFF_SIZE, patron_archivos);
	

	//OPERACION - RE-escritura aleatoria de los arch creados	
	for(i=0; i<cant_archivos; i++){

		sprintf(archcompleto, "%s%s-%d",dirarchivos, patron_archivos, i );
		FILE *tmparch = abrir_archivo(archcompleto, "r+");
		io_aleatorio(tmparch, archcompleto, veces_aleatorio, IO_BUFF_SIZE,1);
		fclose(tmparch);

	}
}
