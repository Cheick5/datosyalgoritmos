// Se importan todas las librerias necesarias.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"


//Se crea una funcion "menor_que" que entrega un 1 si el primero es menor o cero en caso contrario
int menor_que(atacante a1, atacante a2)
{
    if (a1.categoria < a2.categoria) { //Comparacion de categorias
        return 1;
    }

    if (a1.categoria == a2.categoria) { //Si son iguales, vemos las probabilidades
        
        // Caso en el cual o la probabilidad del primero es menor a la del segundo o si son iguales y se comparan los nombres alfabeticamente
        if(a1.prob_ataque < a2.prob_ataque || (a1.prob_ataque == a2.prob_ataque && strcmp(a1.nombre, a2.nombre) > 0)){  
            return 1;
        }
    }

    return 0;
}

// Funcion (entregada por el profesor) que entrega el mayor entre los dos parametros que se le entregan
int max(int a, int b) {
    return (a > b)? a : b;
}

// Funcion (entregada por el profesor) que entrega la altura del arbol
int height(struct node *node) {
    if (node == NULL) {

        // En caso de que el arbol no tenga datos (sea NULL) se debe retornar cero
        return 0;
    }

    // Se retorna la altura del arbol, se le suma uno para que no parta del cero
    return 1 + max(height(node->left), height(node->right));
}

//Funcion (entregada por el profesor) que entrega la altura entre dos nodos, positivo si esta cargado a la izquierda, negativo en caso contrario
int balance(struct node *node) {
    if (node == NULL) {

        // En caso de que el arbol no tenga datos (sea NULL) se debe retornar cero
        return 0;
    }

    // Retorna el balance, este servira para analizar los casos en los cuales exista un desbalance y se tenga que realizar alguna rotacion (hacia derecha o izquierda)
    return height(node->left) - height(node->right);
}

// Funcion (entregada por el profesor) que sirve para evitar el desbalance, realizando una rotacion hacia la izquierda
struct node *leftRotate(struct node *x) {

    // y es el pivote (nueva raiz)
    struct node *y = x->right;
    // z podria ser NULL (lo cual no es un problema)
    struct node *z = y->left;

    // Se realiza la rotacion hacia la izquierda
    y->left = x;
    x->right = z;

    // Se actualiza la altura (height) de y e x 
    // La altura (height) de los otros nodos no cambia; no hay que actualizar
    y->height = height(y);
    x->height = height(x);

    // Se retorna el pivote (y)
    return y;
}

// Funcion (entregada por el profesor) que sirve para evitar el desbalance, realizando una rotacion hacia la derecha
struct node *rightRotate(struct node *y) {
    // x es el pivote (nueva raiz)
    struct node *x = y->left;
    // z podria ser NULL (lo cual no es un problema)
    struct node *z = x->right;

    // Se realiza la rotacion hacia la derecha
    x->right = y;
    y->left = z;

    // Se actualiza la altura (height) de y e x 
    // La altura (height) de los otros nodos no cambia; no hay que actualizar
    y->height = height(y);
    x->height = height(x);

    // Se retorna el pivote (x)
    return x;
}

// Funcion (entregada por el profesor) que sirve para insertar datos (en este caso se insertan en la estructura del arbol)
struct node *insert(struct node *node, atacante atacante) {

    // Caso arbol vacio
    if (node == NULL) { 

        // Al ser vacio, se debe pedir memoria dinamica y se crea un nuevo nodo "tmp"
        struct node *tmp = (struct node *)malloc(sizeof(struct node));

        // Se asignan los datos correspondientes a cada entidad
        tmp->x = atacante;
        tmp->left = NULL;
        tmp->right = NULL;

        // Al ser vacio, cuando se agrega este nodo, la nueva altura (height) queda en uno
        tmp->height = 1; 

        // Se retorna el nuevo nodo creado
        return tmp;
    }

    // caso en que el arbol es no vacio
    // en este caso la raiz es la misma, es por esto que al final esta el "return node;" 
    // Se llama recursivamente al metodo insert ya sea al lado izquierdo o derecho
    // Se actualiza el hijo correpondiente con la nueva raiz obtenida

    // Condicional que sirve para analizar si se debe insertar por la izquierda o derecha (en este caso es por izquierda)
    if (menor_que(atacante,node->x) == 1) {
        //Si la categoria y la prpobabilidad del atacante a insertar es menor que el que ya está, se inserta a la izquierda
        node->left = insert(node->left, atacante);
    }

    // Condicional que sirve para analizar si se debe insertar por la izquierda o derecha (en este caso es por derecha)
    else {
        node->right = insert(node->right, atacante);
    }

    // Se actualiza la altura (height) de node (actualizar la altura del arbol)
    node->height = height(node);

    // Se calcula el balance de node (del arbol)

    // si balance > 1 o balance < -1, el nodo esta desbalanceado, positivo si esta cargado a la izquierda, negativo en caso contrario (cargado hacia la derecha)
    int node_balance = balance(node);

    // caso left left, cargado a la izquierda, por lo tanto, se debe hacer una rotacion a la derecha
    if (node_balance > 1 && menor_que(atacante,node->left->x) == 1) {
        return rightRotate(node);
    }

    // caso right right, por lo tanto, se debe hacer una rotacion a la izquierda
    if (node_balance < -1 && menor_que(atacante,node->right->x) == 0) {
        return leftRotate(node);
    }

    // caso left right, en este caso se deben hacer dos rotaciones, la primera hacia la izquierda y luego hacia la derecha
    if (node_balance > 1 && menor_que(atacante,node->left->x) == 0 ) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // caso right left, en este caso se deben hacer dos rotaciones, la primera hacia la derecha y luego hacia la izquierda
    if (node_balance < -1 && menor_que(atacante,node->right->x) == 1) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Se retorna el nodo
    return node;
}

// Funcion "show_nodes" para mostrar los nodos de mayor a menor (D,R,I)
void show_nodes(struct node *root, int *puntero, int N){

    // Caso arbol vacio
    if (root == NULL){

        // No debe retornar nada, ya que, no hay nada que mostrar
        return;
    }

    // Usamos un puntero como contador para que al actualizar el valor en las funciones recursivas, se actualice también en las demás
    // Caso en que el puntero sea igual al N (numero de enemigos a mostrar)
    if (*puntero == N){

        // No debe retornar nada
        return;
    }

    // En primer lugar, se imprime por la derecha y se verifica si el puntero es efectivamente igual a N o no
    show_nodes(root->right, puntero, N);

    // Caso en que el puntero sea igual al N (numero de enemigos a mostrar)
    if (*puntero == N){

        // No debe retornar nada
        return;
    }

    // En segundo lugar, se imprime la raiz
    printf("Nombre = %s \n", root->x.nombre);

    // Se le suma una unidad a "*puntero"
    *puntero = *puntero + 1;

    // En tercer lugar, se imprime por la izquierda
    show_nodes(root->left, puntero, N);

    // Se retorna
    return;
}