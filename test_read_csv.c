#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char providerName[100];
char serviceType[50];
char phoneNumber[20];
char email[100];

void read_data_csv(){
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

int main() {
    read_data_csv();
    return 0;
}