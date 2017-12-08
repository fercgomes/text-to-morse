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

tNode* splay(tNode* root, int key) {
  if (root == NULL || root->ascii == key) {
    return root;
  } else if (root->ascii < key) {
      if (root->right == NULL) {
        return root;
      } else if (root->right->ascii < key) {
        root->right->right = splay(root->right->right, key);
        root->right = leftRotation(root->right);
      } else if (root->right->ascii > key) {
        root->right->left = splay(root->right->left, key);
        root->right = rightRotation(root->right);
      }
      return leftRotation(root);
  } else {
    if (root->left == NULL) {
      return root;
    } else if (root->left->ascii > key) {
        root->left->left = splay(root->left->left, key);
        root->left = rightRotation(root->left);
    } else if (root->left->ascii < key) {
        root->left->right = splay(root->left->right, key);
        root->left = leftRotation(root->left);
    }
    return rightRotation(root);
  }
}

tNode* SPLAY_insert(tNode* root, int key, char* morse) {
  tNode* aux;
  if (root == NULL) {
    aux = (tNode*)malloc(sizeof(tNode));
    aux->morseCode = morse;
    aux->ascii = key;
    aux->left = NULL;
    aux->right = NULL;
    return aux;
  } else {
    aux = root;
    while (aux != NULL) {
      if (aux->ascii > key) {
        aux = aux->left;
      } else {
        aux = aux->right;
      }
    }
    aux = SPLAY_insert(aux, key, morse);
    return splay(root, key);
  }
}

