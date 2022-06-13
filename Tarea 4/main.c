#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"

enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {

    struct node *root = NULL;

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

                    case NOMBRE:
                        strcpy(aux.nombre,token);

                        break;
                    case CATEGORIA:
                        aux.categoria = atoi(token);
                        break;

                    case PROBABILIDAD:
                        aux.prob_ataque = atof(token);
                        break;

                    // Agregar los atacantes
                }

                columna++;
                token = strtok(NULL, separa);
            }

            root = insert(root, aux);
        }
    }

    // Se cierra el archivo, puesto que, los datos presentes en el archivo ya fueron ingresados.
    fclose(fp);

    // Esta parte es para imprimir en el archivo de salida los nombres de los N mas peligrosos.

    // int contador = 0;
    int N = atoi(argv[2]);
    
    int Contador = 0;
    show_nodes(root);
    // printf("%d", Contador);

    // while (contador < N){
    //     show_nodes(root);
    //     contador = contador + 1;
    // }
}