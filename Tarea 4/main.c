#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"

enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {

    // Se crea la raiz apuntando a NULL
    struct node *root = NULL;

    // Se define N como la cantidad de enemigos entregada por el usuario
    int N = atoi(argv[2]);

    // Se abre el archivo que es entregado por el usuario y se crean variables que utilizaremos para leer los datos del archivo
    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    char separa[] = ",";

    // Proceso para leer el archivo e ir rellenando nuestro arbol
    fgets(line, 100, fp); // ignoramos la cabecera
    // segundo while para rellenar el arbol
    while (fgets(line, 100, fp) != NULL) {

        // Se define un puntero "token" que sera utilizado para ir leyendo el archivo
        char *token = strtok(line, separa);

        // Se define la variable "columna" y se inicializa en 1
        int columna = 1;

        // Se crea un puntero "aux" que hace referencia a la estructura de los enemigos (atacante)
        atacante aux;

        // Mientras el token no sea NULL se realizara el proceso de guardado de informacion en el arbol
        if (token != NULL){
            
            // Utilizando un ciclo while, mientras el token sea distinto de NULL, utilizaremos un switch (existen tres casos, nombre, peligrosidad y probabilidad)
            while(token != NULL){

                // Se utilizara un switch para ir rellenando el arbol
                switch (columna) {
                    
                    // Caso en el cual se guarda el nombre del enemigo
                    case NOMBRE:
                        strcpy(aux.nombre,token);
                        break;
                    
                    // Caso en el cual se guarda la categoria del enemigo
                    case CATEGORIA:
                        aux.categoria = atoi(token);
                        break;

                    // Caso en el cual se guarda la probabilidad del enemigo
                    case PROBABILIDAD:
                        aux.prob_ataque = atof(token);
                        break;
                }

                // Se actualizan los iteradores
                columna++;
                token = strtok(NULL, separa);
            }

            // Se define root como la funcion para insertar (proceso iterativo que va haciendo cada vez otro root)
            root = insert(root, aux);
        }
    }

    // Se cierra el archivo, puesto que, los datos presentes en el archivo ya fueron ingresados.
    fclose(fp);

    // Proceso para imprimir por pantalla los nombres de los N mas peligrosos (N es ingresado por el usuario).

    // Se define "Contador" y se inicializa en cero
    int Contador = 0;

    // Se crea un puntero al contenido de la variable Contador
    int * pointer = &Contador;

    // Funcion que se utiliza para mostrar los N enemigos mas peligrosos
    show_nodes(root, pointer, N);
}