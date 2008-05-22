#ifndef SALIDAMETRICAS_H_
#define SALIDAMETRICAS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFLDS 8 /* número máximo de campos posible */

/* 
 * Estructura donde se almacenan los resultados de una prueba
 * realizada con alguna de las operaciones definidas en 
 * operaciones.h
 */
typedef struct {
	char *testId;	/* Identificador de la prueba 			*/
	long long BEs;	/* Bytes Escritos por Segundo 			*/
	long long BLs;	/* Bytes Leídos por Segundo 			*/
    long long LE;	/* Latencia de Escritura 				*/ 
    long long LL; 	/* Latencia de Lectura	 				*/
    long long tCD; 	/* Tiempo de creación de Directorios 	*/
    long long tBD; 	/* Tiempo de borrado de Directorios 	*/
    double PF;		/* Porcentaje de Fragmentación			*/
	
} result_t;


/* 
 * Estructura donde se almacenan los valores de los parámetros
 * que se tienen en cuenta para el benchmarking
 * 
 */
typedef struct {
	long long pTB;	/* Tamaño de Bloques   {1024, 4096}            */
	long long pNJ;	/* Nivel de Journaling {journal_data,
	                                        journal_data_ordered,
	                                        journal_data_writeback */
    long long pSI;	/* Frecuencia de sincronización de los datos
                       y metadas al disco en segundos. 
                                 { 5s (default),
                                   8s, 
                                   10s }                            */ 
    long long pAT; 	/* Actualización de Acces Time {Sí o No}		*/
} param_t;

/* 
 * Operaciones para abrir y cerrar el archivo CSV de resultados 
 */
FILE *open_csvFile(char *filename);
void close_csvFile(char *filename);

/*
 * Imprime la cabecera del archivo de salida. 
 * Se le llama solo una vez. 
 */
void print_header(FILE *csvFile, result_t *r);

/* Imprime una línea de resultados en el archivo de resultados
 * Se ejecuta cada vez que se termina una operación, luego de 
 * calcular los valores de las métricas correspondientes. 
 */
void print_test_result(FILE *csvFile, param_t *p);

#endif /*SALIDAMETRICAS_H_*/
