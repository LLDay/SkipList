#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef int ValueType;

struct SimpleList {
    struct SimpleList * next;
    ValueType value;
};

typedef struct SimpleList SimpleNodeType;
typedef SimpleNodeType * SimpleList;
typedef SimpleList SimpleNode;

SimpleList createSimpleList(const ValueType arr[], size_t n);

SimpleNode simpleList_find(SimpleList list, const ValueType item);

void destroySimpleList(SimpleList list);