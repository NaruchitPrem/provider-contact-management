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

int is_valid_input(const char *str) {
    int has_actual_char = 0;

    if (strlen(str) == 0) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        
        int is_letter_upper = (c >= 'A' && c <= 'Z');
        int is_letter_lower = (c >= 'a' && c <= 'z');
        int is_digit = (c >= '0' && c <= '9');
        int is_space = (c == ' ');

        if (!is_letter_upper && !is_letter_lower && !is_digit && !is_space) {
            return 0;
        }

        if (!is_space) {
            has_actual_char = 1;
        }
    }
    
    if (has_actual_char == 0) {
        return 0;
    }

    return 1;
}

int add_data() {

    printf("===== Add New Provider =====\n");

   while (1) {
        printf("Enter Provider Name: ");
        fgets(providerName, sizeof(providerName), stdin);
        remove_newline(providerName);
        if (strcmp(providerName, "exit") == 0) {
            printf("Add operation cancelled.\n");
            return 0;
        }
        if (is_valid_input(providerName)) {
            break;
        }
        printf("-> Invalid input. Name cannot be empty and can only contain letters, numbers, and spaces.\n");
    }

    while (1) {
        printf("Enter Service Type: ");
        fgets(serviceType, sizeof(serviceType), stdin);
        remove_newline(serviceType);
        if (is_valid_input(serviceType)) {
            break;
        }
        printf("-> Invalid input. Service Type cannot be empty and can only contain letters, numbers, and spaces.\n");
    }

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


    printf("\n----------------------------------------\n");
    printf("You are about to add the following data:\n");
    printf("  Provider Name: %s\n", providerName);
    printf("  Service Type:  %s\n", serviceType);
    printf("  Phone Number:  %s\n", phoneNumber);
    printf("  Email:         %s\n", email);
    printf("----------------------------------------\n");

    char confirmation[10];
    while (1) {
        printf("Save this information? (yes/no): ");
        fgets(confirmation, 10, stdin);
        remove_newline(confirmation);

        if (strcmp(confirmation, "yes") == 0) {
            break;
        } else if (strcmp(confirmation, "no") == 0) {
            printf("Add operation cancelled. Returning to main menu.\n");
            return 0;
        } else {
            printf("-> Invalid input. Please type 'yes' or 'no'.\n");
        }
    }

    FILE *file = fopen("providers.csv", "a");
    if (file == NULL) {
        printf("Error: Could not open providers.csv for writing.\n");
        return 0;
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

void update_data() {
    char search_name[100];
    char line_buffer[512];
    int line_to_edit = -1;
    int current_line_number = 0;
    int found_flag = 0;

    printf("\n===== Update Data =====\n");
    while (1) {
        printf("Enter Provider Name to edit (or type 'exit' to cancel): ");
        fgets(search_name, 100, stdin);
        remove_newline(search_name);

        if (strcmp(search_name, "exit") == 0) {
            printf("Update cancelled.\n");
            return;
        }
        


        FILE *infile = fopen("providers.csv", "r");
        if (infile == NULL) {
            printf("Error: Cannot find providers.csv!\n");
            return;
        }

        found_flag = 0;
        int current_line_number = 0;
        
        while (fgets(line_buffer, 512, infile)) {
            current_line_number++;
            char temp_name[100] = "";
            sscanf(line_buffer, "%[^,]", temp_name);
            
            if (strcmp(search_name, temp_name) == 0) {
                found_flag = 1;
                line_to_edit = current_line_number;
                break; 
            }
        }
        fclose(infile);

        if (found_flag == 1) {
            printf("Found '%s'. Proceeding with update...\n", search_name);
            break;
        } else {
            printf("-> '%s' not found. Please try again.\n\n", search_name);
        }
    }

    char new_name[100], new_service[100], new_phone[50], new_email[100];

    printf("--- Enter new info ---\n");
    printf("Enter new Provider Name: ");
    fgets(new_name, 100, stdin);
    remove_newline(new_name);

    printf("Enter new Service Type: ");
    fgets(new_service, 100, stdin);
    remove_newline(new_service);
    
    while (1) {
        printf("Enter Phone Number (e.g., 555-1234): ");
        fgets(new_phone, 50, stdin);
        remove_newline(new_phone);
        if (is_valid_phone(new_phone)) {
            break;
        }
        printf("-> Invalid phone number format. Please use only digits and hyphens.\n");
    }

    while (1) {
        printf("Enter Email (e.g., contact@example.com): ");
        fgets(new_email, 100, stdin);
        remove_newline(new_email);
        if (is_valid_email(new_email)) {
            break;
        }
        printf("-> Invalid email format. Please ensure it includes '@' and a '.' correctly.\n");
    }

    printf("\n----------------------------------------\n");
    printf("You are about to update the following data:\n");
    printf("  Provider Name: %s\n", new_name);
    printf("  Service Type:  %s\n", new_service);
    printf("  Phone Number:  %s\n", new_phone);
    printf("  Email:         %s\n", new_email);
    printf("----------------------------------------\n");

    char confirmation[10];
    while (1) {
        printf("Are you sure you want to update? (yes/no): ");
        fgets(confirmation, 10, stdin);
        remove_newline(confirmation);

        if (strcmp(confirmation, "yes") == 0) {
            break;
        } else if (strcmp(confirmation, "no") == 0) {
            printf("Update cancelled. Returning to main menu.\n");
            return;
        } else {
            printf("-> Invalid input. Please type 'yes' or 'no'.\n");
        }

    FILE *infile = fopen("providers.csv", "r");
    FILE *outfile = fopen("temp.csv", "w");

    current_line_number = 0;
    while (fgets(line_buffer, 512, infile)) {
        current_line_number++;
        
        if (current_line_number == line_to_edit) {
            fprintf(outfile, "%s,%s,%s,%s\n", new_name, new_service, new_phone, new_email);
        } else {
            fputs(line_buffer, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);

    remove("providers.csv");
    rename("temp.csv", "providers.csv");
    
    printf("\nUpdate complete!\n");
    }
}

void delete_data() {
    char search_name[100];
    char line_buffer[512];
    char data_to_delete[512];
    int line_to_delete = -1; 
    int found_flag = 0;

    printf("\n===== Delete Provider Information =====\n");

    while (1) { 
        printf("Enter Provider Name to delete (or type 'exit' to cancel): ");
        fgets(search_name, 100, stdin);
        remove_newline(search_name);

        if (strcmp(search_name, "exit") == 0) {
            printf("Delete operation cancelled.\n");
            return;
        }
        
        char lower_search_name[100];
        stringToLower(lower_search_name, search_name);

        FILE *infile = fopen("providers.csv", "r");
        if (infile == NULL) {
            printf("Error: Cannot find providers.csv!\n");
            return;
        }

        found_flag = 0;
        int current_line_number = 0;
        
        while (fgets(line_buffer, 512, infile)) {
            current_line_number++;
            char temp_name[100] = "";
            sscanf(line_buffer, "%[^,]", temp_name);
            
            char lower_temp_name[100];
            stringToLower(lower_temp_name, temp_name);

            if (strcmp(lower_search_name, lower_temp_name) == 0) {
                found_flag = 1;
                line_to_delete = current_line_number;
                strcpy(data_to_delete, line_buffer);
                break; 
            }
        }
        fclose(infile);

        if (found_flag == 1) {
            break; 
        } else {
            printf("-> '%s' not found. Please try again.\n\n", search_name);
        }
    }

    printf("\n----------------------------------------\n");
    printf("You are about to delete the following record:\n");

    char del_name[100], del_service[100], del_phone[50], del_email[100];
    sscanf(data_to_delete, "%[^,],%[^,],%[^,],%[^\n]", del_name, del_service, del_phone, del_email);
    printf("  Provider Name: %s\n", del_name);
    printf("  Service Type:  %s\n", del_service);
    printf("  Phone Number:  %s\n", del_phone);
    printf("  Email:         %s\n", del_email);
    printf("----------------------------------------\n");

    char confirmation[10];
    while (1) {
        printf("Are you sure you want to delete this? This cannot be undone. (yes/no): ");
        fgets(confirmation, 10, stdin);
        remove_newline(confirmation);

        if (strcmp(confirmation, "yes") == 0) {
            break; 
        } else if (strcmp(confirmation, "no") == 0) {
            printf("Delete cancelled. Returning to main menu.\n");
            return;
        } else {
            printf("-> Invalid input. Please type 'yes' or 'no'.\n");
        }
    }
    
    FILE *infile = fopen("providers.csv", "r");
    FILE *outfile = fopen("temp.csv", "w");

    int current_line_number = 0;
    while (fgets(line_buffer, 512, infile)) {
        current_line_number++;
        
        if (current_line_number != line_to_delete) {
            fputs(line_buffer, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);

    remove("providers.csv");
    rename("temp.csv", "providers.csv");
    
    printf("\nProvider deleted successfully!\n");
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
        //printf("6) Test Case\n");
        printf("0) Exit Program\n");
        printf("Select Menu: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1: read_data(); break;
            case 2: add_data(); break;
            case 3: search_data(); break;
            case 4: update_data(); break;
            case 5: delete_data(); break;
            //case 6: tast_case(); break;
            case 0:
                printf("Thanks For Using!\n");
                exit(0);
            default:
                printf("Invalid menu selection. Please try again.\n");
        }
    }
    return 0;
}