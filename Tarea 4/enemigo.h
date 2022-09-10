// Se define la estructura atacantes, la cual contiene los tres datos de cada enemigo y utilizando typedef se denomina como atacante (para simplificar el llamado)
typedef struct atacantes {
    char nombre[100];
    int categoria;
    float prob_ataque;
} atacante;

// Se define la estructura node (representa el arbol), la cual contiene la altura, el nodo de la derecha, el de la izquierda y un puntero a la estructura atacante (x)
struct node {
  atacante x;
  struct node *left;
  struct node *right;
  int height;
};  


// wena 