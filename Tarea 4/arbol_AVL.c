// Se importan todas las librerias necesarias.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"


//Entrega un 1 si el primero es menor
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

        // else {

        //     if (strcmp(a1.nombre, a2.nombre) > 0) {
        //         return 1;
        //     }
        // }
    }

    return 0;
}

// funcion auxiliar maximo
int max(int a, int b)
{
    return (a > b)? a : b;
}

int height(struct node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

//Altura entre dos nodos, positivo si esta cargado a la izquierda
int balance(struct node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

struct node *leftRotate(struct node *x) {
    // y es el pivote (nueva raiz)
    struct node *y = x->right;
    // OJO: z podria ser NULL (lo cual no es un problema)
    struct node *z = y->left;

    // rotamos a la izquierda
    y->left = x;
    x->right = z;

    // actualizamos el height de y e x 
    // (height de los otros nodos no cambia; no hay que actualizar)
    y->height = height(y);
    x->height = height(x);

    return y;
}

struct node *rightRotate(struct node *y) {
    // x es el pivote (nueva raiz)
    struct node *x = y->left;
    // OJO: z podria ser NULL (lo cual no es un problema)
    struct node *z = x->right;

    // rotamos a la derecha
    x->right = y;
    y->left = z;

    // actualizamos el height de y e x 
    // (height de los otros nodos no cambia; no hay que actualizar)
    y->height = height(y);
    x->height = height(x);

    return x;
}

struct node *insert(struct node *node, atacante atacante) {
    if (node == NULL) { // caso arbol vacio
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        tmp->x = atacante;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1; // en este caso las hojas tienen altura 1
        return tmp;
    }

    // caso en que el arbol es no vacio
    // en este caso la raiz es la misma, por eso hacemos "return node;" al final
    // llamamos recursivamente al metodo insert ya sea al lado izquierdo o derecho
    // actualizamos el hijo correpondiente con la nueva raiz obtenida
    if (menor_que(atacante,node->x) == 1) {
        //Si la categoria y la prpobabilidad del atacante a insertar es menor que el que ya está, se inserta a la izquierda
        node->left = insert(node->left, atacante);
    }
    else {
        node->right = insert(node->right, atacante);
    }

    // actualizamos height de node
    node->height = height(node);
    // calculamos balance de node
    // si balance > 1 o balance < -1, el nodo esta desbalanceado, positivo si esta cargado a la izquierda
    int node_balance = balance(node);

    // caso left left, cargado a la izquierda
    if (node_balance > 1 && menor_que(atacante,node->left->x) == 1) {
        return rightRotate(node);
    }
    // caso right right
    if (node_balance < -1 && menor_que(atacante,node->right->x) == 0) {
        return leftRotate(node);
    }
    // caso left right
    if (node_balance > 1 && menor_que(atacante,node->left->x) == 0 ) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // caso right left
    if (node_balance < -1 && menor_que(atacante,node->right->x) == 1) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// (D,R,I)
void show_nodes(struct node *root, int Contador, int N){

    if (root == NULL){
        return;
    }

    if (Contador == N){
        return;
    }

    // Contador = Contador + 1;

    show_nodes(root->right, Contador + 1, N);

    printf("Nombre = %s \n", root->x.nombre);

    show_nodes(root->left, Contador + 1, N);


    // printf("%d\n", Contador);
    
    return;
}