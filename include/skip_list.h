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

// Возвращает список пропусков, составленный из массива размерности n
SkipList createSkipList(const KeyType * items, size_t n, size_t lvls);

// Возвращает пустой список (содержит элементы head)
SkipList createEmptySkipList(size_t lvls);

// Возвращает тот же список с другим количеством слоев
SkipList skipList_changeLvl(SkipList list, size_t newLvl);

// Находит узел на нулевом слое
SkipNode skipList_find(SkipList list, KeyType value);

// Удаляет список
void destroySkipList(SkipList list);

// Добавляет элемент в список
void skipList_add(SkipList list, KeyType item);

// Удаляет элемент из списка
bool skipList_remove(SkipList list, KeyType item);

// Проверяет, содержится ли элемент в списке
bool skipList_contains(SkipList list, KeyType item);

// Находит количество элементов нижнего слоя
size_t skipList_size(SkipList list);
