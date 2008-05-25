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
char mDirsDir[PATH_BUFF_SIZE + 1];
char mFragDir[PATH_BUFF_SIZE + 1];

int main(int argc, char **argv){
	long long t1, t2;
	
	if(argc != 2){
		fprintf(stderr, "Se debe pasar el directorio de trabajo\n");
		exit(1);
	}
	
	// Configuramos el directorio de trabajo.
	sprintf(PATH, "%s%s", argv[1], verificar_barra_final(argv[1]));
	verificar_longitud_path(PATH);
	
	// Cargamos el buffer de salida.
	cargar_buffer(OUTPUT_BUFFER, IO_BUFF_SIZE);

	// Creacion de los directorios de trabajo.
	crear_un_directorio(PATH, "mLect");
	crear_un_directorio(PATH, "mEscr");
	crear_un_directorio(PATH, "mDirs");
	crear_un_directorio(PATH, "mFrag");

	sprintf(mLectDir,  "%s%s", PATH, "mLect/");
	sprintf(mEscrDir,  "%s%s", PATH, "mEscr/");
	sprintf(mDirsDir,  "%s%s", PATH, "mDirs/");
	sprintf(mFragDir,  "%s%s", PATH, "mFrag/");
	
	printf("Directorio de trabajo configurando en '%s'...\n", PATH);
	
	// Abrimos el archivo de salida.
	FILE *salida = open_csvFile("./salida.csv");
	fprintf(salida,"testId,BEs,BLs,LE,LL,tCD,tBD,PF-%,PF-min,PF-cant\n");
	
	t1 = tiempo_milis();

	//Ejecucion de las operaciones
	//MLECT ##################################################################
	printf("Operaciones de Lectura/Re-lectura Secuencial...\n");
	fflush(stdout);
	mLect(1000, IO_BUFF_SIZE * 1000, "patronlect", mLectDir, salida);
	//########################################################################

	
	//MESCR ##################################################################
	printf("Operaciones de Escritura Secuencial/Aleatoria...\n");
	fflush(stdout);
	mEscr(500, 2000000, "patronescr", 10, mEscrDir, salida);
	//########################################################################

	//MLECT2 #################################################################
	// leer 2000 archivos de 2m, secuencial y aleatoriamente
	printf("Operaciones de Lectura Secuencial/Aleatoria...\n");
	fflush(stdout);
	mLect2(salida, mEscrDir, "patronescr", 500, 5120);
	//########################################################################
	

	//MDIRs ##################################################################
	// crear y borrar 100.000 directorios
	printf("Operaciones de Creacion/Borrado de Directorios...\n");
	fflush(stdout);
	mDirs(salida, mDirsDir, 50000);
	//########################################################################
		
	
	//MFRAG ##################################################################
	printf("Operaciones de Fragmentacion...\n");
	fflush(stdout);
	frag_result result_frag;
	test_fragmentacion(mFragDir);
	
	// Calculamos la fragmentacion de cada directorio.
	porcentaje_fragmentacion(mFragDir,  &result_frag);
	
	result_t r = {"mFrag", 0, 0, 0, 0, 0, 0, result_frag};
	
	print_test_result(salida, &r);
	//########################################################################
	
	t2 = tiempo_milis();
	
	// Imprimimos el tiempo total
	printf("Fin del test... %lld ms.\n", t2 - t1);
	
	// Cerramos el archivo de salida.
	close_csvFile(salida);
	
	// Bye bye...
	return EXIT_SUCCESS;
}
