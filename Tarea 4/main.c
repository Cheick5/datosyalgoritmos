#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"

int main(int argc, char* argv[]) {
    
    // Se abre el archivo que es entregado por el usuario y se crean variables que utilizaremos para leer los datos del archivo.
    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    char separa[] = ",";

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
                switch (columna) {

                    // Agregar los atacantes
                }

                columna++;
                token = strtok(NULL, separa);
            }
        }
    }

    // Se cierra el archivo, puesto que, los datos presentes en el archivo ya fueron ingresados.
    fclose(fp);

    // Esta parte es para imprimir en el archivo de salida los nombres de los N mas peligrosos.

    // int contador = 0;
    //  FILE *fpout = fopen(argv[3], "w");
    //  int N = atoi(argv[2]);

    // //Para cada categoria, comenzando con la 5 (mas peligrosos).
    // for (int i = TABLE_SIZE -1 ; i >= 0; i--) { 
    //     struct node *it = tabla[i];

    //      for (int j = 0; j < largo ; j++){
        
    //     // Mientras contador sea menor a N, debemos seguir ingresando nombres al archivo de salida.
    //     if (contador < N){
        
    //       fprintf(fpout, "%s\n",);
    //       it = it->next;
    //       contador++;
    //      }

    //     // Una vez que contador es mayor que N, ya debemos dejar de ingresar nombres. 
    //     else if (contador > N){
    //          break;
    //      }
    //    }
    //  }

    // // Se cierra el archivo de salida.
    // fclose(fpout);
    
    return 0;
}