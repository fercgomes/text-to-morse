#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "splay.h"

tNode* rightRotation(tNode* root) {
  tNode* aux = root->left;
  root->left = aux->right;
  aux->right = root;
  return aux;
}

tNode* leftRotation(tNode* root) {
  tNode* aux = root->right;
  root->right = aux->left;
  aux->left = root;
  return aux;
}

tNode* splay(tNode* root, int key, int* search_count) {
  if (root == NULL) { // Check if tree is empty
   return NULL;
  } else if (root->ascii == key) { // Check if the key the algorithm is looking for, is the root tree
    (*search_count) += 1;
    return root;
  } else if (root->ascii < key) { //If the key is bigger than the key of the root, ZAG!
    if (root->right == NULL) { // If the right key doesn't exist, returns the root and concludes the key isn't presented in the tree
      (*search_count) += 2;
        return root;
    } else if (root->right->ascii < key) { // If the key is on the right tree of the right tree, ZAG-ZAG
        (*search_count) -= 1;
        root->right->right = splay(root->right->right, key, search_count);
        root = leftRotation(root);
    } else if (root->right->ascii > key) {  // If the key is on the left tree of the right tree, ZAG-ZIG
        root->right->left = splay(root->right->left, key, search_count);
         if (root->right->left != NULL) {
           root->right = rightRotation(root->right);
         }
    }
    (*search_count) += 4;
    if (root->right != NULL) {
      root = leftRotation(root);
    }
    return root;

  } else { // Key is on the left tree
    if (root->left == NULL) { // If left tree doesn't exist, then key isn't on the tree
      (*search_count) += 2;
      return root;
    } else if (root->left->ascii > key) { // If the key is on the left tree of the left tree, ZIG-ZIG
        (*search_count) -= 1;
        root->left->left = splay(root->left->left, key, search_count);
        root = rightRotation(root);
    } else if (root->left->ascii < key) { // If the key is on the right tree of the left tree, ZIG-ZAG
        root->left->right = splay(root->left->right, key, search_count);
        if (root->left->right != NULL) {
          root->left = leftRotation(root->left);
        }
    }
    (*search_count) += 4;
    if (root->left != NULL) {
      root = rightRotation(root);
    }
    return root;

  }
}

tNode* SPLAY_insert(tNode* root, int key, char* morse) {
  int counter = 0;
  /* A splay insertion is just a bst insertion with a splay after it */
  root = BST_insert(root, key, morse);
  root = splay(root, key, &counter);
  return root;
}

char* SPLAY_search(tNode** root, int key, int* search_count) {
  *root = splay((*root), key, search_count);
  (*search_count)++;
  if ((*root)->ascii != key) {
    return NULL;
  } else { 
    return (*root)->morseCode;
  }
}
