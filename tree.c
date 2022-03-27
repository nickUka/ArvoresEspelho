// NICKOLAS UKASINSKI - GRR20193940
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COUNT 5
typedef struct {
    int value;
    struct tree *r, *l;
} tree;

//PRINT TREE IN 2D FUNCTIONS FROM https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
// It does reverse inorder traversal
void print2DUtil(tree *root, int space) {
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->r, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    // Process left child
    print2DUtil(root->l, space);
}

void print2D(tree *root) {
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

tree *init() // aloca memória para o nodo
{
    tree *p;
    p = (tree *) malloc(sizeof(tree));
    if (!p) {
        printf("Problema de alocação");
        exit(0);
    }
    p->l = NULL;
    p->r = NULL;

    return p;
}


void put(tree **t, int value) {
    tree *branch, *aux, *ant;
    branch = init();

    branch->value = value;
    if ((*t) == NULL) {
        *t = branch;
    } else {
        aux = *t;
        while (aux != NULL) {
            ant = aux;
            if (aux->value > branch->value)
                aux = aux->l;
            else
                aux = aux->r;
        }
        if (ant->value > branch->value)
            ant->l = branch;
        else
            ant->r = branch;
    }
}

int eh_espelho(tree *a, tree *b) {
    if(!a && !b )
        return 1;
    if (!a || !b || a->value != b->value)
        return 0;

    return (eh_espelho((a->l), (b->r)) &&
            eh_espelho((a->r), (b->l)));


}

tree *cria_espelho(tree **t) {
    tree *new_tree, *r, *l;
    if (!(*t))
        return NULL;

    l = cria_espelho(&(*t)->l);
    r = cria_espelho(&(*t)->r);

    new_tree = init();
    new_tree->value = (*t)->value;
    new_tree->l = r;
    new_tree->r = l;
    return new_tree;
}

void init_tree(tree **tree) {
    *tree = NULL;
}

void print_in_order(tree *t) {
    if (!t)
        return;

    print_in_order(t->l);
    print_in_order(t->r);
    printf("%d, ", t->value);

}

int main() {
    tree *tree, *esp;

    init_tree(&tree);
//    init_tree(&esp);

    put(&tree, 6);
    put(&tree, 3);
    put(&tree, 2);
    put(&tree, 4);
    put(&tree, 8);
    put(&tree, 9);
    put(&tree, 7);

//    put(&esp, 6);
//    put(&esp, 3);
//    put(&esp, 2);
//    put(&esp, 4);
//    put(&esp, 8);
//    put(&esp, 9);
//    put(&esp, 7);

    print2D(tree);
    printf("\n");
    printf("\n");
    printf("\n");

    esp = cria_espelho(&tree);
    print2D(esp);
    printf("\n");

    printf("%d", eh_espelho(tree, esp));
    // char hora2[8] = "22:12:15";
    // t_time time2 = string_to_time(hora2);
    // printf("%s", time_to_string(time2));
    // printf("%d", time_cmp(time, time2));
}