/*
 ============================================================================
 Name        : ext3bench.c
 Autores 
   - Cristhian Daniel Parra
   - Fernando Mancía Zelaye
   - Germán Huttemann Arza
   - Marcelo Rodas Britez
 ============================================================================
 */

#include "primitivas.h"
#include "operaciones.h"
#include "salida-metricas.h"


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
		fprintf(stderr, "Se debe pasar el directorio de trabajo\n");
		exit(1);
	}
	
	// Configuramos el directorio de trabajo.
	sprintf(PATH, "%s%s", argv[1], verificar_barra_final(argv[1]));
	verificar_longitud_path(PATH);
	printf("En este PATH trabajaremos %s\n", PATH);
	
	// Cargamos el buffer de salida.
	cargar_buffer(OUTPUT_BUFFER, IO_BUFF_SIZE);

	// Creacion de los directorios de trabajo.
	crear_un_directorio(PATH, "mLect");
	crear_un_directorio(PATH, "mEscr");
	crear_un_directorio(PATH, "mLect2");
	crear_un_directorio(PATH, "mDirs");
	crear_un_directorio(PATH, "mFrag");

	sprintf(mLectDir,  "%s%s", PATH, "mLect/");
	sprintf(mEscrDir,  "%s%s", PATH, "mEscr/");
	sprintf(mLect2Dir, "%s%s", PATH, "mLect2/");
	sprintf(mDirsDir,  "%s%s", PATH, "mDirs/");
	sprintf(mFragDir,  "%s%s", PATH, "mFrag/");
	
	// Abrimos el archivo de salida.
	FILE *salida = open_csvFile("./salida.csv");

	//Ejecucion de las operaciones
	//MLECT ##################################################################
	mLect(1000, IO_BUFF_SIZE * 1000, "patronlect", mLectDir, salida);
	//########################################################################

	
	//MESCR ##################################################################
	mEscr(2000, 2000000, "patronescr", 5, mEscrDir, salida);
	//########################################################################

	//MLECT2 #################################################################
	// leer 2000 archivos de 2m, secuencial y aleatoriamente
	mLect2(salida,PATH, "patronlect2", 2000, 2097152);
	//########################################################################
	

	//MDIRs ##################################################################
	// crear y borrar 100.000 directorios
	mDirs(salida,PATH, 100000);
	//########################################################################
		
	
	//MFRAG ##################################################################
	frag_result result_frag[5];
	test_fragmentacion(mFragDir);
	
	// Calculamos la fragmentacion de cada directorio.
	porcentaje_fragmentacion(mLectDir,  &result_frag[1]);
	porcentaje_fragmentacion(mLect2Dir, &result_frag[2]);
	porcentaje_fragmentacion(mEscrDir,  &result_frag[3]);
	porcentaje_fragmentacion(mFragDir,  &result_frag[4]);
	
	result_frag[0].porcentaje = (result_frag[1].porcentaje +
								 result_frag[2].porcentaje +
								 result_frag[3].porcentaje +
								 result_frag[4].porcentaje) / 4;
	
	result_frag[0].minimo = min(result_frag[1].minimo, min(result_frag[2].minimo,
							min(result_frag[3].minimo, result_frag[4].minimo)));
	
	result_frag[0].cant_arch = result_frag[1].cant_arch +
							   result_frag[2].cant_arch +
							   result_frag[3].cant_arch +
							   result_frag[4].cant_arch;
	
	result_t r = {"mFrag", 0, 0, 0, 0, 0, 0, result_frag[0]};
	
	print_test_result(salida, &r);
	//########################################################################
	
	// Cerramos el archivo de salida.
	close_csvFile(salida);
	
	// Bye bye...
	return EXIT_SUCCESS;
}
