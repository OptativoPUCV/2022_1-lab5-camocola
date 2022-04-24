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
    TreeMap * newTree = (TreeMap*) malloc(sizeof(TreeMap));
    if (newTree == NULL) return NULL;
    newTree->root = NULL;
    newTree->current = NULL;
    newTree->lower_than = lower_than;
    return newTree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* aux=tree->root;
    int Key = *(int*)(key);
    while (aux != NULL)
    {
        int auxKey= *(int*)(aux->pair->key);
        if (auxKey == Key)
        {
            //llave repetida
            return;
        }
        if (tree->lower_than(key,aux->pair->key)==1)
        {
            //1 si key1<key2
            if (aux->left == NULL)
            {
                TreeNode* nuevoNodo = createTreeNode(key, value);
                aux->left = nuevoNodo;
                nuevoNodo->parent = aux;
                tree->current = nuevoNodo;
                return;
            }
            aux = aux->left;
        }
        else
        {
            //0 si key1>key2
            if (aux->right == NULL)
            {
                TreeNode* nuevoNodo = createTreeNode(key, value);
                aux->right = nuevoNodo;
                nuevoNodo->parent = aux;
                tree->current = nuevoNodo;
                return;
            }
            aux = aux->right;
        }
    }
    return ;
}

TreeNode * minimum(TreeNode * x){
    while (x != NULL)
    {
        if (x->left != NULL)
        {
            x = x->left;
        }
        else
        {
            return x;
        }
    }
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode* aux=tree->root;
    int nodeKey = *(int*)(node->pair->key);
    while (aux != NULL)
    {
        int auxKey= *(int*)(aux->pair->key);
        if (auxKey == nodeKey)
        {
            //nodo a eliminar encontrado

            //nodo sin hijos
            if (aux->left == NULL && aux->right == NULL )
            {
                if (aux->parent->left == aux)
                {
                    aux->parent->left = NULL;
                }
                else
                {
                    aux->parent->right = NULL;
                }
                free(aux);
                aux = NULL;
            }
            //nodo con 1 hijo
            else if (aux->left != NULL && aux->right == NULL)
            {
                if (aux->parent->left == aux)
                {
                    aux->parent->left = aux->left;
                }
                else
                {
                    aux->parent->right = aux->left;
                }
                //aux->left->parent = aux->parent;
                free(aux);
                aux = NULL;
            }
            else if (aux->left == NULL && aux->right != NULL)
            {
                if (aux->parent->left == aux)
                {
                    aux->parent->left = aux->right;
                }
                else
                {
                    aux->parent->right = aux->right;
                }
                //aux->right->parent = aux->parent;
                free(aux);
                aux = NULL;
            }

            //nodo con 2 hijos

        }
        else if (tree->lower_than(node->pair->key,aux->pair->key)==1)
        {
            //1 si key1<key2
            aux = aux->left;
        }
        else{
            //0 si key1>key2
            aux = aux->right;
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
    TreeNode* aux=tree->root;
    int Key = *(int*)(key);
    while (aux != NULL)
    {
        int auxKey= *(int*)(aux->pair->key);
        if (auxKey == Key)
        {
            tree->current = aux;
            return aux->pair;
        }
        if (tree->lower_than(key,aux->pair->key)==1)
        {
            //1 si key1<key2
            aux = aux->left;
        }
        else{
            //0 si key1>key2
            aux = aux->right;
        }
    }
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
