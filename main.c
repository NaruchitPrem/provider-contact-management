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

void normalize_phone_number(char *dest, const char *src) {
    int j = 0;
    for (int i = 0; src[i] != '\0'; i++) {
        if (src[i] >= '0' && src[i] <= '9') {
            dest[j] = src[i];
            j++;
        }
    }
    dest[j] = '\0';
}

int prompt_after_action() {
    char user_choice[100];

    while (1) {
        printf("\nPress Enter to return to the main menu, or type 'exit' to quit: ");
        
        fgets(user_choice, sizeof(user_choice), stdin);
        remove_newline(user_choice);

        if (strcmp(user_choice, "") == 0) {
            return 1;
        } 
        else if (strcmp(user_choice, "exit") == 0) {
            return 0;
        }
        else {
            printf("-> Invalid input. Please try again.\n");
        }
    }
}

int add_data() {

    printf("===== Add New Provider =====\n");

   while (1) {
        printf("Enter Provider Name (type 'exit' to cancle): ");
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
        if (strcmp(serviceType, "exit") == 0) {
            printf("Add operation cancelled.\n");
            return 0;
        }
        if (is_valid_input(serviceType)) {
            break;
        }
        printf("-> Invalid input. Service Type cannot be empty and can only contain letters, numbers, and spaces.\n");
    }

    while (1) {
        printf("Enter Phone Number (e.g., 555-1234): ");
        fgets(phoneNumber, sizeof(phoneNumber), stdin);
        remove_newline(phoneNumber);
        if (strcmp(phoneNumber, "exit") == 0) {
            printf("Add operation cancelled.\n");
            return 0;
        }
        if (is_valid_phone(phoneNumber)) {
            break;
        }
        printf("-> Invalid phone number format. Please use only digits and hyphens.\n");
    }

    while (1) {
        printf("Enter Email (e.g., contact@example.com): ");
        fgets(email, sizeof(email), stdin);
        remove_newline(email);
        if (strcmp(email, "exit") == 0) {
            printf("Add operation cancelled.\n");
            return 0;
        }
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

void search_data() {
    char searchTerm[100];
    int searchChoice;
    int found = 0;

    while (1) {
        printf("What do you want to search from? (Type 'back' to return to menu):\n");
        printf("1.Provider Name\n");
        printf("2.Service Type\n");
        printf("3.Phone Number\n");
        printf("4.Email\n");
        printf("Select 1 to 4 : ");
        char choice_input[20];
        fgets(choice_input, sizeof(choice_input), stdin);
        remove_newline(choice_input);

        if (strcmp(choice_input, "back") == 0) {
            printf("Search cancelled.\n");
            return;
        }
        if (sscanf(choice_input, "%d", &searchChoice) == 1 && (searchChoice >= 1 && searchChoice <= 4)) {
            break;
        }   
        printf("\n-> Invalid input. Please select 1 to 4 .\n\n");
    }


    printf("Enter the words you want to search for : ");
    fgets(searchTerm, sizeof(searchTerm), stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    char processedSearchTerm[100];
    if (searchChoice == 3) {
        normalize_phone_number(processedSearchTerm, searchTerm);
    } else {
        stringToLower(processedSearchTerm, searchTerm);
    }


    FILE *file = fopen("providers.csv", "r");
    if (file == NULL) {
        printf("Can not open file providers.csv \n");
        return;
    }

    char line[400];

    while (fgets(line, sizeof(line), file)) {
        char lineCopy[512];
        strcpy(lineCopy, line);

        char name[100], serviceType[100], phoneNumber[100], email[100];
        int fields_read = sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", name, serviceType, phoneNumber, email);

        if (fields_read < 4) {
            continue;
        }

        char lowerName[100], lowerServiceType[100], normalizedPhone[100],  lowerEmail[100];
        stringToLower(lowerName, name);
        stringToLower(lowerServiceType, serviceType);
        normalize_phone_number(normalizedPhone, phoneNumber);
        stringToLower(lowerEmail, email);

        int is_match = 0;
        if (searchChoice == 1 && strstr(lowerName, processedSearchTerm) != NULL) {
            is_match = 1;
        } else if (searchChoice == 2 && strstr(lowerServiceType, processedSearchTerm) != NULL) {
            is_match = 1;
        } else if (searchChoice == 3 && strstr(normalizedPhone, processedSearchTerm) != NULL) {
            is_match = 1;
        } else if (searchChoice == 4 && strstr(lowerEmail, processedSearchTerm) != NULL) {
            is_match = 1;
        }

        if (is_match) {
            if (found == 0) {
            }
            found = 1;

            char found_name[100], found_service[100], found_phone[50], found_email[100];
            sscanf(lineCopy, "%[^,],%[^,],%[^,],%[^\n]", found_name, found_service, found_phone, found_email);

            printf("\n--- Provider Found ---\n");
            printf("  Name:    %s\n", found_name);
            printf("  Service: %s\n", found_service);
            printf("  Phone:   %s\n", found_phone);
            printf("  Email:   %s\n", found_email);
            printf("----------------------\n");
        }
    }

    if (found == 0) {
        printf("No data found matching the search term: '%s'\n", searchTerm);
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

        char lower_search_name[100];
        stringToLower(lower_search_name, search_name);

        FILE *infile = fopen("providers.csv", "r");
        if (infile == NULL) {
            printf("Error: Cannot find providers.csv!\n");
            return;
        }

        found_flag = 0;
        current_line_number = 0;
        
        while (fgets(line_buffer, 512, infile)) {
            current_line_number++;
            char temp_name[100] = "";
            sscanf(line_buffer, "%[^,]", temp_name);

            char lower_temp_name[100];
            stringToLower(lower_temp_name, temp_name);
            
            if (strcmp(lower_search_name, lower_temp_name) == 0) {
                found_flag = 1;
                line_to_edit = current_line_number;
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

    char old_name[100], old_service[100], old_phone[50], old_email[100];
    sscanf(line_buffer, "%[^,],%[^,],%[^,],%[^\n]", old_name, old_service, old_phone, old_email);

    printf("\n--- Provider Found ---\n");
    printf("  Current Name:    %s\n", old_name);
    printf("  Current Service: %s\n", old_service);
    printf("  Current Phone:   %s\n", old_phone);
    printf("  Current Email:   %s\n", old_email);
    printf("----------------------\n");

    char confirm_edit[10];
    while (1) {
        printf("Do you want to edit this provider? (yes/no): ");
        fgets(confirm_edit, 10, stdin);
        remove_newline(confirm_edit);

        if (strcmp(confirm_edit, "yes") == 0) {
            break;
        } else if (strcmp(confirm_edit, "no") == 0) {
            printf("Update cancelled. Returning to main menu.\n");
            return;
        } else {
            printf("-> Invalid input. Please type 'yes' or 'no'.\n");
        }
    }

    printf("\nPlease enter the new information for the provider.\n");
    char new_name[100], new_service[100], new_phone[50], new_email[100];

    while (1) {
        printf("Enter New Provider Name (type 'exit' to cancel): ");
        fgets(new_name, sizeof(new_name), stdin);
        remove_newline(new_name);
        if (strcmp(new_name, "exit") == 0) {
            printf("Update operation cancelled.\n");
            return ;
        }
        if (is_valid_input(new_name)) {
            break;
        }
        printf("-> Invalid input. Name cannot be empty and can only contain letters, numbers, and spaces.\n");
    }

    while (1) {
        printf("Enter New Service Type (type 'exit' to cancel): ");
        fgets(new_service, sizeof(new_service), stdin);
        remove_newline(new_service);
        if (strcmp(new_service, "exit") == 0) {
            printf("Update operation cancelled.\n");
            return ;
        }
        if (is_valid_input(new_service)) {
            break;
        }
        printf("-> Invalid input. Service Type cannot be empty and can only contain letters, numbers, and spaces.\n");
    }
    
    while (1) {
        printf("Enter New Phone Number (e.g., 555-1234): ");
        fgets(new_phone, 50, stdin);
        remove_newline(new_phone);
        if (strcmp(new_phone, "exit") == 0) {
            printf("Update operation cancelled.\n");
            return ;
        }
        if (is_valid_phone(new_phone)) {
            break;
        }
        printf("-> Invalid phone number format. Please use only digits and hyphens.\n");
    }

    while (1) {
        printf("Enter New Email (e.g., contact@example.com): ");
        fgets(new_email, 100, stdin);
        remove_newline(new_email);
        if (strcmp(new_email, "exit") == 0) {
            printf("Update operation cancelled.\n");
            return ;
        }
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
    }

    FILE *infile = fopen("providers.csv", "r");
    FILE *outfile = fopen("temp.csv", "w");

    current_line_number = 0;
    char write_buffer[512];
    while (fgets(write_buffer, 512, infile)) {
        current_line_number++;
        
        if (current_line_number == line_to_edit) {
            fprintf(outfile, "%s,%s,%s,%s\n", new_name, new_service, new_phone, new_email);
        } else {
            fputs(write_buffer, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);

    remove("providers.csv");
    rename("temp.csv", "providers.csv");
    
    printf("\nUpdate complete!\n");
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
    int function;
    int keep_running = 1;
    char menu_input[100];

    while (keep_running) {
        printf("\n----- Service Provider Data Management System -----\n");
        printf("1) View All Service Provider Information\n");
        printf("2) Add New Provider Information\n");
        printf("3) Search Service Provider Information\n");
        printf("4) Update Service Provider Information\n");
        printf("5) Delete Service Provider Information\n");
        //printf("6) Unit Test\n");
        printf("0) Exit Program\n");
        printf("Select Menu: ");
        fgets(menu_input, sizeof(menu_input), stdin);
        if (sscanf(menu_input, "%d", &function) != 1) {
            function = -1;
        }

        switch (function) {
            case 1:
                read_data();
                keep_running = prompt_after_action();
                break;
            case 2:
                add_data();
                break;
            case 3:
                search_data();
                keep_running = prompt_after_action();
                break;
            case 4:
                update_data();
                break;
            case 5:
                delete_data();
                break;
            case 0:
                keep_running = 0;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                printf("Please Press Enter to return to the menu...");
                char enter_buffer[10]; 
                fgets(enter_buffer, sizeof(enter_buffer), stdin);

        }
    }

    printf("\nThanks For Using!!\n");
    return 0;
}