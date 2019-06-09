#include <simple_list.h>
#include <stdlib.h>
#include <memory.h>

SimpleNode simpleAllocateNode() {
    SimpleNode node = malloc(sizeof(SimpleNodeType));
    if (node == NULL)
        exit(EXIT_FAILURE);
    node->next = NULL;
    node->value = 0;
    return node;
}



SimpleList createSimpleList(const ValueType arr[], size_t n) {
    if (n == 0 || arr == NULL)
        return NULL;

    SimpleNode root = simpleAllocateNode();
    root->value = arr[0];

    SimpleNode pointer = root;
    for (size_t i = 1; i < n; i++) {
        pointer->next = simpleAllocateNode();
        pointer = pointer->next;
        pointer->value = arr[i];
    }

    return root;
}



SimpleNode simpleList_find(SimpleList list, const ValueType item) {
    while (list) {
        if (list->value == item)
            return list;

        list = list->next;
    }
    return NULL;
}



void destroySimpleList(SimpleList list) {
    SimpleNode pointer = list;
    SimpleNode delete;

    while (pointer) {
        delete = pointer;
        pointer = pointer->next;
        free(delete);
        delete = NULL;
    }
}