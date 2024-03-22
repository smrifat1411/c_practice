#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUITS 100
#define MAX_FRUIT_NAME_LENGTH 50

void removeFruit(const char *filename, const char *fruitToRemove) {
    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file %s.\n", filename);
        return;
    }

    // Open a temporary file for writing
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_FRUITS * MAX_FRUIT_NAME_LENGTH];
    char *token;
    int found = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        // Tokenize the line using commas as delimiters
        token = strtok(line, ",\n");

        // Iterate through each token (fruit name)
        while (token != NULL) {
            // If the token (fruit name) is not the one to remove, write it to the temporary file
            if (strcmp(token, fruitToRemove) != 0) {
                fprintf(tempFile, "%s, ", token);
            } else {
                found = 1; // Set found flag to 1 if fruit is found and removed
            }
            token = strtok(NULL, ",\n");
        }
    }

    fclose(file);
    fclose(tempFile);

    // Remove the original file
    if (remove(filename) != 0) {
        printf("Error deleting original file %s.\n", filename);
        return;
    }

    // Rename the temporary file to the original file name
    if (rename("temp.txt", filename) != 0) {
        printf("Error renaming temporary file.\n");
        return;
    }

    if (found) {
        printf("Fruit '%s' removed from file '%s'.\n", fruitToRemove, filename);
    } else {
        printf("Fruit '%s' not found in file '%s'.\n", fruitToRemove, filename);
    }
}

int main() {
    char fruit[MAX_FRUIT_NAME_LENGTH];
    
    printf("Enter the fruit name to remove: ");
    scanf("%s", fruit);
    
    removeFruit("fruits.txt", fruit);

    return 0;
}
