#include <skip_list.h>
#include <simple_list.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <memory.h>


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

    int * array = malloc(size * sizeof(*array));
    
    for (size_t i = 0; i < size; i++)
        if (fscanf(file, "%d", &array[i]) == -1) {
            free(array);
            return NULL;
        }
    return array;
}

void skipListBenchmark(FILE * to, KeyType array[], size_t size, KeyType findValues[], size_t count) {
    clock_t start = clock();
    SkipList skipList = createSkipList(array, size, log2(size));

    clock_t creatingTime = clock() - start;
    fprintf(to, "SkipList creating time: %ldms\n", 1000 * creatingTime / CLOCKS_PER_SEC);

    fprintf(to, "SkipList finding:\n");

    clock_t findingTime = 0;
    for (size_t i = 0; i < count; i++) {
        start = clock();
        SkipNode skipNode = skipList_find(skipList, findValues[i]);
        long int delta = clock() - start;
        findingTime += delta;
        if (skipNode) 
            fprintf(to, "Founded %d \t(%ldms)\n", findValues[i], 1000 * delta / CLOCKS_PER_SEC);
        else fprintf(to, "Not founded %d \t(%ldms)\n", findValues[i], 1000 * delta / CLOCKS_PER_SEC);
    }

    start = clock();
    destroySkipList(skipList);
    clock_t destroingTime = clock() - start;
    fprintf(to, "SkipList destroing time\t %ldms\n", 1000 * destroingTime / CLOCKS_PER_SEC);
    fprintf(to, "SkipList finding time:\t %ldms\n", 1000 * findingTime / CLOCKS_PER_SEC);
}



void simpleListBenchmark(FILE * to, ValueType array[], size_t size, ValueType findValues[], size_t count) {
    clock_t start = clock();
    SimpleList simpleList = createSimpleList(array, size);
    
    clock_t creatingTime = clock() - start;
    fprintf(to, "SimpleList creating time: %ldms\n", 1000 * creatingTime / CLOCKS_PER_SEC);

    fprintf(to, "SimpleNode finding:\n");
    clock_t findingTime = 0;
    for (size_t i = 0; i < count; i++) {
        start = clock();
        SimpleNode simpleNode = simpleList_find(simpleList, findValues[i]);
        long int delta = clock() - start;
        findingTime += delta;

        if (simpleNode) 
            fprintf(to, "Founded %d \t(%ldms)\n", findValues[i], 1000 * delta / CLOCKS_PER_SEC);
        else fprintf(to, "Not founded %d \t(%ldms)\n", findValues[i], 1000 * delta / CLOCKS_PER_SEC);
    }

    start = clock();
    destroySimpleList(simpleList);
    clock_t destroingTime = clock() - start;
    fprintf(to, "SimpleList destroing time\t %ldms\n", 1000 * destroingTime / CLOCKS_PER_SEC);
    fprintf(to, "SimpleList finding time:\t %ldms\n", 1000 * findingTime / CLOCKS_PER_SEC);
}


int * getValuesFromCmd(size_t argc, char const *argv[]) {
    int * arr = malloc(sizeof(*arr) * (argc - 3));

    for (size_t i = 3; i < argc; i++) 
        arr[i - 3] = atoi(argv[i]);

    return arr;
}


int main(int argc, char const *argv[]) {
    if (argc < 4) {
        printf("Required parameters: from_name to_name value1 [value 2 [...]]");
        exit(EXIT_FAILURE);
    }

    const char * fromName = argv[1];
    const char * toName = argv[2];
    FILE * from = fopen(fromName, "r");

    if (from == NULL) {
        printf("Wrong file name");
        exit(EXIT_FAILURE);
    }

    size_t size = countFileLines(from);
    int * array = readFromFile(from, size);
    fclose(from);
    

    FILE * to = fopen(toName, "w");
    int * values = getValuesFromCmd(argc, argv);
    simpleListBenchmark(to, array, size, values, argc - 3);
    fprintf(to, "\n\n");
    skipListBenchmark(to, array, size, values, argc - 3);
    fclose(to);

    free(array);
    free(values);

    return 0;
}
