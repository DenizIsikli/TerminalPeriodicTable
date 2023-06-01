#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000
#define NUM_ELEMENTS 118

typedef struct {
    int atomicNumber;
    char symbol[3];
    char name[20];
    double atomicWeight;
} Element;

Element periodicTable[NUM_ELEMENTS];

void initializePeriodicTableFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error");
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file);

    int index = 0;

    while (!feof(file)) {
        sscanf(line, "%d,%[^,],%[^,],%lf",
               &periodicTable[index].atomicNumber,
               periodicTable[index].symbol,
               periodicTable[index].name,
               &periodicTable[index].atomicWeight);
        index++;
    }

    fclose(file);
}

void returnElement(int atomicNumber) {
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
}

int main() {
    const char *filename = "C:\\Users\\deniz\\CLionProjects\\PeriodicTable\\PeriodicTable.txt";
    initializePeriodicTableFromFile(filename);

    int atomicNumber;
    scanf("%d", &atomicNumber);

    printf("The scanned atomicNumber is: %d", atomicNumber);

    if(atomicNumber != NULL) {
        returnElement(atomicNumber);
    } else {
        perror("Error");
    }

    return 0;
}