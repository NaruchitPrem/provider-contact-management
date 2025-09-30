#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char providerName[100];
char serviceType[50];
char phoneNumber[20];
char email[100];

void read_data(){
    FILE *file = fopen("providers.csv" , "r");
    if (!file) {
        printf("Cannot open file.\n");
        return;
    }
    char str[100] = "";
    char *token;
    char *delim  = ",";
    printf("+----------------------+-----------------+-----------------+------------------------------+\n");
    printf("| %-20s | %-15s | %-15s | %-28s |\n", "ProviderName", "ServiceType", "PhoneNumber", "Email");
    printf("+----------------------+-----------------+-----------------+------------------------------+\n");
    while (fgets(str, sizeof(str), file) != NULL){
        token = strtok(str, delim);
        int col = 0;
        while(token != NULL) {
            switch (col){
                case 0:
                    strcpy(providerName, token);
                    break;
                case 1:
                    strcpy(serviceType, token);
                    break;
                case 2:
                    strcpy(phoneNumber, token);
                    break;
                case 3:
                    token[strcspn(token, "\r\n")] = 0;
                    strcpy(email, token);
                    break;
            }
            col++;
            token = strtok(NULL, delim);
        }
        printf("| %-20s | %-15s | %-15s | %-28s |\n", providerName, serviceType, phoneNumber, email);
    }
    printf("+----------------------+-----------------+-----------------+------------------------------+\n");
    fclose(file);
};

void remove_newline(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

int is_valid_phone(const char *phone) {
    if (strlen(phone) == 0) {
        return 0;
    }
    for (int i = 0; phone[i] != '\0'; i++) {
        int is_digit = (phone[i] >= '0' && phone[i] <= '9');
        int is_hyphen = (phone[i] == '-');
        if (!is_digit && !is_hyphen) {
            return 0;
        }
    }
    return 1;
}

int is_valid_email(const char *email) {
    int at_index = -1;
    int email_len = strlen(email);

    for (int i = 0; i < email_len; i++) {
        if (email[i] == '@') {
            at_index = i;
            break;
        }
    }

    if (at_index <= 0) {
        return 0;
    }

    int dot_found_after_at = 0;
    for (int i = at_index + 1; i < email_len; i++) {
        if (email[i] == '.') {
            if (i > at_index + 1 && i < email_len - 1) {
                dot_found_after_at = 1;
                break;
            }
        }
    }

    if (dot_found_after_at) {
        return 1;
    } else {
        return 0;
    }
}

int add_data() {
    FILE *file = fopen("providers.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("===== Add New Provider =====\n");

    printf("Enter Provider Name: ");
    fgets(providerName, sizeof(providerName), stdin);
    remove_newline(providerName);

    printf("Enter Service Type: ");
    fgets(serviceType, sizeof(serviceType), stdin);
    remove_newline(serviceType);

    while (1) {
        printf("Enter Phone Number (e.g., 555-1234): ");
        fgets(phoneNumber, sizeof(phoneNumber), stdin);
        remove_newline(phoneNumber);
        if (is_valid_phone(phoneNumber)) {
            break;
        }
        printf("-> Invalid phone number format. Please use only digits and hyphens.\n");
    }

    while (1) {
        printf("Enter Email (e.g., contact@example.com): ");
        fgets(email, sizeof(email), stdin);
        remove_newline(email);
        if (is_valid_email(email)) {
            break;
        }
        printf("-> Invalid email format. Please ensure it includes '@' and a '.' correctly.\n");
    }

    fprintf(file, "%s,%s,%s,%s\n", providerName, serviceType, phoneNumber, email);

    fclose(file);
    printf("\nProvider added successfully!\n");

    return 0;
}

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
    int choice;

    while(1) {
        printf("\n==== Service Provider Data Management System ====\n");
        printf("1) View All Service Provider Information\n");
        printf("2) Add New Provider Information\n");
        printf("3) Search Service Provider Information\n");
        printf("4) Update Service Provider Information\n");
        printf("5) Delete Service Provider Information\n");
        printf("0) Exit Program\n");
        printf("Select Menu: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: read_data(); break;
            case 2: add_data(); break;
            case 3: search_data(); break;
            //case 4: update_data(); break;
            //case 5: delete_data(); break;
            case 0:
                printf("Thanks For Using\n");
                exit(0);
            default:
                printf("Invalid menu selection. Please try again.\n");
        }
    }
    return 0;
}