#include "Habitat.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 // Maximum expected line length (adjust as needed)

int **GenerateHabitat(const char *filename, int *num_rows, int *num_cols)
{
    FILE *file;
    char *line = NULL;
    size_t line_size = 0;
    ssize_t read;

    int rows = 0, cols = -1;
    // Open the file
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        return NULL;
    }

    // Read and process each line
    while ((read = getline(&line, &line_size, file)) != -1)
    {
        // Remove trailing newline, if present
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Count columns in this line
        int current_cols = 0;
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            current_cols++;
            token = strtok(NULL, " ");
        }

        // Update rows and columns if necessary
        rows++;
        if (cols == -1)
        { // First line: initialize cols
            cols = current_cols;
        }
        else
        {
            if (current_cols != cols)
            {
                fprintf(stderr, "Warning: Inconsistent number of columns in line %d.\n", rows);
                // You may choose to handle inconsistent column counts here
            }
        }
    }

    // Close the file
    fclose(file);

    // Free line memory
    free(line);

    // Allocate memory for the return array (after successful parsing)
    int **array = (int **)malloc(rows * sizeof(int *));
    if (array == NULL)
    {
        fprintf(stderr, "Error allocating memory for the 2D array.\n");
        return NULL;
    }

    // Allocate memory for each inner array (dynamic allocation)
    for (int i = 0; i < rows; i++)
    {
        array[i] = (int *)malloc(cols * sizeof(int));
        if (array[i] == NULL)
        {
            fprintf(stderr, "Error allocating memory for row %d.\n", i + 1);
            // Free previously allocated memory here
            for (int j = 0; j < i; j++)
            {
                free(array[j]);
            }
            free(array);
            return NULL;
        }
    }

    // Reopen the file to read and fill the array
    file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening the file: %s\n", filename);
        // Free allocated memory here
        for (int i = 0; i < rows; i++)
        {
            free(array[i]);
        }
        free(array);
        return NULL;
    }

    // Read and fill the array
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            fscanf(file, "%d", &array[i][j]);
        }
    }

    // Close the file
    fclose(file);

    *num_rows = rows;
    *num_cols = cols;

    return array; // Now the allocated array is returned
}

Habitat NewHabitat(const char *filename)
{
    Habitat this;
    this = (Habitat)malloc(sizeof(struct HABITAT));
    this->rows = 0;
    this->cols = 0;
    this->jungle = GenerateHabitat(filename, &this->rows, &this->cols);
    this->PrintHabitat = &PrintHabitat;
    this->DeleteHabitat = &DeleteHabitat;

    return this;
}

void PrintHabitat(const Habitat this)
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            printf("%d ", this->jungle[i][j]);
        }
        printf("\n");
    }
}

void DeleteHabitat(const Habitat this)
{
    if (this != NULL)
    {
        for (int i = 0; i < this->rows; i++)
        {
            free(this->jungle[i]);
        }
        free(this->jungle);
        free(this);
    }
};