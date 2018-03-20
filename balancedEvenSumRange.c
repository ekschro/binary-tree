//
//  balancedEvenSumRange.c
//  Binary Tree Assignment
//
//  Created by Ericsson Schroeter on 3/11/18.
//  Copyright © 3/19/18 Ericsson Schroeter. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum {RED,BLACK} color_t;

typedef struct node_t {
  long value;
  color_t color;
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

//Locates the appropriate parent for the given node value.
node_t *locateParent(node_t **t, node_t *z) {
  // Initialize pointer y to NULL and set pointer x to root node.
  node_t *y = 0;
  node_t *x = *t;

  // While pointer x is not NULL navigate the tree based on the value of node z
  // to find the appropriate parent.
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

//leaf
node_t *leaf(node_t *z) {
  node_t *y = malloc(sizeof(node_t));
  *y = (node_t) {.value = 0, .color = BLACK, .parent = z, .left_child = 0, .right_child = 0};

  return y;
}

//sibling
node_t *sibling(node_t *x) {
  node_t *p = x->parent;

  if (p == 0) {
    return 0;
  }
  if (p->left_child == x) {
    return p->right_child;
  }
  else {
    return p->left_child;
  }
}

//transplant
void transplant(node_t **t, node_t *u, node_t *v) {
  node_t *p =u->parent;

  if (p == 0) {
    *t = v;
  }
  else if (u == p->left_child) {
    p->left_child = v;
  }
  else {
    p->right_child = v;
  }

  if (v != 0) {
    v->parent = p;
  }
}

//rotateLeft
void rotateLeft(node_t **t,node_t *x) {
  node_t *y = x->right_child;
  node_t *b = y->left_child;
  transplant(t,x,y);
  x->right_child = b;

  if (b != 0) {
    b->parent = x;
  }

  y->left_child = x;
  x->parent = y;
}

//rotateRight
void rotateRight(node_t **t, node_t *x) {
  node_t *y = x->left_child;
  node_t *b = y->right_child;
  transplant(t,x,y);
  x->left_child = b;

  if (b != 0) {
    b->parent = x;
  }

  y->right_child = x;
  x->parent = y;
}

//rbInsertFixupA(T,z)
void rbInsertFixupA(node_t **t, node_t *z) {
  node_t *y;
  while (z != *t && (z->parent)->color == RED) {
    y = sibling(z->parent);
    if (y->color == BLACK) {
      break;
    }
    (z->parent)->color = BLACK;
    y->color = BLACK;
    z = (z->parent)->parent;
    z->color = RED;
  }
}

//rbInsertFixupC(T,z)
void rbInsertFixupC(node_t **t, node_t *z) {
  node_t *x,*w;
  if (z == *t || (z->parent)->color == BLACK) {
    return;
  }

  x = z->parent;
  w = x->parent;

  if (z == x->left_child && x == w->left_child) {
    rotateRight(t,w);
    x->color = BLACK;
    w->color = RED;
  }
  else if (z == x->right_child && x == w->right_child) {
    rotateLeft(t,w);
    x->color = BLACK;
    w->color = RED;
  }
}

//rbInsertFixupB(T,z)
void rbInsertFixupB(node_t **t, node_t *z) {
  node_t *x,*w;
  if (z == *t || (z->parent)->color == BLACK) {
    return;
  }

  x = z->parent;
  w = x->parent;

  if (z == x->right_child && x == w->left_child) {
    z = x;
    rotateLeft(t,x);
  }
  else if (z == x->left_child && x == w->right_child) {
    z = x;
    rotateRight(t,x);
  }
  rbInsertFixupB(t,z);
}

//rbInsertFixup(T,z)
void rbInsertFixup(node_t **t,node_t *z) {
  rbInsertFixupA(t,z);
  rbInsertFixupB(t,z);
  rbInsertFixupC(t,z);
  (*t)->color = BLACK;
}

// Inserts a new node into binary tree.
void btreeInsert(node_t **t, long n) {
  // Allocate memory for new node being inserted and initialize pointer for
  // the appropriate parent.
  node_t *z = malloc(sizeof(node_t));
  node_t *y;

  // Set value of new node z and point y to appropriate parent of z
  z->value = n;
  y = locateParent(t,z);

  // Initialize z left and right children to NULL
  z->parent = y;
  z->color = RED;
  z->left_child = leaf(z);
  z->right_child = leaf(z);

  // If y is NULL then set new node z as root of the tree.  Otherwise, set z
  // as the left child of y if z's value is less than y's or as the right child
  // of y if it is greater than or equal to y's value.
  if (y == 0) {
    *t = z;
  }
  else if (z->value < y->value) {
    y->left_child = z;
  }
  else {
    y->right_child = z;
  }

  rbInsertFixup(t,z);
}

// btreeEvenSumRange takes in the root node pointer of a binary tree and the
// minimum and maximum of a range as long.  It returns a 1 if the sum of
// the values within the range is odd, a 0 if it is even, and a -1 if there are
// no values found within the given range.
int btreeEvenSumRange(node_t *r, long min, long max) {
  // Initialize i, left, and right variables to -1
  int i = -1;
  int left = -1;
  int right = -1;

  // If current node is not NULL
  if (r != 0) {
    // If minimum of given range is less then or equal to
    // node value then call this for the left child of the current node.
    if (min <= r->value) {
      left = btreeEvenSumRange(r->left_child, min, max);
    }

    // If maximum of given range is greater than or equal to
    // then node value then call this for the left child of the current node.
    if (r->value <= max) {
      right = btreeEvenSumRange(r->right_child, min, max);
    }

    // Based on the state of left and right varibles use bitwise XOR operator
    // to define current state of i.
    if (left > -1 && right > -1) {
      i = right^left;
    }
    else if (left > -1){
      i = left;
    }
    else if (right > -1) {
      i = right;
    }

    // If the current node value is between both the min and max then determine
    // whether it is even or odd and then use a XOR bitwise operation to adjust
    // the current state of i.
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

  long inputData;    // Temporary variables for reading data and ranges
  long minMax[2];

  // Open data file and ranges files at locations given by user
  data = fopen(argv[1],"r");
  ranges = fopen(argv[2],"r");

  // Read and insert data values into Binary tree
  while (fscanf(data,"%ld",&inputData) != EOF) {
    btreeInsert(tree,inputData);
  }

  // Read ranges, query binary tree with range values, and then output
  // if the range query results in an even or odd sum.
  while (fscanf(ranges,"%ld %ld",&minMax[0],&minMax[1]) != EOF) {
    if (btreeEvenSumRange(root, minMax[0], minMax[1]) == 1) {
      printf("Range [%ld,%ld]: %s\n",minMax[0], minMax[1], "odd sum");
    }
    else {
      printf("Range [%ld,%ld]: %s\n",minMax[0], minMax[1], "even sum");
    }
  }

  // Free all allocated memory for the tree and close opened files.
  freeTree(root);
  fclose(data);
  fclose(ranges);

  return 0;
}
