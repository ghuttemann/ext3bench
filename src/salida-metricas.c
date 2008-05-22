#include "salida-metricas.h"


File *open_csvFile(char *filename) {
	fopen(filename,"w");
}

void close_csvFile(char *filename) {
	close(filename);
}

void print_header(FILE *csvFile, param_t *p) {
	
	// "4096,has_journal,5000,si"
	fprintf(csvFile,"# Parámetros de la Prueba\n"			);
	fprintf(csvFile,"# -----------------------\n"			);
	fprintf(csvFile,"pTB,pNJ,pSI,pAT\n"						);
	fprintf(csvFile,"%d,%s,%d,%d\n",p.pTB,p.pNJ,p.pSI,p.pAT	);
	fprintf(csvFile,"# Resultados de las Pruebas \n"		);
	fprintf(csvFile,"# -------------------------\n"			);
	fprintf(csvFile,"testId,BEs,BLs,LE,LL,tCD,tBD,PF"		);
	
	fflush(csvFile);
}

void print_header(FILE *csvFile, result_t *r) {

	fprintf(csvFile,"%s,%d,%d,%d,%d,%d,%d,%d,%d\n", 
			r.testId, r.BEs, r.BLs, r.LE, r.LL, r.tCD, r.tBD,r.PF);
	
	fflush(csvFile);
}