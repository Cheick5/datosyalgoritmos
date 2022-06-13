// Se incluye el archivo .h que contiene las estructuras. 
#include "enemigo.h"


int menor_que(atacante a1, atacante a2);
int max(int a, int b);
int height(struct node *node);
int balance(struct node *node);
struct node *leftRotate(struct node *x);
struct node *rightRotate(struct node *y);
struct node *insert(struct node *node, atacante atacante);
void show_nodes(struct node *root);