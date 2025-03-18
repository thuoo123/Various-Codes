//Binary tree practice
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node* left;
    struct node* right;
}node;

void randoms(int* arr,int index,int min,int max);
void create_tree(node* head, node* temp);
void print_tree(node* root);
int count_node(node* head);
node* find_node(node* root,node* head,int key);
void descendants(node* unit,int count, int gen);
int height_tree(node* head);
int max(int l,int r);
int depth_tree(node* root,int count,int target);
int main() {
    int i,j;
    int n;
    int max,min;
    int total;
    int find;
    int parent,gen;
    int height;
    int depth,location;
    int* arr;
    node* root = NULL;
    node* temp;
    node* ptr;
    printf("Enter number of values to be generated:");
    scanf("%d",&n);
    printf("Enter range of values(inclusive):\n");
    printf("Enter minimum:");
    scanf("%d",&min);
    printf("Enter maximum:");
    scanf("%d",&max);
    arr = (int*)malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        randoms(arr,i,min,max);
    }
    for(i=0;i<n;i++){
        temp = (node*)malloc(sizeof(node));
        temp->item = arr[i];
        temp->left = NULL;
        temp->right = NULL;
        if(root == NULL){
            root = temp;
            continue;
        }
        create_tree(root,temp);
    }
    
    print_tree(root);
    printf("\n");
    total = count_node(root);
    printf("Number of nodes is:%d\n",total);
    printf("Enter number to find:");
    scanf("%d",&find);
    find_node(root,root,find);
    printf("Enter another number to find its descendants:");
    scanf("%d",&parent);
    printf("Enter no. of generations down from %d:",parent);
    scanf("%d",&gen);
    ptr = find_node(root,root,parent);
    descendants(ptr,0,gen);
    height = height_tree(root);
    printf("The height of tree:%d\n",height);
    printf("Enter number in tree to find its depth:");
    scanf("%d",&location);
    depth = depth_tree(root,0,location);
    printf("the depth of %d is:%d",location,depth);
    return 0;
}

void randoms(int* arr,int index,int min,int max){
    int i;
    arr[index] = rand()%(max-min+1) + min;
    for(i=0;i<index;i++){
        if(arr[index] == arr[i]){
            randoms(arr,index,min,max);
        }
    }
    
}

void create_tree(node* head, node* temp){
    if(temp->item < head->item){
        if(head->left == NULL){
            head->left = temp;
            return;
        }
        create_tree(head->left,temp);
    }else{
        if(head->right == NULL){
            head->right = temp;
            return;
        }
        create_tree(head->right,temp);
    }
}

void print_tree(node* root){
    if(root == NULL){
        return;
    }
    
    print_tree(root->left);
    printf("%d ",root->item);
    print_tree(root->right);
}

int count_node(node* head){
    if(head == NULL){
        return 0;
    }
    
    int l = count_node(head->left);
    int r = count_node(head->right);
    
    return l + r + 1;
}

node* find_node(node* root,node* head,int key){
    
    if(head != NULL){
        if(head->item == key){
            printf("%d is Found!\n",key);
            return head;
        }
    
        if(head != NULL){
            if(key < head->item){
                find_node(root,head->left,key);
            }else{
                find_node(root,head->right,key);
            }
        }
    }else{
        printf("The number %d is not found!\n",key);
        printf("Please Enter a new number:");
        scanf("%d",&key);
        find_node(root,root,key);
    }
}

void descendants(node* unit,int count, int gen){
    if(unit == NULL){
        return;
    }
    
    if(count == gen){
        printf("the %d heir is %d\n",gen,unit->item);
        return;
    }
    
    if(count<gen){
        descendants(unit->left,count+1,gen);
        descendants(unit->right,count+1,gen);
    }
}

int height_tree(node* head){
    if(head == NULL){
        return -1;
    }
    
    int l = height_tree(head->left);
    int r = height_tree(head->right);
    
    int c = max(l,r) + 1;
    
    return c;
}

int max(int l,int r){
    if(l>r){
        return l;
    }else{
        return r;
    }
}

int depth_tree(node* root,int count,int target){
    if(root == NULL){
        return 0;
    }
    
    if(root->item == target){
        return count;
    }else{
        if(target < root->item){
            return depth_tree(root->left,count+1,target);
        }else{
            return depth_tree(root->right,count+1,target);
        }
    }
    
}