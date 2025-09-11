#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char providerName[100];
char serviceType[50];
char phoneNumber[20];
char email[100];

void read_data_csv(){
    FILE *file = fopen("providers.csv" , "r");
    char str[100] = "";
    char *token;
    char *delim  = ",";
    while (fgets(str, sizeof(str), file) != NULL){
        printf("Provider: %s", str);
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
                    strcpy(email, token);
                    break;
            }
            col++;
            token = strtok(NULL, delim);
        }
        printf("ProviderName: %s, ServiceType: %s, PhoneNumber: %s, Email: %s\n", 
            providerName, serviceType, phoneNumber, email);
    }
    fclose(file);
};

int main() {
    read_data_csv();
    return 0;
}