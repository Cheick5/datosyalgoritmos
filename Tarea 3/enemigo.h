struct atacantes {
    char nombre[100];
    float prob_ataque;
};
typedef struct atacantes atacante;

struct node {
    atacante x;
    struct node *next;
};