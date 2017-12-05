#include "splaytree.h"

tNode* splayCreate() {
  return NULL;
}

void splayDelete(tNode* root) {
  if (root != NULL) {
    splayDelete(root->leftChild);
    splayDelete(root->rightChild);
    free(root);
  }
}

tNode* rightRotation(tNode* root) {
  tNode* aux = root->leftChild;
  root->leftChild = aux->rightChild;
  aux->rightChild = root;
  return aux;
}

tNode* leftRotation(tNode* node) {
  tNode* aux = root->rightChild;
  root->rightChild = aux->leftChild;
  aux->leftChild = root;
  return aux;
}

tNode* splay(tNode* root, int key) {
  if (root == NULL || node->ascii == key) {
    return root;
  } else if (root->ascii < key) {
      if (root->rightChild == NULL) {
        return root;
      } else if (root->rightChild->key < key) {
        root->rightChild->rightChild = splay(root->rightChild->rightChild, key);
        root->rightChild = leftRotation(root->rightChild);
      } else if (root->rightChild->key > key) {
        root->rightChild->leftChild = splay(root->rightChild->leftChild, key);
        root->rightChild = rightRotation(root->rightChild);
      }
      return leftRotation(root);
  } else {
    if (root->leftChild == NULL) {
      return root;
    } else if (root->leftChild->key > key) {
        root->leftChild->leftChild = splay(root->leftChild->leftChild, key);
        root->leftChild = rightRotation(root->leftChild);
    } else if (root->leftChild->key < key) {
        root->leftChild->rightChild = splay(root->leftChild->rightChild, key);
        root->leftChild = leftRotation(root->leftChild);
    }
    return rightRotation(root);
  }
}

tNode* insert(tNode* root, int key, char* morse) {
  tNode* aux;
  if (root == NULL) {
    aux = (tNode*)malloc(sizeof(tNode));
    aux->morseCode = morse;
    aux->ascii = key;
    aux->leftChild = NULL;
    aux->rightChild = NULL;
    return aux;
  } else {
    aux = root;
    while (aux != NULL) {
      if (aux->ascii > key) {
        aux = aux->leftChild;
      } else {
        aux = aux->rightChild;
      }
    }
    aux = insert(aux, key, morse);
    return splay(root, key);
  }
}

