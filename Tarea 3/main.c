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
                    case CATEGORIA:
                        categoria = atoi(token);
                        break;

                    case PROBABILIDAD:

                    if(categoria == 4 || categoria == 5 ){
                        if(atof(token) == 0) {
                            aux.prob_ataque = 1;
                        }
                    }
                    else{
                        aux.prob_ataque = atof(token);
                    }
                        break;
                }

                columna++;
                token = strtok(NULL, separa);
            }

            insertar_encadenamiento(tabla, categoria-1, aux);

        }
    }
    imprimir_tabla_encadenamiento(tabla,TABLE_SIZE);



    printf("\n");

    ordenar_lista(tabla[0]);
    ordenar_lista(tabla[1]);
    ordenar_lista(tabla[2]);
    ordenar_lista(tabla[3]);
    ordenar_lista(tabla[4]);
    imprimir_tabla_encadenamiento(tabla,TABLE_SIZE);



    return 0;
}