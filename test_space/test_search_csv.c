#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void stringToLower(char *dest, const char *src) {
    int i = 0;
    for (i = 0; src[i] != '\0'; i++) {
        if (src[i] >= 'A' && src[i] <= 'Z') {
            dest[i] = src[i] + 32;
        } else {
            dest[i] = src[i];
        }
    }
    dest[i] = '\0';
}

void search_data() {
    char searchTerm[100];
    int searchChoice;
    int found = 0;

    printf("What do you want to search from? :\n");
    printf("1.Provider Name\n");
    printf("2.Service Type\n");
    printf("Select (1 or 2): ");
    scanf("%d", &searchChoice);
    getchar();

    printf("Enter the words you want to search for : ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    char lowerSearchTerm[100];
    stringToLower(lowerSearchTerm, searchTerm);

    FILE *file = fopen("providers.csv", "r");
    if (file == NULL) {
        printf("Can not open file providers.csv \n");
        return;
    }

    char line[400];
    fgets(line, sizeof(line), file);

    printf("\nResult:\n");
    while (fgets(line, sizeof(line), file)) {
        char name[100], serviceType[100];
        char lineCopy[400];
        strcpy(lineCopy, line);
        
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(name, token);

        token = strtok(NULL, ",");
        if (token != NULL) strcpy(serviceType, token);

        char lowerName[100], lowerServiceType[100];
        stringToLower(lowerName, name);
        stringToLower(lowerServiceType, serviceType);

        if (searchChoice == 1 && strstr(lowerName, lowerSearchTerm) != NULL) {
            lineCopy[strcspn(lineCopy, "\n")] = 0;
            printf("%s\n", lineCopy);
            found = 1;
        } else if (searchChoice == 2 && strstr(lowerServiceType, lowerSearchTerm) != NULL) {
            lineCopy[strcspn(lineCopy, "\n")] = 0;
            printf("%s\n", lineCopy);
            found = 1;
        }
    }

    if (found != 1) {
        printf("No data found matching the search term. '%s'\n", searchTerm);
    }

    fclose(file);
}

int main() {
    search_data();
    return 0;
}