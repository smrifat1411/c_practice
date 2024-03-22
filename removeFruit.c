#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRUITS 100
#define MAX_FRUIT_NAME_LENGTH 50

void removeFruit(const char *filename, const char *fruitToRemove)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char fruits[MAX_FRUITS][MAX_FRUIT_NAME_LENGTH];
    int count = 0;

    // read
    while (fscanf(file, "%49[^, \n]%*c", fruits[count]) == 1)
    {
        count++;
    }
    fclose(file);

    // algorithm
    int i, j;
    int found = 0;
    for (i = 0; i < count; i++)
    {
        if (strcmp(fruits[i], fruitToRemove) == 0)
        {
            found = 1;
            for (j = i; j < count - 1; j++)
            {
                strcpy(fruits[j], fruits[j + 1]);
            }
            count--;
            break;
        }
    }

    if (!found)
    {
        printf("Fruit '%s' not found in the list.\n", fruitToRemove);
        return;
    }

    // write
    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(file, "%s", fruits[i]);
        if (i < count - 1)
            fprintf(file, ",");
    }

    fclose(file);
    printf("Fruit '%s' removed from the list.\n", fruitToRemove);
}

int main()
{
    char fruit[MAX_FRUIT_NAME_LENGTH];
    printf("Enter the fruit name to remove: ");
    scanf("%s", fruit);

    removeFruit("fruits.txt", fruit);

    return 0;
}
