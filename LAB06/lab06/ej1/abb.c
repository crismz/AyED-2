#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    bool b = true;
    if (tree != NULL && b) {
        if (tree->left != NULL && b){
            b = elem_less(tree->left->elem,tree->elem);
            invrep(tree->left);
        }
        if (tree->right != NULL && b) {
            b = elem_less(tree->elem,tree->right->elem);
            invrep(tree->right);
        }
    }
    return b;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (abb_is_empty(tree)) {
        tree = malloc(sizeof(struct _s_abb));
        tree->elem = e;
        tree->left = NULL;
        tree->right = NULL;
    } else {
        if (elem_eq(e,tree->elem)){
            assert(invrep(tree) && abb_exists(tree, e));
            return tree;
        }
        if (elem_less(e,tree->elem)){
            tree->left = abb_add(tree->left,e); 
        } else {
            tree->right = abb_add(tree->right,e);
        }
    }
    assert(invrep(tree) && abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    bool is_empty=false;
    assert(invrep(tree));
    is_empty = tree == NULL;
    return is_empty;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        exists = elem_eq(e,tree->elem);
        if (!exists){
            if (elem_less(e,tree->elem)){
            exists = abb_exists(tree->left,e); 
            } else {
            exists = abb_exists(tree->right,e);
            }
        }
    }
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if(!(abb_is_empty(tree))){
        length++;
        length = length + abb_length(tree->left);
        length = length + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) || length > 0));
    return length;
}


abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree));
    if (!abb_is_empty(tree)){
        if (elem_eq(e,tree->elem)){
            abb father;
            abb max;
            max = NULL;
            if (tree->left == NULL){
                if(tree->right == NULL){
                    free(tree);
                    tree = NULL;
                } 
            } else {
                father = tree->left;
                max = father;
                
                while(max->right != NULL){      // Para sacar el máx del arbol izquierdo y su padre
                    father = max;
                    max = max->right;
                }
                tree->elem = max->elem;         
                if (father == max) {
                    tree->left = max->left;     
                } else {
                    father->right = max->left;
                }
                free(max);
            }
        } else {
            if (elem_less(e,tree->elem)){
            tree->left = abb_remove(tree->left,e); 
            } else {
            tree->right = abb_remove(tree->right,e);
            }
        }
    }
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}


abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb tree_max = tree;
    max_e = tree_max->elem;
    while(tree_max->right != NULL){
        tree_max = tree_max->right;
        max_e = tree_max->elem;
    }
    tree_max = NULL;
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    abb tree_min = tree;
    min_e = tree_min->elem;
    while(tree_min->left != NULL){
        tree_min = tree_min->left;
        min_e = tree_min->elem;
    }
    tree_min = NULL;
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        printf("%d ", tree->elem);
        abb_dump(tree->left);
        abb_dump(tree->right);
    }
}

abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if (tree != NULL){
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
    }
    tree = NULL;
    assert(tree == NULL);
    return tree;
}

