#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void update_data() {
    char search_name[100];
    char line_buffer[512];
    int line_to_edit = -1;
    int current_line_number = 0;
    int found_flag = 0;

    printf("\n===== Update Data =====\n");
    printf("Enter Provider Name to edit: ");
    fgets(search_name, 100, stdin);
    remove_newline(search_name);

    FILE *infile = fopen("providers.csv", "r");
    if (infile == NULL) {
        printf("Error: Cannot find providers.csv!\n");
        return;
    }

    while (fgets(line_buffer, 512, infile)) {
        current_line_number++;
        char temp_name[100];
        sscanf(line_buffer, "%[^,]", temp_name);
        
        if (strcmp(search_name, temp_name) == 0) {
            printf("Found '%s' at line %d\n", search_name, current_line_number);
            found_flag = 1;
            line_to_edit = current_line_number;
            break;
        }
    }
    fclose(infile);

    if (found_flag == 0) {
        printf("'%s' not found in the file.\n", search_name);
        return;
    }

    char new_name[100], new_service[100], new_phone[50], new_email[100];

    printf("--- Enter new info ---\n");
    printf("Enter new Provider Name: ");
    fgets(new_name, 100, stdin);
    remove_newline(new_name);

    printf("Enter new Service Type: ");
    fgets(new_service, 100, stdin);
    remove_newline(new_service);
    
    printf("Enter new Phone Number: ");
    fgets(new_phone, 50, stdin);
    remove_newline(new_phone);

    printf("Enter new Email: ");
    fgets(new_email, 100, stdin);
    remove_newline(new_email);

    infile = fopen("providers.csv", "r");
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

int main() {
    update_data();
    return 0;
}