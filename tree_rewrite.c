#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node* left;
    struct node* right;
    struct node* next;
} node;

typedef struct queueNode {
    node* treeNode;
    struct queueNode* next;
} queueNode;

typedef struct queue {
    queueNode* front;
    queueNode* rear;
} queue;

int rands(int max, int min,int last,int* m);
void createnode(node*,node*);
void printnode(node* head);
void enqueue(queue* q, node* treeNode);
node* dequeue(queue* q);
void print_level(node* head);
int finddepth(node* head, int final,int count);
int find_height(node* ptr,int cur);
int max(int l,int r);
node* find_node(node* head,int target);
void find_descendants(node* init,node* cur,int k, int c);
int main() {
    node* head = NULL;
    node** headptr = &head;
    int i;
    int j,n;
    int k,k2;
    int random;
    int target;
    int* arr;
    node* temp;
    int dest;
    int depth,height;
    node* descend;
    printf("Enter range of random numbers below:\n");
    printf("Enter lower bound:");
    scanf("%d",&j);
    printf("Enter upper bound:");
    scanf("%d",&n);
    printf("Enter number of nodes in binary tree:");
    scanf("%d",&k);
    arr = malloc(sizeof(int)*k);
    if(k>(n - j + 1)){
        printf("ERROR!!!");
        return 1;
    }
    for(i=0;i<k;i++){
        random = rands(n,j,i,arr);
        printf("%d ",random);    
    }
    printf("\n");
    for(i=0;i<k;i++){
        temp = malloc(sizeof(node));
        temp->item = arr[i];
        temp->left = NULL;
        temp->right = NULL;
        temp->next = NULL;
        if(head == NULL){
            head = temp;
            continue;
        }
        createnode(head,temp);
    }
    
    printnode(head);
    printf("\n");
    printf("Enter node to find its depth:");
    scanf("%d",&dest);
    depth = finddepth(head,dest,0);
    printf("The depth is %d\n", depth);
    printf("Enter number to find in tree:");
    scanf("%d",&target);
    descend = find_node(head,target);
    printf("Enter the Kth descendant of %d:",descend->item);
    scanf("%d",&k2);
    find_descendants(descend,descend,k2,0);
    
    printf("Enter another/same number to find in tree:");
    scanf("%d",&target);
    descend = find_node(head,target);
    height = find_height(descend,0);
    printf("the height of %d:%d\n",target,height);
    
    //For level by level traversal
    print_level(head);

    
}

void enqueue(queue* q, node* treeNode) {
    queueNode* newQueueNode = (queueNode*)malloc(sizeof(queueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newQueueNode;
        return;
    }
    q->rear->next = newQueueNode;
    q->rear = newQueueNode;
}

node* dequeue(queue* q) {
    if (q->front == NULL)
        return NULL;
    queueNode* temp = q->front;
    node* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return treeNode;
}

void print_level(node* head) {
    if (head == NULL)
        return;
    queue* q = (queue*)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    enqueue(q, head);
    while (q->front != NULL) {
        node* temp = dequeue(q);
        printf("%d ", temp->item);
        if (temp->left != NULL)
            enqueue(q, temp->left);
        if (temp->right != NULL)
            enqueue(q, temp->right);
    }
    printf("\n");
}

int rands(int max, int min,int last,int* m){
    int ans;
    ans = rand()%(max - min + 1) + min;
    *(m+last) = ans;
    for(int s=0;s<last;s++){
        if(ans == *(m+s)){
            ans = rands(max,min,last,m);
        }
    }
    return ans;
}

void createnode(node* head,node* ptr){
    if(ptr->item < head->item){
        if(head->left ==  NULL){
            head->left = ptr;
            return;
        }
        createnode(head->left,ptr);
    }else{
        if(head->right ==  NULL){
            head->right = ptr;
            return;
        }
        createnode(head->right,ptr);
    }
}

void printnode(node* head){
    if(head == NULL){
        return;
    }
    printnode(head->left);
    printf("%d ",head->item);
    printnode(head->right);
}

int finddepth(node* head, int final,int count){
    int l,r;
    
    if(head == NULL){
        return 0;
    }
    
    if(final == head->item){
        return count;
    }
    
    if(final<head->item){
       count = finddepth(head->left,final,count+1);
    }else{
        count = finddepth(head->right,final,count+1);
    }
    
    return count;
}

node* find_node(node* head,int target){
    node* ptr = head;
    while(head != NULL){
        if(head->item == target){
            printf("Yes! Present\n");
            return head;
        }else{
            if(target > head->item){
                head = head->right;
            }else{
                head = head->left;
            }
        }
    }
    
    if(head == NULL){
        printf("Not found, pls try again.\n");
        printf("enter new target value:");
        scanf("%d",&target);
        find_node(ptr,target);   
    }
}

void find_descendants(node* init,node* cur,int k, int c){
    if(cur == NULL){
        return;
    }
    
    if(c == k){
        printf("The descendants of %d:",init->item);
        printf("%d\n",cur->item);
        return;
    }
    
    if(c<k){
        find_descendants(init,cur->left,k,c+1);
        find_descendants(init,cur->right,k,c+1);
    }
}

int find_height(node* ptr, int cur){
    int l,r;
    if(ptr == NULL){
        return -1;
    }
    l = find_height(ptr->left,cur+1);
    r = find_height(ptr->right,cur+1);
    
    return max(l,r) + 1;

}

int max(int l,int r){
    if(l == r){
        return l;
    }
    
    if(l>r){
        return l;
    }else{
        return r;
    }
}