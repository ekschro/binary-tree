#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int value;
  char *place;
  struct node_t *parent;
  struct node_t *left_child;
  struct node_t *right_child;
} node_t;

void freeTree(node_t *l) {
  if (l != 0) {
    freeTree(l->left_child);
    freeTree(l->right_child);
    free(l);
  }
}

void printTree(node_t *l) {
  int d = 0;
  if (l != 0) {
    printTree(l->left_child);
    printTree(l->right_child);
    if (l->parent != 0) {
      d = (l->parent)->value;
    }
    printf("val = %d, parent = %d, %s\n", l->value, d,l->place);
  }
}

//Locates the appropriate parent for the given node value.
node_t *locateParent(node_t **t, node_t *z) {
  node_t *y = 0;
  node_t *x = *t;

  while (x != 0) {
    y = x;
    if (z->value < x->value) {
      x = x->left_child;
    }
    else {
      x = x->right_child;
    }
  }
  return y;
}

void treeInsert(node_t **t, int n) {
  node_t *z = malloc(sizeof(node_t));
  node_t *y;

  z->value = n;
  y = locateParent(t,z);

  z->parent = y;
  z->left_child = 0;
  z->right_child = 0;

  if (y == 0) {
    z->place = "root";
    *t = z;
  }
  else if (z->value < y->value) {
    z->place = "left";
    y->left_child = z;
  }
  else {
    z->place = "right";
    y->right_child = z;
  }
}

int main(void) {
  node_t *root = 0;
  node_t **tree = &root;

  int input;

  while (input != -1) {
    scanf("%d",&input);
    treeInsert(tree,input);
  }

  node_t *p = root;
  printTree(p);

  freeTree(*tree);

  return 0;
}
