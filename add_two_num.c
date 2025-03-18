#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
}node;


int find_last(char* num,int count,int length);
void create_node(node* head,int last);
int find_size(node* head);
int add_list(node* head,int size);
void printnode(node* head,int label);
int main() {
    node** l;
    node* temp;
    node* ptr;
    node* final = NULL;
    char num[101];
    int size[2];
    int sum = 0;
    int i,j,k;
    int arr[20];
    int last;
    
    l = malloc(sizeof(node*)*2);
    for(i=0;i<2;i++){
        l[i] = NULL;
        printf("Enter numbers in list %d:",i+1);
        scanf("%s",num);
        if(strlen(num)<1 && strlen(num)>100){
            printf("Ensure number has between 1 to 100 digits inclusive");
            return 1;
        }
        for(j=0;j<strlen(num);j++){
            last = find_last(num,j,strlen(num));
            if(l[i] == NULL){
                temp = malloc(sizeof(node));
                l[i] = temp;
                temp->data = last;
                temp->next = NULL;
                temp->prev = NULL;
                continue;
            }
            create_node(l[i],last);
        }
    }
    
    
    for(i=0;i<2;i++){
         printnode(l[i],i+1);
    }
    
    for(i=0;i<2;i++){
        size[i] = find_size(l[i]);
        printf("size %d:%d\n",i+1,size[i]);
    }
    
    for(i=0;i<2;i++){
        sum = sum + add_list(l[i],(size[i]-1));
    }
    
    printf("%d\n",sum);
    for(i=0;i<20;i++){
        arr[i] = 99;
    }
    j = 0;
    while(sum > 0){
        arr[j] = sum%10;
        sum = sum/10;
        j++;
    }
    j=0;
    while(arr[j] != 99){
        printf("%d",arr[j]);
        j++;
    }
    k=0;
    while(arr[k] != 99){
        temp = malloc(sizeof(node));
        temp->data = arr[k];
        temp->next = NULL;
        temp->prev = NULL;
        if(final == NULL){
            final = temp;
            k++;
            continue;
        }else{
            ptr = final;
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
            temp->prev = ptr;
            k++;
        }
    }
    
    printnode(final,3);
    return 0;
}

void printnode(node* head,int label){
    node* ptr = head;
    printf("List %d:",label);
    while(ptr != NULL){
        printf("%d",ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}

int find_last(char* num,int count,int length){
    int ans;
    return num[length - (count + 1)] - '0';
    
}

void create_node(node* head,int last){
    node* temp = malloc(sizeof(node));
    temp->data = last;
    temp->next = NULL;
    temp->prev = NULL;
    node* ptr = head;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = temp;
    temp->prev = ptr;
}

int find_size(node* head){
    node* ptr = head;
    int size = 0;
    while(ptr != NULL){
        ptr = ptr->next;
        size++;
    }
    return size;
}

int add_list(node* head,int size){
    node* ptr = head;
    int sum = 0;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    
    while(ptr != NULL){
        sum = sum + (ptr->data)*pow(10,size);
        size = size - 1;
        ptr = ptr->prev;
    }
    
    return sum;
}