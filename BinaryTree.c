#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
  long long value;
  struct node_t *parent;
  struct node_t *left_child;
  struct node_t *right_child;
} node_t;

// Frees all allocated memory used for the created tree.
void freeTree(node_t *l) {
  if (l != 0) {
    freeTree(l->left_child);
    freeTree(l->right_child);
    free(l);
  }
}

// Prints tree, this was used for testing reasons.
void printTree(node_t *l) {
  long long d = 0;
  if (l != 0) {
    printTree(l->left_child);
    printTree(l->right_child);
    if (l->parent != 0) {
      d = (l->parent)->value;
    }
    printf("val = %lli, parent = %lli\n", l->value, d);
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

// Inserts a new node into binary tree.
void btreeInsert(node_t **t, long long n) {
  node_t *z = malloc(sizeof(node_t));
  node_t *y;

  z->value = n;
  y = locateParent(t,z);

  z->parent = y;
  z->left_child = 0;
  z->right_child = 0;

  if (y == 0) {
    *t = z;
  }
  else if (z->value < y->value) {
    y->left_child = z;
  }
  else {
    y->right_child = z;
  }
}

//
int btreeEvenSumRange(node_t *r, long long min, long long max) {
  int i = -1;
  int left = -1;
  int right = -1;

  if (r != 0) {
    if (min <= r->value)
      left = btreeEvenSumRange(r->left_child, min, max);
    if (r->value <= max)
      right = btreeEvenSumRange(r->right_child, min, max);

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
  node_t *root = 0;       // Initialize pointer to root of tree to NULL
  node_t **tree = &root;  // Initialize tree pointer to address of root pointer

  FILE *data;             // Initialize FILE pointers for data and ranges
  FILE *ranges;

  long long inputData;    // Temporary variables for reading data and ranges
  long long minMax[2];

  // Open data file and ranges files at locations given by user
  data = fopen(argv[1],"r");
  ranges = fopen(argv[2],"r");

  // Read and insert data values into Binary tree
  while (fscanf(data,"%lli",&inputData) != EOF) {
    btreeInsert(tree,inputData);
  }

  // Read ranges, query binary tree with range values, and then output
  // if the range query results in an even or odd sum.
  while (fscanf(ranges,"%lli %lli",&minMax[0],&minMax[1]) != EOF) {
    if (btreeEvenSumRange(root, minMax[0], minMax[1]) == 1) {
      printf("Range [%lli,%lli]: %s\n", minMax[0], minMax[1], "odd sum");
    }
    else {
      printf("Range [%lli,%lli]: %s\n", minMax[0], minMax[1], "even sum");
    }
  }

  // Free all allocated memory for the tree and close opened files.
  freeTree(root);
  fclose(data);
  fclose(ranges);

  return 0;
}
