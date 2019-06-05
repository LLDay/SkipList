#include "skip_list.h"
#include "stdlib.h"
#include "time.h"

int main() {
    srand(time(NULL));

    KeyType a[] = {4, 2, 7, 1, 6, 9, 3, 8, 5};
    SkipList list = createSkipList(a, sizeof(a) / sizeof(a[0]), 2);
    SkipNode b = skipList_find(list, 8);
    destroySkipList(list);
    return 0;
}