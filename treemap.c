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

  /*TreeNode *aux = node->parent;
  TreeNode *aux2;

  if(node->left == NULL && node->right == NULL){

    if(aux == NULL){
      tree->root = NULL;
    }
    
    if(aux->left == node){
      if(aux == tree->root) tree->root->left = NULL;
      aux2 = aux->left;
      aux->left = NULL;
      free(aux2);
    }
    else{
      if(aux->right == node){
        if (aux == tree->root) tree->root->right = NULL;
        aux2 = aux->right;
        aux->right = NULL;
        free(aux2);
      }
      
    }
  } */

  
  TreeNode *parent = node->parent;

  // Case 1: No children
  if (node->left == NULL && node->right == NULL) {
    if (parent == NULL) {
      // Node is the root
      tree->root = NULL;
    } else {
      // Remove node as a child of its parent
      if (parent->left == node) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    }
    free(node->pair);
    free(node);
  }
  // Case 2: One child
  else if (node->left == NULL || node->right == NULL) {
    TreeNode* child = (node->left != NULL) ? node->left : node->right;
    child->parent = parent;
    if (parent == NULL) {
      // Node is the root
      tree->root = child;
    } else {
      // Replace node with its child as a child of its parent
      if (parent->left == node) {
        parent->left = child;
      } else {
        parent->right = child;
      }
    }
    free(node->pair);
    free(node);
  }
  // Case 3: Two children
  else {
    // Find the minimum node in the right subtree
    TreeNode* min = node->right;
    while (min->left != NULL) {
      min = min->left;
    }
    // Replace the node with its minimum child
    Pair* temp = node->pair;
    node->pair = min->pair;
    min->pair = temp;
    removeNode(tree, min);
  }
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
    if(tree->lower_than(aux->pair->key, key) == 1){
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
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
