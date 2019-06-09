#include "skip_list.h"
#include "simple_list.h"
#include "stdlib.h"
#include "time.h"

#define CTEST_MAIN

#pragma GCC diagnostic ignored "-Wformat" 
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "ctest.h"
#pragma GCC diagnostic pop


int main(int argc, const char *argv[]) {
    int result = ctest_main(argc, argv);
    return result;
}


CTEST(SKIP_LIST, Create) {
    SkipList a = createEmptySkipList(3);
    ASSERT_NOT_NULL(a->down);
    ASSERT_NOT_NULL(a->down->down);
    ASSERT_NOT_NULL(a->down->down->down);
    ASSERT_NULL(a->down->down->down->down);
    ASSERT_NULL(a->next);
    ASSERT_EQUAL(skipList_size(a), 0);

    KeyType arr[] = {7, 4, 2};
    SkipList b = createSkipList(arr, sizeof(arr) / sizeof(arr[0]), 2);
    if (b->next) 
        ASSERT_EQUAL(b->next->key, b->next->down->key);
    ASSERT_EQUAL(b->down->next->key, 2);
    ASSERT_EQUAL(b->down->next->next->key, 4);
    ASSERT_EQUAL(skipList_size(b), 3);

    SkipList d = createSkipList(NULL, 3, 2);
    SkipList c = createSkipList(arr, 0, 3);

    ASSERT_NULL(d);
    ASSERT_NULL(c);

    destroySkipList(a);
    destroySkipList(b);
}



CTEST(SKIP_LIST, AddRemove) {
    KeyType arr[] = {5, 8, 3, 9, 12, 1, 6, 7, 11, 2, 10, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    SkipList list = createEmptySkipList(2);
    
    for (size_t i = 0; i < size; i++) {
        skipList_add(list, arr[i]);
        ASSERT_EQUAL(skipList_size(list), i + 1);
    }

    ASSERT_EQUAL(list->down->next->key, 1);
    ASSERT_EQUAL(skipList_find(list, 8)->next->key, 9);
    ASSERT_NULL(skipList_find(list, 12)->next);

    for (size_t i = 1; i < size; i++) {
        ASSERT_TRUE(skipList_contains(list, arr[i]));
        ASSERT_TRUE(skipList_remove(list, arr[i]));
        ASSERT_FALSE(skipList_contains(list, arr[i]));
    }

    ASSERT_EQUAL(list->down->down->next->key, 5);

    destroySkipList(list);
}



CTEST(SKIP_LIST, ChangeLevels) {
    KeyType arr[] = {5, 8, 3, 9, 12, 1, 6, 7, 11, 2, 10, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    SkipList oldList = createSkipList(arr, size, 0);
    
    ASSERT_NULL(oldList->down);

    SkipList list = newLevelSkipList(oldList, 2);
    ASSERT_NOT_NULL(list->down->down);
    destroySkipList(oldList);
    
    if (list->next && list->next->key < 12) {
        SkipNode p = list->next;
        KeyType value = p->down->down->key;
        ASSERT_EQUAL(p->key, p->down->key);
        ASSERT_EQUAL(p->key, value);
        ASSERT_EQUAL(value + 1, p->down->down->next->key);
    }

    SkipNode firstLevel = list->down; 
    SkipNode zerolevel = list->down->down;   
    SkipList newlist = newLevelSkipList(list, 1);
    destroySkipList(list);

    ASSERT_TRUE(newlist == firstLevel);
    ASSERT_TRUE(newlist->down == zerolevel);
    destroySkipList(newlist);
}



CTEST(SIMPLE_LIST, All) {
    KeyType arr[] = {5, 8, 3, 9, 12, 1, 6, 7, 11, 2, 10, 4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    SimpleList a = createSimpleList(arr, size);

    SimpleList pointer = a;
    for (size_t i = 0; i < size; i++) {
        ASSERT_EQUAL(pointer->value, arr[i]);
        pointer = pointer->next;
    }
    ASSERT_NULL(pointer);

    ASSERT_NULL(simpleList_find(a, 13));
    ASSERT_NULL(simpleList_find(a, 4)->next);

    ASSERT_EQUAL(simpleList_find(a, 12)->next->value, 1);

    destroySimpleList(a);
}