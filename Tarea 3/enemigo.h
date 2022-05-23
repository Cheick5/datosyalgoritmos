// Se crea la estructura atancantes que contiene los datos de cada atacante, es decir, su nombre y su probabilidad de ataque.
struct atacantes {
    char nombre[100];
    float prob_ataque;
};
// Se crea un nombre para llamar a la estructura de una manera mas facil.
typedef struct atacantes atacante;

// Se crea la estructura node que contiene los datos de cada atacante (x) y un puntero al siguiente de ese nodo.
struct node {
    atacante x;
    struct node *next;
};