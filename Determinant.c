// Determinant
#include <stdio.h>
#include <stdlib.h>

int determinant(int** matrix,int n);
int** new_matrix(int** matrix,int size,int pos);
int main() {
    int size;
    int** matrix;
    int i,j;
    int answer;
    printf("Enter size of matrix:");
    scanf("%d",&size);
    matrix = (int**)malloc(sizeof(int*)*size);
    for(i=0;i<size;i++){
        *(matrix+i) = (int*)malloc(sizeof(int)*size);
    }
    printf("Enter the matrix:\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    printf("Your inputted matrix is as follows:\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    answer = determinant(matrix,size);
    printf("Your determinant:%d",answer);
    for(i=0;i<size;i++){
        free(matrix[i]);
    }
    free(matrix);
}

int determinant(int** matrix,int n){
    int i,j;
    int sum = 0;
    int** small;
    if(n == 2){
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    }
    
    for(i=0;i<n;i++){
        if(i%2 == 0){
            small = new_matrix(matrix,n-1,i);
            sum = sum + matrix[0][i]*determinant(small,n-1);
            for(j=0;j<n-1;j++){
                free(small[j]);
            }
            free(small);
        }else{
            small = new_matrix(matrix,n-1,i);
            sum = sum - matrix[0][i]*determinant(small,n-1);
            for(j=0;j<n-1;j++){
                free(small[j]);
            }
            free(small);
        }
    }
    return sum;
}

int** new_matrix(int** matrix,int size,int pos){
    int** small;
    int i,j;
    small = (int**)malloc(sizeof(int*)*size);
    for(i=0;i<size;i++){
        small[i] = (int*)malloc(sizeof(int)*size);
    }
    for(i=0;i<size;i++){
        for(j=0;j<size+1;j++){
            if(j == pos){
                continue;
            }else{
                small[i][j] = matrix[i+1][j];
            }
            if(j > pos){
                small[i][j-1] = matrix[i+1][j];
            }
        }
    }
    
    return small;
}