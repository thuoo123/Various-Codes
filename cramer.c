// Cramer's rule
#include <stdio.h>
#include <stdlib.h>

float determinant(float** matrix,int n);
float** new_matrix(float** matrix,int size,int pos);
float** cramer_matrix(float** coeff,int n,float* last,int pos);
int main() {
    int n;
    float** matrix;
    float** coeff;
    float** cramer;
    float* last_col;
    int i,j;
    float answer1;
    float answer2;
    char* arr;
    printf("Enter number of variables:");
    scanf("%d",&n);
    matrix = (float**)malloc(sizeof(float*)*n);
    for(i=0;i<n;i++){
        *(matrix+i) = (float*)malloc(sizeof(float)*(n+1));
    }
    coeff = (float**)malloc(sizeof(float*)*n);
    for(i=0;i<n;i++){
        *(coeff+i) = (float*)malloc(sizeof(float)*n);
    }
    arr = (char*)malloc(sizeof(char)*n);
    for(i=0;i<n;i++){
        arr[i] = 'a' + i;
    }
    arr[n] = ' ';
    last_col = (float*)malloc(sizeof(float)*n);
    printf("Enter the equations row by row:\n");
    for(i=0;i<n;i++){
        for(j=0;j<=n;j++){
            scanf("%f",&matrix[i][j]);
        }
    }
    printf("Your inputted equation is as follows:\n");
    for(i=0;i<n;i++){
        for(j=0;j<=n;j++){
            if(matrix[i][j]>0 && j == 0){
                printf("%.2f%c ",matrix[i][j],arr[j]);
                continue;
            }
            if(matrix[i][j]<0 && j != n){
                printf("%.2f%c ",matrix[i][j],arr[j]);
            }
            if(matrix[i][j]>0 && j != n){
                printf("+ %.2f%c ",matrix[i][j],arr[j]);
            }
            if(matrix[i][j] == 0 && j != n){
                continue;
            }
            if(j == n){
                printf("= %.2f%c ",matrix[i][j],arr[j]);
            }
          
        }
        printf("\n");
    }
    for(i=0;i<n;i++){
        last_col[i] = matrix[i][n];
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            coeff[i][j] = matrix[i][j];
        }
    }
    answer1 = determinant(coeff,n);
    if(answer1 == 0){
        printf("determinant of coefficient matrix is 0!");
        return 1;
    }
    for(i=0;i<n;i++){
        cramer = cramer_matrix(coeff,n,last_col,i);
        answer2 = determinant(cramer,n);
        printf("%c = %.3f\n",arr[i],answer2/answer1);
        for(j=0;j<n;j++){
            free(cramer[j]);
        }
        free(cramer);
    }
    for(i=0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
    for(i=0;i<n;i++){
        free(coeff[i]);
    }
    free(coeff);
}

float** cramer_matrix(float** coeff,int n,float* last,int pos){
    int i,j;
    float** temp = (float**)malloc(sizeof(float*)*n);
    for(i=0;i<n;i++){
        temp[i] = (float*)malloc(sizeof(float)*n);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            temp[i][j] = coeff[i][j];
        }
    }
    for(i=0;i<n;i++){
        temp[i][pos] = last[i];
    }
    return temp;
}

float determinant(float** matrix,int n){
    int i,j;
    float sum = 0;
    float** small;
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

float** new_matrix(float** matrix,int size,int pos){
    float** small;
    int i,j;
    small = (float**)malloc(sizeof(float*)*size);
    for(i=0;i<size;i++){
        small[i] = (float*)malloc(sizeof(float)*size);
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