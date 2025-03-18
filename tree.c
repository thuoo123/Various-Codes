#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int item;
    struct tree* left;
    struct tree* right;
}tree;

int random_int(int n,int* k,int i,int min,int max);
void createtree(tree** head,int data);
void print_tree(tree* head);
void find_node(tree* head,int key,int min,int max);
int main() {
    tree* root = NULL;
    tree** rootptr = &root;
    int* arr;
    int n,i;
    int ans;
    int random;
    int guess;
    int min,max;
    printf("enter number of nodes in binary search tree:");
    scanf("%d",&n);
    printf("\n");
    printf("Please enter range of random Integers to insert into the Binary Tree:\n");
    printf("Lower Bound:");
    scanf("%d",&min);
    printf("Upper Bound:");
    scanf("%d",&max);
    
    if((max-min+1)<n){
        printf("Error!");
        return 1;
    }
    
    
    arr = malloc(n*sizeof(int));
    
    if(arr == NULL){
        printf("Memory Allocation failed");
        return 1;
    }
    
    for(i=0;i<n;i++){
        arr[i] = -99;
    }
    
    for(i=0;i<n;i++){
        random = random_int(n,arr,i,min,max);
        createtree(rootptr,random);
    }
    printf("\n");
    printf("\n");
    print_tree(root);
    printf("\n");
    printf("Input a number from %d to %d:",min,max);
    scanf("%d",&guess);
    find_node(root,guess,min,max);
    return 0;
}

void createtree(tree** head,int data){
    tree* ptr;
    tree* temp = malloc(sizeof(tree));
    temp->item = data;
    temp->left = NULL;
    temp->right = NULL;
    if(*head == NULL){
        *head =temp;
        return;
    }
    ptr = *head;
    while((ptr->left != NULL) || (ptr->right != NULL)){
        if(ptr->left == NULL && ptr->right != NULL){
            if(temp->item >= ptr->item){
                ptr = ptr->right;
                continue;
            }
            if(temp->item < ptr->item){
                break;
            }
        }
        
        if(ptr->left != NULL && ptr->right == NULL){
            if(temp->item >= ptr->item){
                break;
            }
            if(temp->item < ptr->item){
                ptr = ptr->left;
                continue;
            }
        }
        
        if(temp->item >= ptr->item){
            ptr = ptr->right;
            continue;
        }
        
        if(temp->item < ptr->item){
            ptr = ptr->left;
        }
    }
    
    if(temp->item >= ptr->item){
        ptr->right = temp;
    }else{
        ptr->left = temp;
    }
    
}

void print_tree(tree* head){
    tree* cur = head;
    if(cur == NULL){
        return;
    }
    
    print_tree(cur->left);
    printf("%d ",cur->item);
    print_tree(cur->right);
}

int random_int(int n,int* k,int i,int min,int max){
    int ran;
    ran = rand()%(max - min + 1) + min;
    for(int m=0;m<i;m++){
        if(*(k + m) == ran){
            ran = random_int(n,k,i,min,max);
        }
    }
    *(k+i) = ran;
    printf("Number:%d ", ran);
    return ran;
    
}

void find_node(tree* head,int key,int min,int max){
    tree* ptr = head;
    int new;
    while(head != NULL){
        if(head->item == key){
            printf("YES! Number is found");
            break;
        }else{
            if(key > head->item){
                head = head->right;
            }else{
                head = head->left;
            }
        }
    }
    
    if(head == NULL){
        printf("Number not found\n");
        printf("Input a number again from %d to %d:",min,max);
        scanf("%d",&new);
        find_node(ptr, new,min,max);
    }
}