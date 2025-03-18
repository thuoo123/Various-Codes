#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node* next;
}node;
node* findnode(node*,int);
void insertnode(node* pre);
int main(){
    node* head = NULL;
    node* temp;
    node* ptr;
    node* ptr2;
    int i = 0;
    int n;
    int index;
    int index2;
    printf("enter numbers of lists:");
    scanf("%d",&n);
    printf("\n");
    //To construct a List of n nodes
    while((i != -1) && i<n){
        temp = malloc(sizeof(node));
        temp->next = NULL;
        if(head == NULL){       
            head = temp;
        }else{
            ptr = head;
            while(ptr->next != NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
        }
        temp->item = i;
        i++;
    }
    //Printing out the list, forward traversal
    for(ptr=head;ptr != NULL;ptr = ptr->next){
        printf("numbers: %d\n",ptr->item);
    }

    printf("enter the position of node(1,2,3,...):");
    scanf("%d",&index);
    ptr2 = findnode(head,index-1);
    printf("%d\n",ptr2->item);
    printf("insert new node between which 2 nodes?\n");
    scanf("%d",&index2);
    printf("between %d node & %d node\n",index2,index2+1);
    printf("\n");
    insertnode(findnode(head,index2 - 1));
    for(ptr=head;ptr != NULL;ptr = ptr->next){
        printf("numbers: %d\n",ptr->item);
    }
}

node* findnode(node* head2,int index2){
    if(head2 == NULL || index2<0){
        return NULL;
    }
    
    while(index2>0){
        head2 = head2->next;
        if(head2 == NULL){
            return NULL;
        }
        index2--;
    }
    return head2;
}

void insertnode(node* pre){
    node* cur;
    int k;
    cur = malloc(sizeof(node));
    printf("Enter value to insert:");
    scanf("%d",&k);
    printf("\n");
    cur->item = k;
    cur->next = pre->next;
    pre->next = cur;
}