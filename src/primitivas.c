#include "primitivas.h"


// ToDo: El main no debe estar aquí
int main(){


	crear_archivos(5, 8000000, "megas");
	crear_archivos(10, 512, "qui");
	crear_archivos(5, 0, "cero");
	crear_archivos(8, 2048, "dosmil");
	return 0;
}


/**
 Función que crea "n" archivos de "cbytes"-
 Si el archivo existe trunca a 0 bytes y luego empieza a llenar hasta "cbytes".

 Para el "llenado" de archivos se redirecciona /dev/zero
**/
void crear_archivos(int n, long long cbytes, char * patron){
	int i=0;
	FILE * tmp;
	FILE * zero = fopen("/dev/zero","r");
	char buffer[cbytes];
	int leidos;
	for(i=0; i<n; i++){

		char * nombre = (char *)malloc(256*sizeof(char));
		strcat(nombre, PATH);
		strcat(nombre, patron);
		char var[2]; 
		sprintf(var, "%d", i);
		strcat(nombre, var);

		printf("Creando el archivo %s ...\n", nombre);
		tmp = fopen(nombre, "w");
		if(cbytes > 0){
			leidos = fread (buffer, 1, cbytes , zero);
			fwrite (buffer, 1, leidos, tmp);
		}
		fclose(tmp);
	}
}
