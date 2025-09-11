#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char providerName[100];
char serviceType[50];
char phoneNumber[20];
char email[100];

void add_data_csv(){
    FILE *file = fopen("providers.csv" , "a");
     if (!file) {
        printf("Cannot open file.\n");
        return;
    }
    char str[100];
    printf("Add new provider details in the format: ProviderName,ServiceType,PhoneNumber,Email\n");
    printf("Add new provider details in the format: ");
    fgets(str, 100, stdin);
    fputs(str, file);
    fclose(file);
    printf("New provider added: %s", str);
    
}

int main() {
    add_data_csv();
    return 0;
}