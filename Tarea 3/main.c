// Se importan todas las librerias necesarias.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define TABLE_SIZE 5

// Definimos las opcines numericas que podria tener el switch para hacer los case.
enum OPTIONS {NOMBRE = 1, CATEGORIA = 2, PROBABILIDAD = 3};

int main(int argc, char* argv[]) {

    // Se abre el archivo que es entregado por el usuario y se crean variables que utilizaremos para leer los datos del archivo.
    FILE *fp = fopen(argv[1], "r");
    char line[1000];
    char separa[] = ",";
    int categoria;

    struct node *tabla[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i) {
        tabla[i] = NULL; // Inicializamos la tabla en null para evitar errores random
    }

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

            // Utilizamos la funcion entregada por el profesor para insertar en la lista correspondiente.
            insertar_encadenamiento(tabla, categoria-1, aux);
        }
    }

    // Se cierra el archivo, puesto que, los datos presentes en el archivo ya fueron ingresados a sus correspondientes listas.
    fclose(fp);

    printf("\n");

    // Ahora se realizara el proceso de ordenamiento para las listas, en primer lugar deben ser ordenadas por probabilidad de mayor a menor.
    // Luego realizaremos el procedimiento de ordenamiento para cada lista en particular (tienen diferentes requisitos).
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

    // Como tenemos los datos a la mitad de la lista 2 (requisito propio de esta), realizamos un ordenamiento alfabetico para que queden ordenados correctamente.
    ordenar_lista_Alfabetico(tabla[2]);

    // Se imprimen todas las listas con las 5 categorias.
    imprimir_tabla_encadenamiento(tabla,5);

    // Se realiza el proceso en el cual se imprime en un archivo de salida las N personas mas peligrosas (número entregado por el usuario).
    // Se crea una variable contador para tener en cuenta la cantidad de personas que han sido ingresadas en el archivo de salida y se pasa a int el numero que ingreso el usuario.
     int contador = 0;
     FILE *fpout = fopen(argv[3], "w");
     int N = atoi(argv[2]);

    //Para cada categoria, comenzando con la 5 (mas peligrosos).
    for (int i = TABLE_SIZE -1 ; i >= 0; i--) { 
        struct node *it = tabla[i];

        // Utilizamos la funcion "largo_hash" para que se imprima solamente una vez cada nombre en cada categoria.
        int largo = largo_hash(it);

         for (int j = 0; j < largo ; j++){
        
        // Mientras contador sea menor a N, debemos seguir ingresando nombres al archivo de salida.
        if (contador < N){
        
          fprintf(fpout, "%s\n", it->x.nombre);
          it = it->next;
          contador++;
         }

        // Una vez que contador es mayor que N, ya debemos dejar de ingresar nombres. 
        else if (contador > N){
             break;
         }
       }
     }

    // Se cierra el archivo de salida.
    fclose(fpout);
    
    return 0;
}