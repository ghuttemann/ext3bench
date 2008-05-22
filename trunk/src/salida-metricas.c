#include "salida-metricas.h"


FILE *open_csvFile(char *filename) {
	fopen(filename,"w");
}

void close_csvFile(FILE fd) {
	close(fd);
}

void print_header(FILE *csvFile, param_t *p) {
	
	// Imprimimo en un archivo de salida para la posterior
	fprintf(csvFile,"# Parámetros de la Prueba\n"			);
	fprintf(csvFile,"# -----------------------\n"			);
	fprintf(csvFile,"pTB,pNJ,pSI,pAT\n"						);
	fprintf(csvFile,"%d,%s,%d,%d\n",p.pTB,p.pNJ,p.pSI,p.pAT	);
	fprintf(csvFile,"# Resultados de las Pruebas \n"		);
	fprintf(csvFile,"# -------------------------\n"			);
	fprintf(csvFile,"testId,BEs,BLs,LE,LL,tCD,tBD,PF"		);
	

	// Imprimimos en salida estándar
	printf("# Parámetros de la Prueba\n"			);
	printf("# -----------------------\n"			);
	printf("|Tam. Bloque | Nivel de Journal | Sync Interval | Access time |\n"						);
	printf("|%12d|%18s|%15d|%13d|\n",p.pTB,p.pNJ,p.pSI,p.pAT	);
	printf("# Resultados de las Pruebas \n"		);
	printf("# -------------------------\n"			);
	printf("|testId    | BEs      | BLs     | LE       | LL       | tCD       | tBD       | PF       |"		);
	fflush(csvFile);
}

void print_test_result(FILE *csvFile, result_t *r) {

	fprintf(csvFile,"%s,%d,%d,%d,%d,%d,%d,%d\n", 
			r.testId, r.BEs, r.BLs, r.LE, r.LL, r.tCD, r.tBD,r.PF);
	
	printf(csvFile,"|%10s|%10d|%10d|%10d|%10d|%10d|%10d|%10d|\n", 
				r.testId, r.BEs, r.BLs, r.LE, r.LL, r.tCD, r.tBD,r.PF);
		
	
	fflush(csvFile);
}

param_t verificar_filesystem(char *dev) {
    
	// TODO
	return null;
}