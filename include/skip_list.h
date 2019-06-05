#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef int KeyType;

struct SkipNode {
    struct SkipNode * next;
    struct SkipNode * down;
    KeyType key;
}; 

typedef struct SkipNode SkipNodeType;
typedef SkipNodeType * SkipNode;
typedef SkipNode SkipList;

struct HeadNode {
    SkipNode next;
    SkipNode down;
};

typedef struct HeadNode HeadNodeType;
typedef HeadNodeType * HeadNode;


SkipList createSkipList(const KeyType * items, size_t n, size_t lvls);

SkipNode skipList_find(SkipList list, KeyType value);

void destroySkipList(SkipList root);

bool skipList_add(SkipList list, KeyType item);

bool skipList_remove(SkipList list, KeyType item);

bool skipList_contains(SkipList list, KeyType item);

size_t skipList_size(SkipList list);
