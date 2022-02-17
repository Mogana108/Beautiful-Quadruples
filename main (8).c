#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 0
#define X 1
#define Y 2
#define Z 3
#define MAX 4096


char* readline();
char** split_string(char*);

void insert(int * arr, int count, int value) {
    int i;
    for (i = count - 1; i >= 0 && arr[i] > value; i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = value;
}

int min(int a, int b) {
    return a < b ? a : b;
}

/*
 * Complete the beautifulQuadruples function below.
 */
long beautifulQuadruples(int _w, int _x, int _y, int _z) {
    /*
     * Write your code here.
     */
    int sortedInput[4];
    unsigned long * count;
    unsigned long numPairs = 0;
    unsigned long numBeautiful = 0;
    
    insert(sortedInput, 0, _w);
    insert(sortedInput, 1, _x);
    insert(sortedInput, 2, _y);
    insert(sortedInput, 3, _z);
    
    count = (unsigned long *)calloc(MAX, sizeof(unsigned long));
    if (count == NULL) { return - 1; }
    
    for (int y = 1; y <= sortedInput[Y]; y++) {
        for (int z = y; z <= sortedInput[Z]; z++) {
            count[y ^ z]++;
            numPairs++;
        }
    }

    for (int x = 1; x <= sortedInput[X]; x++) {
        for (int w = 1; w <= min(x, sortedInput[W]); w++) {
            numBeautiful += numPairs - count[x ^ w];
        }
        
        // remove pairs (x, z)
        for (int z = x; z <= sortedInput[Z]; z++) {
            count[x ^ z]--;
        }
        numPairs -= (sortedInput[Z] - x + 1);
    }
    
    return numBeautiful;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** abcd = split_string(readline());

    char* a_endptr;
    char* a_str = abcd[0];
    int a = strtol(a_str, &a_endptr, 10);

    if (a_endptr == a_str || *a_endptr != '\0') { exit(EXIT_FAILURE); }

    char* b_endptr;
    char* b_str = abcd[1];
    int b = strtol(b_str, &b_endptr, 10);

    if (b_endptr == b_str || *b_endptr != '\0') { exit(EXIT_FAILURE); }

    char* c_endptr;
    char* c_str = abcd[2];
    int c = strtol(c_str, &c_endptr, 10);

    if (c_endptr == c_str || *c_endptr != '\0') { exit(EXIT_FAILURE); }

    char* d_endptr;
    char* d_str = abcd[3];
    int d = strtol(d_str, &d_endptr, 10);

    if (d_endptr == d_str || *d_endptr != '\0') { exit(EXIT_FAILURE); }

    long result = beautifulQuadruples(a, b, c, d);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
