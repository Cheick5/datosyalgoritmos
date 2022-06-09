typedef struct atacantes {
    char nombre[100];
    float prob_ataque;
} atacante;

struct node {
  atacante x;
  struct node *left;
  struct node *right;
  int height;
};  