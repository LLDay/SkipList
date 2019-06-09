#include <skip_list.h>
#include <simple_list.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

size_t countFileLines(FILE * file) {
    fseek(file, SEEK_SET, 0);
    size_t size = 0;
    int tmp;
    while (fscanf(file, "%d", &tmp) != -1)
        size++;

    return size;
}



int * readFromFile(FILE * file, size_t size) {
    fseek(file, SEEK_SET, 0);

    int * array = malloc(size * sizeof(int));
    
    for (size_t i = 0; i < size; i++)
        if (fscanf(file, "%d", &array[i]) == -1) {
            free(array);
            return NULL;
        }
    return array;
}

void skipListBenchmark(KeyType array[], size_t size, KeyType findValue) {
    clock_t start = clock();
    SkipList skipList = createSkipList(array, size, log2(size));
    printf("SkipList creating time: %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);

    start = clock();
    SkipNode skipNode = skipList_find(skipList, findValue);
    printf("SkipList finding time %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);
    if (skipNode) 
        printf("Founded (%d)\n", findValue);
    else printf("Not founded (%d)\n", findValue);

    start = clock();
    destroySkipList(skipList);
    printf("SkipList destroing time %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);
}



void simpleListBenchmark(ValueType array[], size_t size, ValueType findValue) {
    clock_t start = clock();
    SimpleList simpleList = createSimpleList(array, size);
    printf("SimpleList creating time: %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);

    start = clock();
    SimpleNode simpleNode = simpleList_find(simpleList, findValue);
    printf("SimpleList finding time %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);
    if (simpleNode) 
        printf("Founded (%d)\n", findValue);
    else printf("Not founded (%d)\n", findValue);

    start = clock();
    destroySimpleList(simpleNode);
    printf("SimpleList destroing time %f\n", ((double) clock() - start) / CLOCKS_PER_SEC);
}



int main(int argc, char const *argv[]) {
    if (argc < 3) {
        printf("Missing parameters FILE_NAME FIND_VALUE");
        exit(EXIT_FAILURE);
    }

    const char * fileName = argv[1];
    int value = atoi(argv[2]);

    FILE * file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Wrong file name");
        exit(EXIT_FAILURE);
    }

    size_t size = countFileLines(file);
    int * array = readFromFile(file, size);
    fclose(file);
    
    simpleListBenchmark(array, size, value);
    printf("---------------------\n");
    skipListBenchmark(array, size, value);

    free(array);
    return 0;
}
