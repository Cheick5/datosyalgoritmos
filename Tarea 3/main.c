#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "enemigo.h"
#include "hash.h"


#define TABLE_SIZE 5



enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {


    printf("%s\n",argv[1]);



    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    int count = 0;
    char separa[] = ",";
    int categoria;
    struct node *tabla[TABLE_SIZE];

    fgets(line, 100, fp); // ignoramos la cabecera
    printf("line = %s\n",line);
    // segundo while para rellenar los arreglos
    while (fgets(line, 100, fp) != NULL) {
//        printf("entro\n");


        char *token = strtok(line, separa);

        int columna = 1;
        atacante aux;




        if (token != NULL)
        {
            while(token != NULL){
                switch (columna) {
                    case NOMBRE:
                        strcpy(aux.nombre,token);
//                        printf("NOMBRE = %s \n",aux.nombre);
                        break;
                    case PROBABILIDAD:
                        aux.prob_ataque = atof(token);
//                        printf("PROBABILIDAD = %f \n",aux.prob_ataque);

                        break;
                    case CATEGORIA:
                        categoria = atoi(token);
//                        printf("CATEGORIA = %d \n",categoria);
                        break;
                }

//                printf("token = %s--a = %d\n",token,a);
                columna++;
                token = strtok(NULL, separa);
            }
                printf("aux nombre = %s, aux categoria = %d, aux probabilidad = %f\n",aux.nombre,categoria,aux.prob_ataque);
            printf("\n");
            insertar_encadenamiento(tabla, categoria, aux);
            printf("tabla = %s\n",tabla[categoria]->x.nombre);
//            imprimir_tabla_encadenamiento(tabla,TABLE_SIZE);
        }













//        strcpy(aux.nombre, strtok(line, ","));
//        printf("aux nombre = %s\n",aux.nombre);


//        categoria = atoi(strtok(NULL, ","));
//        printf("aux categoria = %f\n",categoria);

//        insertar_encadenamiento(tabla, categoria, aux);
//        imprimir_tabla_encadenamiento(tabla,1000);


    }
    return 0;

}



