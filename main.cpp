#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 50
#define MAX_COLUMN_LENGTH 50
#define NUM_ELEMENTS 118

typedef struct {
    int atomicNumber;
    char symbol[MAX_COLUMN_LENGTH];
    char name[MAX_COLUMN_LENGTH];
    double atomicWeight;
} Element;

Element periodicTable[NUM_ELEMENTS];

void initializePeriodicTableFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Failed  to open the file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file);

    int index = 0;

    while (fgets(line, sizeof(line), file) != NULL && index < NUM_ELEMENTS) {
        sscanf(line, "%d,%[^,],%[^,],%lf",
               &periodicTable[index].atomicNumber,
               periodicTable[index].symbol,
               periodicTable[index].name,
               &periodicTable[index].atomicWeight);
        index++;
    }

    fclose(file);
}

int main() {
    const char *filename = "PeriodicTable.csv";
    initializePeriodicTableFromFile(filename);

    int atomicNumber;
    scanf("%d", atomicNumber);

    Element *element = NULL;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (periodicTable[i].atomicNumber == atomicNumber) {
            element = &periodicTable[i];
            break;
        }
    }

    if (element != NULL) {
        printf("Element: %s\n", element->name);
        printf("Symbol: %s\n", element->symbol);
        printf("Atomic Weight: %.2lf\n", element->atomicWeight);
        /* ... print other fields ... */
    } else {
        printf("Element with atomic number %d not found.\n", atomicNumber);
    }

    return 0;
}