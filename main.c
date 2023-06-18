#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <omp.h>

#define MAX_LINE_LENGTH 1000
#define NUM_ELEMENTS 118

// Function prototype
void initializePeriodicTableFromFile(const char *filename);
void returnElement(int atomicNumber);

typedef struct {
    int atomicNumber;
    char symbol[3];
    char name[20];
    double atomicWeight;
} Element;

// Create 118 elements
Element periodicTable[NUM_ELEMENTS];

void initializePeriodicTableFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error");
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int index = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        // Replace whatever is read from "line" accordingly with format and insert information for every element
        sscanf(line, "%d,%[^,],%[^,],%lf",
               &periodicTable[index].atomicNumber,
               periodicTable[index].name,
               periodicTable[index].symbol,
               &periodicTable[index].atomicWeight);
        index++;
    }
    fclose(file);
}

void returnElement(int atomicNumber) {
    Element *element = NULL;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (periodicTable[i].atomicNumber == atomicNumber) {
            // If the element is found given the parameter, put the information in object "element"
            element = &periodicTable[i];
            break;
        }
    }

    // Print information
    if (element != NULL) {
        printf("Atomic number: %d\n", element->atomicNumber);
        printf("Element name: %s\n", element->name);
        printf("Symbol: %s\n", element->symbol);
        printf("Atomic Weight: %.2lf\n\n", element->atomicWeight);
        /* ... print other fields ... */
    } else {
        printf("Element with atomic number %d not found.\n\n", atomicNumber);
    }
}

int main() {
    const char *filename = "C:\\Users\\deniz\\CLionProjects\\PeriodicTable\\PeriodicTable.txt";
    initializePeriodicTableFromFile(filename);

    int atomicNumber;
    char input[10];

    while (true) {
        printf("Enter an atomic number (or 'q' to quit):");

        // Input for the atomic number
        if (scanf("%d", &atomicNumber) == 1) {
            returnElement(atomicNumber);
        } else {
            printf("Invalid input. Please enter a valid atomic number or 'q' to quit.\n");
        }

        if (input[0] == 'q' || input[0] == 'Q') {
            break;  // Exit the loop if 'q' or 'Q' is entered
        }
    }
    return 0;
}
