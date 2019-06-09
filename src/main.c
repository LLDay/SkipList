#include <stdio.h>

int main(int argc, char const *argv[]) {
    FILE * sample = fopen("../sample.txt", 'r');
    

    fclose(sample);
    return 0;
}
