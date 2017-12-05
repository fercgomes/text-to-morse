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

tNode* rightRotation(tNode* node) {
  
  node->parent->leftChild = node->rightChild;
  node->rightChild->parent = node->parent;
  node->rightChild = node->parent;
  node->parent = node->rightChild->parent;
  node->rightChild->parent = node;
  return node;
}

tNode* leftRotation(tNode* node) {
  node->parent->rightChild = node->leftChild;
  node->leftChild->parent = node->parent;
  node->leftChild = node->parent;
  node->parent = node->leftChild->parent;
  node->leftChild->parent = node;
  return node;
}

tNode* splay(tNode* root, int key) {
  if (root == NULL || node->ascii == key) {
    return root;
  } else if (root->ascii < key) {
      if (root->rightChild == NULL) {
        return root;
      } else if (root->rightChild->key < key) {
        root->rightChild->rightChild = splay(root->rightChild->rightChild, key);
        root->rightChild = leftRotation(root->rightChild->rightChild);
      } else if (root->rightChild->key > key) {
        root->rightChild->leftChild = splay(root->rightChild->leftChild, key);
        root->rightChild = rightRotation(root->rightChild->leftChild);
      }
      return leftRotation(root->rightChild);
  } else {
    if (root->leftChild == NULL) {
      return root;
    } else if (root->leftChild->key > key) {
        root->leftChild->leftChild = splay(root->leftChild->leftChild, key);
        root->leftChild = rightRotation(root->leftChild->leftChild);
    } else if (root->leftChild->key < key) {
        root->leftChild->rightChild = splay(root->leftChild->rightChild, key);
        root->leftChild = leftRotation(root->leftChild->rightChild);
    }
    return rightRotation(root->leftChild);
  }
}

tNode* insert(tNode* root, int key, char* morse) {
  tNode* aux;
  if (root == NULL) {
    aux = (tNode*)malloc(sizeof(tNode));
    aux->morseCode = morse;
    aux->ascii = key;
    aux->parent = NULL;
    aux->leftChild = NULL;
    aux->rightChild = NULL;
  } else {
    root = splay(root, key);
    if (root->key == key) {
      return root;
    } else {
      aux = (tNode*)malloc(sizeof(tNode));
      aux->morseCode = morse;
      aux->ascii = key;
      aux->parent = NULL;
      if (root->key < key) {
        aux->leftChild = root;
        aux->leftChild->parent = aux;
        aux->rightChild = root->rightChild;
        aux->rightChild->parent = aux;
        root->rightChild = NULL;
      } else {
        aux->rightChild = root;
        aux->rightChild->parent = aux;
        aux->leftChild = root->leftChild;
        aux->leftChild->parent = aux;
        root->leftChild = NULL;
      }
    }
  }
  return aux;
}

