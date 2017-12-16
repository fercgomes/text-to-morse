#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "splay.h"

/* TODO: @DANIEL
 * Documentar essa parte um pouco melhor */

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
  if (root == NULL) {
   return NULL;
  } else if (root->ascii == key) {
    (*search_count) += 1;
    return root;
  } else if (root->ascii < key) { // Zag
    if (root->right == NULL) {
      (*search_count) += 2;
        return root;
    } else if (root->right->ascii < key) { // Zag-zag
        (*search_count) -= 1;
        root->right->right = splay(root->right->right, key, search_count);
        root = leftRotation(root);
    } else if (root->right->ascii > key) {  // Zag-zig
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

  } else { // Zig
    if (root->left == NULL) {
      (*search_count) += 2;
      return root;
    } else if (root->left->ascii > key) { //Zig-zig
        (*search_count) -= 1;
        root->left->left = splay(root->left->left, key, search_count);
        root = rightRotation(root);
    } else if (root->left->ascii < key) { //Zig-zag
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
