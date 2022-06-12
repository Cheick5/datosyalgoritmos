// Se importan todas las librerias necesarias.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arbol_AVL.h"

int height(struct node *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + max(height(node->left), height(node->right));
}

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

struct node *insert(struct node *node, int data) {
    if (node == NULL) { // caso arbol vacio
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        tmp->data = data;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1; // en este caso las hojas tienen altura 1
        return tmp;
    }

    // caso en que el arbol es no vacio
    // en este caso la raiz es la misma, por eso hacemos "return node;" al final
    // llamamos recursivamente al metodo insert ya sea al lado izquierdo o derecho
    // actualizamos el hijo correpondiente con la nueva raiz obtenida
    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else {
        node->right = insert(node->right, data);
    }

    // actualizamos height de node
    node->height = height(node);
    // calculamos balance de node
    // si balance > 1 o balance < -1, el nodo esta desbalanceado
    int node_balance = balance(node);

    // caso left left
    if (node_balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }
    // caso right right
    if (node_balance < -1 && data >= node->right->data) {
        return leftRotate(node);
    }
    // caso left right
    if (node_balance > 1 && data >= node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // caso right left
    if (node_balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}