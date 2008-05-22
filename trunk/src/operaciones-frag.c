#include "operaciones.h"
#include "primitivas.h"

void test_fragmentacion(char *path) {
	char PATRON[] = "mix_frag";
	char buffer[PATH_BUFF_SIZE + 1];
	FILE *arch;
	int i, j, CBYTES=600, tam;
	
	// Crear archivos vacíos.
	crear_archivo(path, 1000, 0, 0, PATRON);
	
	// Escribir 600 bytes en cada archivo (repetir 1000 veces).
	for (j=0; j < 1000; j++) {
		for (i=0; i < 1000; i++) {
			sprintf(buffer, "%s%s-%d", path, PATRON, i);
			arch = abrir_archivo(buffer, "w");
			escribir_archivo(arch, buffer, CBYTES, CBYTES / 2);
			fclose(arch);
		}
	}
	
	// Truncar cada archivo a la mitad de su longitud
	for (i=0; i < 1000; i++) {
		sprintf(buffer, "%s%s-%d", path, PATRON, i);
		arch = abrir_archivo(buffer, "w");
		tam  = tam_archivo(arch);
		
		if (ftruncate(fileno(arch), tam/2) == -1) {
			fprintf(stderr, 
					"test_fragmentacion(): Error al truncar '%s'",
					buffer);
			perror(NULL);
			exit(1);
		}
		
		fclose(arch);
	}
	
	// Agregar 600 bytes en cada archivo (repetir 1000 veces).
	for (j=0; j < 1000; j++) {
		for (i=0; i < 1000; i++) {
			sprintf(buffer, "%s%s-%d", path, PATRON, i);
			arch = abrir_archivo(buffer, "a");
			escribir_archivo(arch, buffer, CBYTES, CBYTES / 2);
			fclose(arch);
		}
	}
}
