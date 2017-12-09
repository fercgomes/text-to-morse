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
  if (root == NULL || root->ascii == key) {
    (*search_count) += 1;
    return root;
  } else if (root->ascii < key) {
    if (root->right == NULL) {
      (*search_count) -= 2;
        return root;
    } else if (root->right->ascii < key) {
        (*search_count) -= 1;
        root->right->right = splay(root->right->right, key, search_count);
        root->right = leftRotation(root->right);
    } else if (root->right->ascii > key) { 
        root->right->left = splay(root->right->left, key, search_count);
        root->right = rightRotation(root->right);
    }
    (*search_count) += 5;
    return leftRotation(root);
  } else {
    if (root->left == NULL) {
      (*search_count) -= 2;
      return root;
    } else if (root->left->ascii > key) {
        (*search_count) -= 1;
        root->left->left = splay(root->left->left, key, search_count);
        root->left = rightRotation(root->left);
    } else if (root->left->ascii < key) {
        root->left->right = splay(root->left->right, key, search_count);
        root->left = leftRotation(root->left);
    }
    (*search_count) -= 5;
    return rightRotation(root);
  }
}

tNode* SPLAY_insert(tNode* root, int key, char* morse) {
  root = BST_insert(root, key, morse);
  return splay(root, key);
}

char* SPLAY_search(tNode* root, int key, int* search_count) {
  root = splay(root, key, search_count);
  (*search_count)++;
  if (root->ascii == key) {
    return root->morseCode;
  } else { 
    return NULL;
}
