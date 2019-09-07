#include "cstdio"
#include "cstdlib"
#include "cstring"
#include "vector"

struct node {
  node *parent;
  node *left_child; 
  node *left_sibling;
  node *right_sibling;

  int val;
};

const int maxN = 10000;

node *min_ptr;
node *roots[maxN];

vector<node*> roots;

int insert(int nval){
  node *nnode = malloc(sizeof(node));

  // Constructor
  nnode->parent = nnode->left_child = nnode->left_sibling = 
      nnode->right_sibling = NULL;
  nnode->val = nval;

  return 0;
}

int main(){


  return 0;
}