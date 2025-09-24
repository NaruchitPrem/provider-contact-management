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

void add_data(){
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
    int choice;

    while(1) {
        printf("\n==== ระบบจัดการข้อมูลการติดต่อผู้ให้บริการ ====\n");
        printf("1) ดูข้อมูลการติดต่อผู้ให้บริการทั้งหมด\n");
        printf("2) เพิ่มข้อมูลการติดต่อใหม่\n");
        printf("3) ค้นหาข้อมูลการติดต่อผู้ให้บริการ\n");
        printf("4) อัพเดตข้อมูลการติดต่อ\n");
        printf("5) ลบข้อมูลการติดต่อ\n");
        printf("0) ออกจากโปรแกรม\n");
        printf("กรุณาเลือกเมนู: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: read_data(); break;
            //case 2: add_data(); break;
            //case 3: search_data(); break;
            //case 4: update_data(); break;
            //case 5: delete_data(); break;
            //case 0:
               // printf("ขอบคุณที่ใช้งาน\n");
                //exit(0);
            //default:
                //printf("เลือกเมนูไม่ถูกต้อง กรุณาลองใหม่\n");
        }
    }
    return 0;
}