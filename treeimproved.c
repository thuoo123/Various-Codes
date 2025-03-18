#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int item;
    struct tree* left;
    struct tree* right;
}tree;

int random_int(int n,int* k,int i,int min,int max);
int countnodes(tree* head,int count);
void descendants(tree* initial,tree* ptr,int k,int c);
void createtree(tree* head,tree* temp);
void print_tree(tree* head);
tree* find_node(tree* head,int key,int min,int max);
int main() {
    tree* root = NULL;
    tree** rootptr = &root;
    int* arr;
    int n,i,k;
    int c = 0;
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
        tree* temp = malloc(sizeof(tree));
        temp->item = random;
        temp->left = NULL;
        temp->right = NULL;
        if(root == NULL){
            root = temp;
            continue;
        }
        createtree(root,temp);
    }
    printf("\n");
    printf("\n");
    print_tree(root);
    printf("\n");
    printf("Input a number from %d to %d:",min,max);
    scanf("%d",&guess);
    tree* ptr = find_node(root,guess,min,max);
    printf("\n");
    printf("Number of nodes:%d\n",countnodes(root,0));
    printf("Find which generation descendants of %d:",ptr->item);
    scanf("%d",&k);
    descendants(ptr,ptr,k,c);
    return 0;
    
}

void createtree(tree* head,tree* temp){

        if(temp->item<head->item){
            if(head->left != NULL){
                createtree(head->left,temp);
                
            }else{
                head->left = temp;
            }
            
        }else{
             if(head->right != NULL){
                createtree(head->right,temp);
                
            }else{
                head->right = temp;
            }
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

tree* find_node(tree* head,int key,int min,int max){
    tree* ptr = head;
    int new;
    while(head != NULL){
        if(head->item == key){
            printf("YES! Number is found");
            return head;
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

int countnodes(tree* head,int count){
    if(head == NULL){
        return 0;
    }
    
    int l = countnodes(head->left,count);
    int r = countnodes(head->right,count);
    
    return l + r + 1;
}

void descendants(tree* initial,tree* ptr,int k,int c){
    
    if(ptr == NULL){
        printf("No descendants left!\n");
        return;
    }
    
    if(c == k){
        printf("the %dth descendant of %d is:%d\n",k,initial->item,ptr->item);
        return;
    }
    
    if(c<k){
        descendants(initial,ptr->left,k,c+1);
        descendants(initial,ptr->right,k,c+1);
    }
}