#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static bool invrep(dict_t d) {
    bool b = true;
    if (d != NULL && b){
        if (d->left != NULL && b){
            b = key_less(d->left->key,d->key);
            invrep(d->left);
        }
        if (d->right != NULL && b){
            b = key_less(d->key,d->right->key);
            invrep(d->right);
        } 
    }

    return b;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    if (dict == NULL){
        dict = malloc(sizeof(struct _node_t));
        dict->key = word;
        dict->value = def;
        dict->left = NULL;
        dict->right = NULL;
    } else if (key_less(dict->key,word)){
        dict->right = dict_add(dict->right,word,def);
    } else if (key_less(word,dict->key)){
        dict->left = dict_add(dict->left,word,def);
    } else if (key_eq(dict->key,word)){
        value_t destroy = dict->value;
        key_t destroy_k = dict->key;
        dict->value = def;
        dict->key = word;
        value_destroy(destroy);
        key_destroy(destroy_k);
    }

    assert(invrep(dict) && key_eq(def,dict_search(dict,word)));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def=NULL;
    assert(invrep(dict));
    if (dict != NULL){
        if (key_eq(word, dict->key)){
            def = dict->value;
        } else if (key_less(word,dict->key)){
            def = dict_search(dict->left,word);
        } else if (key_less(dict->key,word)){
            def = dict_search(dict->right,word);
        }
    }
    assert(((def != NULL) == dict_exists(dict,word)));
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    assert(invrep(dict));
    bool exists = false;
    if (dict != NULL){
        if (key_eq(word,dict->key)){ 
            exists = true;
        } else if (key_less(word,dict->key)){
            exists = dict_exists(dict->left,word);
        } else if (key_less(dict->key,word)){
            exists = dict_exists(dict->right,word);
        }
    }
    assert(invrep(dict));
    return exists;
}

unsigned int dict_length(dict_t dict) {
    assert(invrep(dict));
    unsigned int counter = 0;

    if (dict != NULL){
        counter++;
        counter = counter + dict_length(dict->left);
        counter = counter + dict_length(dict->right);
    }
    return counter;
}

dict_t dict_remove(dict_t dict, key_t word) {
    assert(invrep(dict));
    if (dict != NULL){
        if (key_eq(word,dict->key)){
            dict_t father;
            dict_t max;
            max = NULL;
            if (dict->left == NULL){
                if(dict->right == NULL){
                    key_destroy(dict->key);
                    value_destroy(dict->value);
                    free(dict);
                    dict = NULL;
                } 
            } else {
                father = dict->left;
                max = father;
                
                while(max->right != NULL){      // Para sacar el máx del arbol izquierdo y su padre
                    father = max;
                    max = max->right;
                }
                dict->key = max->key;
                dict->value = max->value;         
                if (father == max) {
                    dict->left = max->left;     
                } else {
                    father->right = max->left;
                }
                key_destroy(max->key);
                value_destroy(max->value);
                free(max);
            }
        } else {
            if (key_less(word,dict->key)){
            dict->left = dict_remove(dict->left,word); 
            } else {
            dict->right = dict_remove(dict->right,word);
            }
        }
    }

    assert(invrep(dict) && !dict_exists(dict,word));
    return dict;
}

dict_t dict_remove_all(dict_t dict) {
    assert(invrep(dict));
    if (dict != NULL){
        dict_remove_all(dict->left);
        dict_remove_all(dict->right);
        key_destroy(dict->key);
        value_destroy(dict->value);
        free(dict);
        dict = NULL;
    }
    assert(invrep(dict) && dict_length(dict) == 0);
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict) && file != NULL);
    if (dict != NULL){
        dict_dump(dict->left,file);
        fprintf(file,"%s: %s\n", string_ref(dict->key),string_ref(dict->value));
        dict_dump(dict->right,file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    assert(dict == NULL);
    return dict;
}

