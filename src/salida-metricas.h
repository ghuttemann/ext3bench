#ifndef SALIDAMETRICAS_H_
#define SALIDAMETRICAS_H_

#include "primitivas.h"

#define MAXFLDS 8 /* número máximo de campos posible */

/* 
 * Estructura donde se almacenan los resultados de una prueba
 * realizada con alguna de las operaciones definidas en 
 * operaciones.h
 */
typedef struct {
	char testId[20];/* Identificador de la prueba 			*/
	double BEs;		/* Bytes Escritos por Segundo 			*/
	double BLs;		/* Bytes Leídos por Segundo 			*/
	double LE;		/* Latencia de Escritura 				*/ 
	double LL; 		/* Latencia de Lectura	 				*/
	double tCD; 	/* Tiempo de creación de Directorios 	*/
	double tBD; 	/* Tiempo de borrado de Directorios 	*/
    frag_result PF;	/* Porcentaje de Fragmentación			*/
} result_t;


/* 
 * Estructura donde se almacenan los valores de los parámetros
 * que se tienen en cuenta para el benchmarking
 * 
 */
typedef struct {
	int pTB;	/* Tamaño de Bloques   {1024, 4096}            */
	char pNJ[25];	/* Nivel de Journaling {journal_data,
	                                        journal_data_ordered,
	                                        journal_data_writeback */
    int pSI;	/* Frecuencia de sincronización de los datos
                   y metadas al disco en segundos. 
                                 { 5s (default),
                                   8s, 
                                   10s }                            */ 
    char pAT[3]; 	/* Actualización de Acces Time {Sí o No}		*/
} param_t;

/* 
 * Operaciones para abrir y cerrar el archivo CSV de resultados 
 */
FILE *open_csvFile(char *filename);
void close_csvFile(FILE *fd);

/*
 * Imprime la cabecera del archivo de salida. 
 * 
 * Se ejecuta solo una vez. 
 */
void print_header(FILE *csvFile, param_t *r);

/* Imprime una línea de resultados en el archivo de resultados
 * 
 * Se ejecuta cada vez que se termina una operación, luego de 
 * calcular los valores de las métricas correspondientes. 
 */
void print_test_result(FILE *csvFile, result_t *p);


/* 
 * Obtiene los parámetros del filesystem montado en dev y retorna
 * los resultados en un estructura param_t
 * 
 * dev : dispositivo donde se halla el Sistema de archivos a probar. 
 */
param_t *verificar_filesystem(char *dev);

#endif /*SALIDAMETRICAS_H_*/
