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
  tree->current = tree->root;
  TreeNode *new = createTreeNode(key, value);
  
  if(tree->root == NULL){
    tree->root = new;
    return;
  }
  
  if(searchTreeMap(tree, key) != NULL) return;
  while(tree->current != NULL)
    {
      if(tree->lower_than(tree->current->pair->key, key))
      {
        //hacia derecha
        if(tree->current->right == NULL){
          tree->current->right = new;
          new->parent = tree->current->right;
          return;
        }
        tree->current = tree->current->right;
      }
      else
      {
        //hacia izq
        tree->current = tree->current->left;
      }
    }
}


TreeNode * minimum(TreeNode * x){

  while (x->left != NULL)
  {
    x = x->left;
  }

    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  
  TreeNode *padre = node->parent;
  TreeNode *hijo;

  if (node->left == NULL && node->right == NULL) {
    if (padre == NULL) {
      tree->root = NULL;
    } else {
      if (padre->left == node) {
        padre->left = NULL;
      } else {
        padre->right = NULL;
      }
    }
    free(node);
  }
  else if (node->left == NULL || node->right == NULL) {

    if (node->left != NULL){
      hijo = node->left;
    } else{
      hijo = node->right;
    }
    
    hijo->parent = padre;
    if (padre == NULL) {
      tree->root = hijo;
    } else {
      if (padre->left == node) {
        padre->left = hijo;
      } else {
        padre->right = hijo;
      }
    }
    free(node);
  }
  else {
    
    TreeNode* minimo = minimum(node->right);

  node->pair->key = minimo->pair->key;
    node->pair->value = minimo->pair->value;
    
    removeNode(tree, minimo);
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

while(aux != NULL){
      if(is_equal(tree, aux->pair->key, key) == 1){
    tree->current = aux;
    return aux->pair;
  }
  else{
    if(tree->lower_than(aux->pair->key, key) == 0){
      aux = aux->left;
    }
    else{
      aux = aux->right;
    }
  }
}


  if(aux == NULL) return NULL;
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
 /* TreeNode *minimo = minimum(tree->root);
  TreeNode *siguiente = minimo;

  if (minimo->pair->key == key) return minimo->pair;
  while(1)
    {
      if (siguiente->pair->key < key){
        tree->current = siguiente;
        siguiente->pair = nextTreeMap(tree);
      }
    } */
  //TreeNode *aux = tree->root;
  
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode *primero = minimum(tree->root);
  
    return primero->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  TreeNode *siguiente;
  TreeNode *padre;
  
  if(tree->current->right != NULL){
    siguiente = minimum(tree->current->right);
    tree->current = siguiente;
    return siguiente->pair;
    
  }else{
    
    padre = tree->current->parent;
    if(padre->parent == NULL) return NULL;
    
    while (tree->current->pair->key < padre->pair->key){
      if(padre->parent == NULL && padre == tree->root) return padre->pair;
      padre = padre->parent;
    }
    tree->current = padre;
    return padre->pair;
  }
}

