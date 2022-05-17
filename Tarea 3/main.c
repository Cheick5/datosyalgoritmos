#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define TABLE_SIZE 5

enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {

//printf("%s\n",argv[1]);

    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    int count = 0;
    char separa[] = ",";
    int categoria;
    struct node *tabla[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) {
        tabla[i] = NULL; //Inicializamos la tabla en null para evitar errores random
    }

    fgets(line, 100, fp); // ignoramos la cabecera
    printf("line = %s\n",line);
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
                    case PROBABILIDAD:
                        aux.prob_ataque = atof(token);


                        break;
                    case CATEGORIA:
                        categoria = atoi(token);
                        break;
                }

                columna++;
                token = strtok(NULL, separa);
            }
//            printf("aux nombre = %s, aux categoria = %d, aux probabilidad = %f\n",aux.nombre,categoria,aux.prob_ataque);
            insertar_encadenamiento(tabla, categoria-1, aux);
//            printf("tabla = %s\n",tabla[categoria]->x.nombre);
        }
    }
    imprimir_tabla_encadenamiento(tabla,TABLE_SIZE);
    return 0;
}