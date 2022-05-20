#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define TABLE_SIZE 5

enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {

    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    char separa[] = ",";
    int categoria;
    struct node *tabla[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) {
        tabla[i] = NULL; //Inicializamos la tabla en null para evitar errores random
    }

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
                        categoria = atoi(token);
                        break;

                    case PROBABILIDAD:

                    if (categoria == 3 && atof(token) == 0){
                        aux.prob_ataque = 0;
                    }
                    else if(categoria == 4 && atof(token) == 0){
                        aux.prob_ataque = 1;
                    }
                    else if (categoria == 5 && atof(token) == 0){
                        aux.prob_ataque = 1;
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

    fclose(fp);

    printf("\n");

    for (int i = 0; i < TABLE_SIZE; ++i) {
        //Se ordena cada una de las categorias (1-5) en base a la probabilidad.
        ordenar_lista(tabla[i]);
    }
    for (int i = 0; i < TABLE_SIZE; ++i) {

        //Se ordena cada una de las categotias (1-5) alfabeticamente (para aquellos que tienen la misma probabilidad).
        ordenar_lista_Alfabetico(tabla[i]);
    }

    //Se crea un nodo adicional (temporal) para que ese nodo sea la lista que es generada por la funcion "ordenamiento_categoria_3" y luego se asigna a tabla[2] (categoria 3) temporal.
    struct node * temporal = ordenamiento_categoria_3(tabla[2]);
    tabla[2] = temporal;

    ordenar_lista_Alfabetico(tabla[2]);

    // imprimir_tabla_encadenamiento(tabla,5); // Se imprimen todas las listas con las 5 categorias.

     int contador = 0;
     FILE *fpout = fopen(argv[3], "w");
     int N = atoi(argv[2]);

     for (int i = TABLE_SIZE-1; i >= 0; i--) { //Para cada categoria
        struct node *it = tabla[i];
        int largo = largo_hash(it);

         for (int j = 0; j <largo ; j++){ // 1: Dentro de Categoria 5, iterar el largo de

         if (contador < N){
        
          fprintf(fpout, "%s\n", it->x.nombre);
          it = it->next;
          contador++;
         }
        
         else if (contador > N){
             break;
         }
       }
     }

     fclose(fpout);

    return 0;
}