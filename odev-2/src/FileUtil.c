#include "FileUtil.h"

int *splitToIntegers(char *str, int *size) {
    int count = 0;
    int *numbers = NULL;
    char *token = strtok(str, " ");
    
    while (token != NULL) {
        numbers = (int *)realloc(numbers, (count + 1) * sizeof(int));
        if (numbers == NULL) {
            printf("Memory reallocation failed\n");
            exit(1);
        }
        numbers[count++] = atoi(token);
        token = strtok(NULL, " ");
    }

    *size = count;
    return numbers;
}

int **ReadFile(char *filename, int *rowCount) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("File does not exist.\n");
        exit(1);
    }

    int **array = NULL;
    *rowCount = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, f)) != -1) {
        int size;
        int *numbers = splitToIntegers(line, &size);

        array = (int **)realloc(array, (*rowCount + 1) * sizeof(int *));
        if (array == NULL) {
            printf("Memory reallocation failed\n");
            exit(1);
        }

        array[(*rowCount)++] = numbers;
    }

    fclose(f);
    if (line)
        free(line);

    return array;
}
