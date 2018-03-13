#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  int value;
  char *place;
  struct node_t *parent;
  struct node_t *left_child;
  struct node_t *right_child;
} node_t;

typedef struct list_t {
  int min;
  int max;
  struct list_t *prev;
} list_t;

void freeTree(node_t *l) {
  if (l != 0) {
    freeTree(l->left_child);
    freeTree(l->right_child);
    free(l);
  }
}

void freeList(list_t *l) {
  if (l != 0) {
    freeList(l->prev);
    free(l);
  }
}

void printList(list_t *l) {
  if (l != 0) {
    printList(l->prev);
    printf("%d %d\n", l->min, l->max);
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

void addToList(list_t **l, int min, int max) {
  list_t *new = malloc(sizeof(list_t));

  new->min = min;
  new->max = max;
  new->prev = *l;
  *l = new;
}

int treeReportRange(node_t *r, int min, int max) {
  int i = -1;
  int left = -1;
  int right = -1;

  if (r != 0) {
    if (min <= r->value)
      left = treeReportRange(r->left_child, min, max);
    if (r->value <= max)
      right = treeReportRange(r->right_child, min, max);

    if (left > -1 && right > -1) {
      i = right^left;
    }
    else if (left > -1){
      i = left;
    }
    else if (right > -1) {
      i = right;
    }

    if (min <= r->value && r->value <= max) {
        if ((r->value%2) == 0) {
          if (i != -1) {
            i = i^0;
          }
          else {
            i = 0;
          }
        }
        else {
          if (i != -1) {
            i = i^1;
          }
          else {
            i = 1;
          }
        }
    }
  }

  return i;
}

int main(int argc,char *argv[]) {
  node_t *root = 0;
  node_t **tree = &root;

  list_t *last = 0;
  list_t **head = &last;

  FILE *data;
  FILE *ranges;
  char *fileLoc;

  int inputData;
  int minMax[2];

  data = fopen(argv[1],"r");
  ranges = fopen(argv[2],"r");

  while (fscanf(data,"%d",&inputData) != EOF) {
    treeInsert(tree,inputData);
  }

  while (fscanf(ranges,"%d %d",&minMax[0],&minMax[1]) != EOF) {
    addToList(head,minMax[0],minMax[1]);
  }

  //printTree(root);
  //printList(last);

  freeTree(root);
  freeList(last);
  fclose(data);
  fclose(ranges);

  return 0;
}
