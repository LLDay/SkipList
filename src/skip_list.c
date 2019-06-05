#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

#include "skip_list.h"

SkipNode allocateNode() {
    SkipNode node = malloc(sizeof(SkipNodeType));
    if (node == NULL)
        exit(EXIT_FAILURE);
    node->down = NULL;
    node->next = NULL;
    node->key = 0;
    return node;
}


int comp(const void * elem1, const void * elem2) {
    int f = *((KeyType *)elem1);
    int s = *((KeyType *)elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}



bool isPut(size_t lvl) {
    return rand() % (lvl + 1);
}



bool isUniqueElems(const KeyType arr[], size_t n) {
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++)
            if (arr[i] == arr[j])
                return false;
    return true;
}


void fillSkipList(SkipList root, const KeyType * arr, size_t n, size_t current_lvl) {
    if (current_lvl) {
        SkipNode down = allocateNode(); 
        root->down = down;
        root->key = arr[0];
        fillSkipList(root->down, arr, n, current_lvl - 1);
    }
    
    SkipNode pointer = root;
    if (!current_lvl) {
        // for bottom layer 
        for (size_t i = 0; i < n - 1; i++) {
            pointer->key = arr[i];
            pointer->next = allocateNode();
            pointer = pointer->next;
        }
        // for last iteration
        pointer->key = arr[n - 1];
    }

    else {
        SkipNode downPointer = root->down->next;
        // first elems of each layer are same
        while (downPointer) {
            if (isPut(current_lvl)) {
                pointer->next = allocateNode();
                pointer = pointer->next;
                pointer->down = downPointer;
                pointer->key = downPointer->key;
            }
            downPointer = downPointer->next;
        }
    }
}


SkipNode getBottom(SkipNode node) {
    SkipNode pointer = node;
    while(pointer->down)
        pointer = pointer->down;
    
    return pointer;
}


SkipList createSkipList(const KeyType items[], size_t n, size_t lvls) {
    if (n == 0 || items == NULL || !isUniqueElems(items, n))
        return NULL;

    KeyType * arr = malloc(sizeof(KeyType) * (n + 1));  
    memcpy(arr, items, n * sizeof(KeyType));
    arr[n] = SKIP_MIN;
    qsort(arr, n + 1, sizeof(KeyType), comp);

    SkipList root = allocateNode();
    fillSkipList(root, arr, n + 1, lvls);
    free(arr);
    return root;
}


void destroyLine(SkipList root) {
    SkipNode pointer = root;
    SkipNode deleteItem;

    while(pointer) {
        deleteItem = pointer;
        pointer = pointer->next;
        free(deleteItem);
        deleteItem = NULL;
    }
}


void destroySkipList(SkipList root) {
    SkipList pointer = root;
    SkipList deleteLine;

    while (pointer) {
        deleteLine = pointer;
        pointer = pointer->down;
        destroyLine(deleteLine);
    }
}

SkipNode getNearestNode(SkipList list, KeyType value) {
    SkipNode pointer = list; 
    while (pointer->next && pointer->next->key <= value)
        pointer = pointer->next;
    return pointer;
}

SkipNode skipList_find(SkipList list, KeyType value) {
    SkipNode pointer = getNearestNode(list, value);

    if (pointer->key == value)
        return getBottom(pointer);

    if (!pointer->down)
        return NULL;

    return skipList_find(pointer->down, value);
}


bool skipList_add(SkipList list, KeyType item) {
    
}



bool skipList_remove(SkipList list, KeyType item) {

}



bool skipList_contains(SkipList list, KeyType item) {
    return skipList_find(list, item) != NULL;
}



size_t skipList_size(SkipList list) {
    SkipNode bottom = getBottom(list);
    size_t size = 0;

    while (bottom->next) {
        bottom = bottom->next;
        size++;
    }

    return size;
}