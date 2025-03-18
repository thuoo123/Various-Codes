// Online C compiler to run C program online
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void randoms(int* arr,int index,int min,int max);
void check(int* arr,int* win,int index);
int main() {
    int i;
    int win[6];
    int* arr = (int*)malloc(sizeof(int)*6);
    srand(time(NULL));
    printf("Enter winning numbers:");
    for(i=0;i<6;i++){
        scanf("%d",&win[i]);
    }
    for(i=0;i<6;i++){
        randoms(arr,i,1,49);
    }
    check(arr,win,1);
    
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

void check(int* arr,int* win,int index){
    int count = 0;
    int i,j;
    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            if(win[i] == arr[j]){
                count++;
            }
        }
    }
    printf("%d.You have %d matches, ",index,count);
    if(count<4){
        printf("The numbers: ");
        for(i=0;i<6;i++){
            printf("%d ",arr[i]);
        }
        printf("Did not win\n");
        for(int i=0;i<6;i++){
            randoms(arr,i,1,49);
        }
        check(arr,win,index+1);
    }else{
        printf("The numbers: ");
        for(i=0;i<6;i++){
            printf("%d ",arr[i]);
        }
        printf("Matches all!!!\n");
        
        return;
    }
}
