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



bool addOrNot(size_t lvl) {
    if (!lvl)
        return true;
    return rand() % (lvl + 1);
}



size_t levelsSize(SkipList list) {
    SkipList pointer = list;
    size_t size = 0;
    
    while (pointer) {
        pointer = pointer->down;
        size++;
    }

    return size - 1;
}



bool isUniqueElems(const KeyType arr[], size_t n) {
    for (size_t i = 0; i < n; i++)
        for (size_t j = i + 1; j < n; j++)
            if (arr[i] == arr[j])
                return false;
    return true;
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

    KeyType * arr = malloc(sizeof(KeyType) * n);  
    memcpy(arr, items, n * sizeof(KeyType));
    qsort(arr, n, sizeof(KeyType), comp);

    SkipList root = allocateNode();
    root->key = SKIP_MIN;
    
    SkipNode pointer = root;
    for (size_t i = 0; i < n; i++) {
        pointer->next = allocateNode();
        pointer = pointer->next;
        pointer->key = arr[i];
    }   

    free(arr);
    return newLevelSkipList(root, lvls);
}



SkipList createEmptySkipList(size_t lvls) {
    SkipList root = allocateNode();
    root->key = SKIP_MIN;
    return newLevelSkipList(root, lvls);
}



void destroyLine(SkipNode list) {
    SkipNode pointer = list;
    SkipNode deleteItem;

    while(pointer) {
        deleteItem = pointer;
        pointer = pointer->next;
        free(deleteItem);
        deleteItem = NULL;
    }
}



void destroySkipList(SkipList list) {
    SkipList pointer = list;
    SkipList deleteLine;

    while (pointer) {
        deleteLine = pointer;
        pointer = pointer->down;
        destroyLine(deleteLine);
    }
}



SkipNode addLevel(SkipNode down, size_t lvlNum) {
    SkipNode newRoot = allocateNode();
    newRoot->down = down;
    newRoot->key = SKIP_MIN;

    SkipNode pUp = newRoot;
    SkipNode pDown = down->next;

    while (pDown) {
        if (addOrNot(lvlNum)) {
            pUp->next = allocateNode();
            pUp = pUp->next;
            pUp->key = pDown->key;
            pUp->down = pDown;
        }
        pDown = pDown->next;
    }

    return newRoot;
}



SkipList newLevelSkipList(SkipList list, size_t newLvl) {
    size_t lvl = levelsSize(list);
    if (lvl == newLvl)
        return list;

    SkipNode root = list;
    for (size_t i = lvl + 1; i <= newLvl; i++)
        root = addLevel(root, i);

    SkipNode delete;
    for (size_t i = lvl; i > newLvl; i--) {
        delete = root;
        root = root->down;
        destroyLine(delete);
    }

    return root;
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



SkipNode descendAdd(SkipNode node, KeyType item, size_t lvl) {
    SkipNode nearest = getNearestNode(node, item);
    SkipNode addedNode;

    if (nearest->down)
        addedNode = descendAdd(nearest->down, item, lvl - 1);

    else {
        SkipNode newNode = allocateNode();
        newNode->next = nearest->next;
        newNode->key = item;
        nearest->next = newNode;
        return newNode;
    }

    if (addOrNot(lvl) && addedNode) {
        SkipNode newNode = allocateNode();
        newNode->next = nearest->next;
        newNode->key = item;
        newNode->down = addedNode;
        nearest->next = newNode;
        return newNode;
    }

    return NULL;
}



bool skipList_add(SkipList list, KeyType item) {
    if (skipList_contains(list, item))
        return false;

    descendAdd(list, item, levelsSize(list));
    return true;
}



bool skipList_remove(SkipList list, KeyType item) {
    SkipNode preDelete = NULL;
    SkipNode pointer = list;

    while (!preDelete) {
        if (pointer == NULL)
            return false;

        while (pointer->next && pointer->next->key < item)
            pointer = pointer->next;
        
        if (pointer->next && pointer->next->key == item)
            preDelete = pointer;

        pointer = pointer->down;
    }

    SkipNode delete = preDelete->next;
    preDelete->next = delete->next;
    free(delete);
    delete = NULL;
   
    if (preDelete->down)
        return skipList_remove(preDelete->down, item);
    
    return true;
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
