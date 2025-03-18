//Pushing and Popping a Stack Data Structure
#include <stdio.h>
#include <stdlib.h>
#define max 10000
#define min 1

typedef struct node{
    int item;
    struct node* next;

}node;

typedef struct linkedlist{
    node* head;
    int size;
}linkedlist;

typedef struct stack{
    linkedlist ll;
}stack;

void push(stack* stk, int data, int count);
int pop(stack* stk);
void removenode(stack* stk, node* ptr);
int main(){
    stack* s;
    int data;
    int n,i;
    int output;
    printf("Enter number of values to be stored on stack:");
    scanf("%d",&n);
    printf("\n");
    s = malloc(sizeof(stack));
    s->ll.head = NULL;
    for(i=0;i<n;i++){
        data = rand()%(max-min+1) + min;
        printf("Random data %d: %d\n",i+1,data);
        push(s,data,i+1);
    }
    printf("\n");
    printf("size of stack: %d nodes\n",s->ll.size);
    printf("\n");
    for(i=0;i<n;i++){
        output = pop(s);
        printf("Output:%d\n",output);
    }
    
}

void push(stack* stk, int data, int count){
    node* temp;
    temp = malloc(sizeof(node));
    temp->item = data;
    temp->next = NULL;
    if(stk->ll.head == NULL){
        stk->ll.head = temp;
        stk->ll.size = count;
        return;
    }
    temp->next = stk->ll.head;
    stk->ll.head = temp;
    stk->ll.size = count;
}

int pop(stack* stk){
    int item;
    item = stk->ll.head->item;
    removenode(stk,stk->ll.head);
    return item;
}

void removenode(stack* stk, node* ptr){
    node* temp;
    temp = ptr->next;
    free(ptr);
    stk->ll.head = temp;
}