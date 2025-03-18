// Hash function to put cars into hashtable
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct node{
    int num;
    char licensing[30];
    char name[20];
    struct node* nextnode;
}node;

int hash(char serial[],int n);
int main() {
    node* hasharray[1000];
    int i;
    int j;
    int cars;
    int length;
    int index;
    char names[20];
    char license[30];
    char duplicate[30];
    for(i=0; i<1000;i++){
        hasharray[i] = NULL;
    }
    printf("enter number of vehicles:");
    scanf("%d",&cars);
    printf("\n");
    printf("---------------------------\n");
    for(i=0;i<cars;i++){
        printf("Enter Car License plate no:");
        scanf("%s",license);
        printf("Your License is %s\n",license);
        printf("\n");
        printf("Enter name of owner:");
        
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        scanf("%s",names);
        printf("Name provided:%s\n",names);
        printf("---------------------------");
        printf("\n");
        length = strlen(license);
        strcpy(duplicate,license);
        index = hash(duplicate,length);
        //printf("%s\n",license);
        node* temp = malloc(sizeof(node));
        if(temp == NULL){
            printf("error in allocating memory");
            return 1;
        }
        temp->num = i;
        strcpy(temp->name,names);
        strcpy(temp->licensing,license);
        temp->nextnode = NULL;
        
        if(hasharray[index] == NULL){
            hasharray[index] = temp;
        }
        else{
            node* ptr = hasharray[index];
            while(ptr->nextnode != NULL){
                    ptr = ptr->nextnode;
                }
                    ptr->nextnode = temp;
            
        }
    }
    for(j=0;j<1000;j++){
        if(hasharray[j] != NULL){
        node* ptr = hasharray[j];
            int k = 1;
            while (ptr != NULL) {
                ptr->num = k;
                k = k + 1;
                ptr = ptr->nextnode;
            }
        }
    }
    
    printf("Data of Vehicles:\n\n");
    for (j = 0; j < 1000; j++) {
        if (hasharray[j] != NULL) {
            node* ptr = hasharray[j];
            while (ptr != NULL) {
                printf("Index:%d, ",j);
                printf("%d.",ptr->num);
                printf("Name:%s, ",ptr->name);
                printf("License:%s", ptr->licensing);
                printf("\n");
                ptr = ptr->nextnode;
            }
        }
    }
    
    for (j = 0; j < 1000; j++) {
        node* ptr = hasharray[j];
        while (ptr != NULL) {
            node* temp = ptr;
            ptr = ptr->nextnode;
            free(temp);
        }
    }
}

int hash(char serial[],int n){
    int j;
    int i;
    int sum = 0;
    int remainder;
    for(j=0;j<n;j++){
        serial[j] = toupper(serial[j]);
    }
    i = 0;
    while(serial[i] != '\0'){
        switch(serial[i]){
            case 'A':
                serial[i] = 11;
                break;
            case 'B':
                serial[i] = 12;
                break;
            case 'C':
                serial[i] = 13;
                break;
            case 'D':
                serial[i] = 14;
                break;
            case 'E':
                serial[i] = 15;
                break;
            case 'F':
                serial[i] = 16;
                break;
            case 'G':
                serial[i] = 17;
                break;
            case 'H':
                serial[i] = 18;
                break;
            case 'I':
                serial[i] = 19;
                break;
            case 'J':
                serial[i] = 20;
                break;
            case 'K':
                serial[i] = 21;
                break;
            case 'L':
                serial[i] = 22;
                break;
            case 'M':
                serial[i] = 23;
                break;
            case 'N':
                serial[i] = 24;
                break;
            case 'O':
                serial[i] = 25;
                break;
            case 'P':
                serial[i] = 26;
                break;
            case 'Q':
                serial[i] = 27;
                break;
            case 'R':
                serial[i] = 28;
                break;
            case 'S':
                serial[i] = 29;
                break;
            case 'T':
                serial[i] = 30;
                break;
            case 'U':
                serial[i] = 31;
                break;
            case 'V':
                serial[i] = 32;
                break;
            case 'W':
                serial[i] = 33;
                break;
            case 'X':
                serial[i] = 34;
                break;
            case 'Y':
                serial[i] = 35;
                break;
            case 'Z':
                serial[i] = 36;
                break;
            case '1':
                serial[i] = 1;
                break;
            case '2':
                serial[i] = 2;
                break;
            case '3':
                serial[i] = 3;
                break;
            case '4':
                serial[i] = 4;
                break;
            case '5':
                serial[i] = 5;
                break;
            case '6':
                serial[i] = 6;
                break;
            case '7':
                serial[i] = 7;
                break;
            case '8':
                serial[i] = 8;
                break;
            case '9':
                serial[i] = 9;
                break;
            case '0':
                serial[i] = 0;
                break;
            default:
                serial[i] = 100;
        }
        i++;
    }
    for(i=0;i<n;i++){
        sum = sum + serial[i];
    }
    //printf("your sum is %d\n",sum);
    remainder = sum%1000;
    return remainder;
}