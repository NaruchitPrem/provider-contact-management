#include <stdio.h>
#include <string.h>

char providerName [100], serviceType[100], email[100], phoneNumber[100];


void setup_test_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating test file.\n");
        return;
    }
    fprintf(file, "Test Provider 1,Service A,111-222-3333,test1@example.com\n");
    fprintf(file, "Test Provider 2,Service B,444-555-6666,test2@example.com\n");
    fclose(file);
}

void unit_test_add() {
    const char *test_filename = "test_providers.csv";

    printf("\n--- Star Testing: add_data ---\n");
    printf("Caution!!: This test will delete all data in providers.csv and recreate\n");
    
    char confirmation[10];
    printf("Do you want to continue? (yes/no): ");
    fgets(confirmation, 10, stdin);
    remove_newline(confirmation);

    if (strcmp(confirmation, "yes") != 0) {
        printf("Cancle Testing\n");
        return;
    }

    setup_test_file(test_filename);

    FILE *file = fopen("providers.csv", "a");
    fprintf(file, "New Provider,New Service,123-456-7890,new@example.com\n");
    fclose(file);

    file = fopen("providers.csv", "r");
    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "New Provider,New Service,123-456-7890,new@example.com")) {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found) {
        printf("\nTest Result: PASS - Add new provider complete\n");
    } else {
        printf("\nTest Result: FAIL - No newly added data was found in the file.\n");
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

int main() {
    return 0;
}