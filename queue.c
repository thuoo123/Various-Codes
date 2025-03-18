//Pushing and Popping a Queue Data Structure
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

typedef struct queue{
    linkedlist ll;
}queue;

void enqueue(queue* , int , int );
int dequeue(queue* );
void removenode(queue*, node* );
int main(){
    queue* s;
    int data;
    int n,i;
    int output;
    printf("Enter number of values to be stored on stack:");
    scanf("%d",&n);
    printf("\n");
    s = malloc(sizeof(queue));
    s->ll.head = NULL;
    for(i=0;i<n;i++){
        data = rand()%(max-min+1) + min;
        printf("Random data %d: %d\n",i+1,data);
        enqueue(s,data,i+1);
    }
    printf("\n");
    printf("size of stack: %d nodes\n",s->ll.size);
    printf("\n");
    for(i=0;i<n;i++){
        output = dequeue(s);
        printf("Output:%d\n",output);
    }
    
}

void enqueue(queue* q, int data, int count){
    node* temp;
    temp = malloc(sizeof(node));
    temp->item = data;
    temp->next = NULL;
    if(q->ll.head == NULL){
        q->ll.head = temp;
        q->ll.size = count;
        return;
    }
    node* ptr = q->ll.head;
    while(ptr->next !=NULL){
        ptr = ptr->next;
    }
    ptr->next = temp;
    q->ll.size = count;
}

int dequeue(queue* q){
    int item;
    item = q->ll.head->item;
    removenode(q,q->ll.head);
    return item;
}

void removenode(queue* q, node* ptr){
    node* temp;
    temp = ptr->next;
    free(ptr);
    q->ll.head = temp;
}