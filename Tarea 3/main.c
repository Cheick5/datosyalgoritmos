#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "enemigo.h"
#include "hash.h"


#define TABLE_SIZE 5


int main(int argc, char* argv[]) {


    printf("%s\n",argv[1]);

    FILE *input = fopen(argv[1], "r");
    char line[1000]; // asumimos que cada linea tiene largo a lo mas 1000

//    atacante x ;
//    strcpy(x.nombre , "hola");
//    x.prob_ataque = 12;
//    printf("%s",x.nombre);

    int categoria;
    atacante aux;
    struct node *tabla[TABLE_SIZE];

    fgets(line, 1000, input); // ignoramos la cabecera
    // segundo while para rellenar los arreglos
    while (fgets(line, 1000, input) != NULL) {

        strcpy(aux.nombre, strtok(line, ","));

        categoria = atoi(strtok(NULL, ","));

        insertar_encadenamiento(tabla, categoria, aux);
        imprimir_tabla_encadenamiento(tabla,1000);


    }

}



