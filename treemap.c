#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap *nuevoMapa = (TreeMap *) malloc(sizeof(TreeMap));
  nuevoMapa->root = NULL;
  nuevoMapa->current = NULL;
  nuevoMapa->lower_than = lower_than;
    return nuevoMapa;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  

}

TreeNode * minimum(TreeNode * x){

  while (x->left != NULL)
  {
    x = x->left;
  }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

  
  TreeNode *aux;
  TreeNode *aux2;
  
  if (node->left == NULL && node->right == NULL){
    aux = node->parent;
    aux2 = node;

    if (aux->left->pair->key == aux2->pair->key){
      aux->left = NULL;
    }
    
    if (aux->right->pair->key == aux2->pair->key){
      aux->right = NULL;
    }

    
    free(node);
    
  }

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  
  TreeNode *aux = tree->root;

  do
    {
      if(is_equal(tree, aux->pair->key, key) == 1){
    tree->current = aux;
    return aux->pair;
  }
  else{
    if(tree->lower_than(aux->pair->key, key) == 1){
      aux = aux->left;
    }
    else{
      aux = aux->right;
    }

      
    }while (aux->right != NULL || aux->left != NULL)
  



  if(aux == NULL) return NULL;
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
