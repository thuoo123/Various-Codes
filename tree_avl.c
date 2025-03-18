// AVL tree
#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int item;
    int height;
    struct node* left;
    struct node* right;
}node;

typedef struct qnode{
    node* treenode;
    struct qnode* next;
}qnode;

typedef struct queue{
    qnode* front;
    qnode* rear;
}queue;

void randoms(int* arr,int index,int min,int max);
void insert_node(node** rootptr,int* arr,int n);
node* left_rotate(node* root);
node* newnode(int key);
int max(int a, int b);
int height(node* root);
int find_balance(node* root);
node* left_rotate(node* root);
node* right_rotate(node* root);
void print_level(node* root);
node* dequeue(queue* q);
void enqueue(queue* q,node* root);
int main() {
    int n;
    int i;
    int min,max;
    int* arr;
    node* root = NULL;
    printf("Enter number of nodes:");
    scanf("%d",&n);
    printf("Enter minimum:");
    scanf("%d",&min);
    printf("Enter maximum:");
    scanf("%d",&max);
    arr = (int*)malloc(sizeof(int)*n);
    for(i=0;i<n;i++){
        randoms(arr,i,min,max);
    }
    
    insert_node(&root,arr,n);
    printf("Printing in Level by Level Order:\n");
    print_level(root);

    return 0;
}

void print_level(node* root){
    queue* q = malloc(sizeof(queue));
    q->front = NULL;
    q->rear = NULL;
    enqueue(q,root);
    while(q->front != NULL){
        node* temp = dequeue(q);
        printf("%d(%d) ",temp->item,temp->height);
        if(temp->left != NULL){
            enqueue(q,temp->left);
        }
        if(temp->right != NULL){
            enqueue(q,temp->right);
        }
    }
}

node* dequeue(queue* q){
    if(q->front == NULL){
        return NULL;
    }
    qnode* qn;
    node* treenode;
    qn = q->front;
    treenode = qn->treenode;
    q->front = q->front->next;
    if(q->front == NULL){
        q->rear = NULL;
    }
    free(qn);
    return treenode;
}

void enqueue(queue* q,node* root){
    qnode* qn = (qnode*)malloc(sizeof(qnode));
    qn->treenode = root;
    qn->next = NULL;
    if(q->front == NULL){
        q->front = qn;
        q->rear = qn;
        return;
    }
    q->rear->next = qn;
    q->rear = qn;
}

node* insert(node* root,int key){
    if(root == NULL){
        return newnode(key);
    }
    
    if(key < root->item){
        root->left = insert(root->left,key);
    }else{
        if(key>root->item){
            root->right = insert(root->right,key);
        }else{
            return root;   
        }
    }
    
    root->height = max(height(root->left),height(root->right)) + 1;
    
    int balance = find_balance(root);
    
    if(balance > 1 && key < root->left->item){
        root = right_rotate(root);
    }
    
    if(balance > 1 && key > root->left->item){
        root->left = left_rotate(root->left);
        root = right_rotate(root);
    }
    
    if(balance < -1 && key > root->right->item){
        root = left_rotate(root);
    }
    
    if(balance < -1 && key < root->right->item){
        root->right = right_rotate(root->right);
        root = left_rotate(root);
    }
    
    return root;
}

node* left_rotate(node* root){
    node* x = root->right;
    node* y = x->left;
    
    x->left = root;
    root->right = y;
    
    root->height = max(height(root->left),height(root->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    
    return x;
}

node* right_rotate(node* root){
    node* x = root->left;
    node* y = x->right;
    
    x->right = root;
    root->left = y;
    
    root->height = max(height(root->left),height(root->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;
    
    return x;
}

int find_balance(node* root){
    if(root == NULL){
        return 0;
    }
    return height(root->left) - height(root->right);
}

int height(node* root){
    if(root == NULL){
        return -1;
    }
    return root->height;
}

int max(int a, int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

node* newnode(int key){
    node* temp = (node*)malloc(sizeof(node));
    temp->item = key;
    temp->height = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert_node(node** rootptr,int* arr,int n){
    for(int i=0;i<n;i++){
        *rootptr = insert(*rootptr,arr[i]);
    }
}

void randoms(int* arr,int index,int min,int max){
    int i;
    arr[index] = rand()%(max - min + 1) + min;
    for(i=0;i<index;i++){
        if(arr[i] == arr[index]){
            randoms(arr,index,min,max);
        }
    }
}