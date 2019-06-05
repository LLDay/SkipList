#include "skip_list.h"
#include "stdlib.h"
#include "time.h"

int main() {
    srand(time(NULL));

    KeyType a[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    SkipList list = createSkipList(a, sizeof(a) / sizeof(a[0]), 2);
    skipList_remove(list, 4);
    printf("%d", skipList_contains(list, 4));
    destroySkipList(list);
    return 0;
}