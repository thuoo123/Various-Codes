// Fibonacci Sequence Implementation
#include <stdio.h>
#include <stdlib.h>
void fibo(long* k,int n);
int main() {
    int num;
    long* arr;
    printf("enter no of terms:\n");
    scanf("%d",&num);
    if(num<1){
        printf("ERROR!");
        return 1;
    }
    arr = malloc(num*sizeof(long));
    if(arr == NULL){
        printf("UH OH!");
        return 1;
    }
    fibo(arr,num);
    for(int i=0;i<num;i++){
        printf("%ld ",arr[i]);
    }
    free(arr);
    return 0;
}

void fibo(long* k,int n){
    int i;
    if(n ==1){
        *k = 1;
    }
    
    if(n == 2){
        *k = 1;
        *(k+1) = 1;
    }
    if(n>2){
        *k = 1;
        *(k+1) = 1;
        for(i=2;i<n;i++){
            *(k+i) = *(k+i-1) + *(k+i-2);
        }
    }
}