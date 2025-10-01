#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char providerName[100];
    char serviceType[100];
    char phoneNumber[50];
    char email[100];

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

int main() {
    add_data();
    return 0;
}