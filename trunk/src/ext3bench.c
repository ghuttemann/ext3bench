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
#include "operaciones.h"


//directorio donde se crean los archivos
char PATH[PATH_BUFF_SIZE + 1];

//sub-directorios de trabajo
char mLectDir[PATH_BUFF_SIZE + 1];
char mEscrDir[PATH_BUFF_SIZE + 1];
char mLect2Dir[PATH_BUFF_SIZE + 1];
char mDirsDir[PATH_BUFF_SIZE + 1];
char mFragDir[PATH_BUFF_SIZE + 1];

int main(int argc, char **argv){
	if(argc != 2){
		printf("Se debe pasar el directorio de trabajo\n");
		return 1;
	}

	sprintf(PATH, "%s%s", argv[1], verificar_barra_final(argv[1]));	
	printf("En este PATH trabajaremos %s\n", PATH);

	//creacion de los directorios de trabajo
	crear_un_directorio(PATH, "mLect");
	crear_un_directorio(PATH, "mEscr");
	crear_un_directorio(PATH, "mLect2");
	crear_un_directorio(PATH, "mDirs");
	crear_un_directorio(PATH, "mFrag");

	sprintf(mLectDir, "%s%s", PATH, "mLect");
	sprintf(mEscrDir, "%s%s", PATH, "mEscr");
	sprintf(mLect2Dir, "%s%s", PATH, "mLect2");
	sprintf(mDirsDir, "%s%s", PATH, "mDirs");
	sprintf(mFragDir, "%s%s", PATH, "mFrag");

	//ejecucion de las operaciones
	mLect(1000, IO_BUFF_SIZE * 1000, "patronlect", mLectDir);

	return 0; 
}
