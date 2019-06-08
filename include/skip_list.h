#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define SKIP_MIN INT_MIN
typedef int KeyType;

struct SkipNode {
    struct SkipNode * next;
    struct SkipNode * down;
    KeyType key;
}; 

typedef struct SkipNode SkipNodeType;
typedef SkipNodeType * SkipNode;
typedef SkipNode SkipList;

#pragma GCC diagnostic ignored "-Wunused-function"

static int snComp(const void * elem1, const void * elem2) {
    int f = *((KeyType *)elem1);
    int s = *((KeyType *)elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

#pragma GCC diagnostic pop

SkipList createSkipList(const KeyType * items, size_t n, size_t lvls);

SkipList createEmptySkipList(size_t lvls);

SkipNode skipList_find(SkipList list, KeyType value);

SkipList newLevelSkipList(SkipList list, size_t lvl);

void destroySkipList(SkipList list);

bool skipList_add(SkipList list, KeyType item);

bool skipList_remove(SkipList list, KeyType item);

bool skipList_contains(SkipList list, KeyType item);

size_t skipList_size(SkipList list);
