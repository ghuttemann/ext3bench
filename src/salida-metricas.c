#include "salida-metricas.h"


FILE *open_csvFile(char *filename) {
	return abrir_archivo(filename, "w");
}

void close_csvFile(FILE *fd) {
	fclose(fd);
}

void print_header(FILE *csvFile, param_t *p) {
	// Imprimimo en un archivo de salida para la posterior
	fprintf(csvFile,"# Parámetros de la Prueba\n"			);
	fprintf(csvFile,"# -----------------------\n"			);
	fprintf(csvFile,"pTB,pNJ,pSI,pAT\n"						);
	fprintf(csvFile,"%d,%s,%d,%s\n", p->pTB, p->pNJ, p->pSI, p->pAT);
	fprintf(csvFile,"# Resultados de las Pruebas \n"		);
	fprintf(csvFile,"# -------------------------\n"			);
	fprintf(csvFile,"testId,BEs,BLs,LE,LL,tCD,tBD,PF"		);
	fflush(csvFile);
	
//	// Imprimimos en salida estándar
//	printf("# Parámetros de la Prueba\n");
//	printf("# -----------------------\n");
//	printf("|Tam. Bloque | Nivel de Journal | Sync Interval | Access time |\n");
//	printf("|%12d|%18s|%15d|%13s|\n",p->pTB, p->pNJ, p->pSI, p->pAT);
//	printf("# Resultados de las Pruebas \n");
//	printf("# -------------------------\n");
//	printf("|testId    | BEs      | BLs     | LE       | LL       | tCD       | tBD       | PF-%%       | PF-min       | PF-cant       |");
}

void print_test_result(FILE *csvFile, result_t *r) {
	fprintf(csvFile,"%s,%f,%f,%f,%f,%f,%f,%f,%d\n", 
			r->testId, r->BEs, r->BLs, r->LE, r->LL, r->tCD, r->tBD, 
			r->PF.porcentaje, r->PF.cant_arch);
	
	fflush(csvFile);
	
//	printf("|%10s|%10f|%10f|%10f|%10f|%10f|%10f|%10f|%10f|%10d|\n", 
//			r->testId, r->BEs, r->BLs, r->LE, r->LL, r->tCD, r->tBD, 
//			r->PF.porcentaje, r->PF.minimo, r->PF.cant_arch);
}

param_t *verificar_filesystem(char *dev) {
	// TODO
	return NULL;
}
