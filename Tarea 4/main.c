#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enemigo.h"

int main(int argc, char* argv[]) {
    
    // Se abre el archivo que es entregado por el usuario y se crean variables que utilizaremos para leer los datos del archivo.
    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    char separa[] = ",";
    int categoria;

    // Proceso para leer el archivo e ir rellenando nuestra estructura y luego la lista.
    fgets(line, 100, fp); // ignoramos la cabecera
    // segundo while para rellenar los arreglos
    while (fgets(line, 100, fp) != NULL) {

        char *token = strtok(line, separa);

        int columna = 1;
        atacante aux;

        if (token != NULL)
        {
            while(token != NULL){
                switch (columna) {}

                columna++;
                token = strtok(NULL, separa);
            }
        }
    }

    // Se cierra el archivo, puesto que, los datos presentes en el archivo ya fueron ingresados a sus correspondientes listas.
    fclose(fp);
}