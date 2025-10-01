#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void remove_newline(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
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

int main (){
    delete_data();
    return 0;
}