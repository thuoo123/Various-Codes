// Determinant of a matrix and its inverse
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int find_determinant(int** matrix, int size);
int** new_matrix(int** matrix,int size,int i);
int** new_matrix2(int** matrix,int row,int col, int size);
int** find_adj(int** matrix,int size);
float** tranverse(int** ptr,int size);
int main() {
    int size;
    int** matrix;
    int** ptr;
    float** adjucate;
    int** inverse;
    char* arr;
    int i,j;
    int ans;
    
    printf("Enter size of matrix:");
    scanf("%d",&size);
    printf("\n");
    matrix = malloc(sizeof(int*)*size);
    for(i=0;i<size;i++){
        *(matrix+i) = malloc(sizeof(int)*size);
    }
    
    printf("Enter Matrix Values(with spaces between values):\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            scanf("%d",&matrix[i][j]);
        }
    }
    
    printf("\n");
    printf("Your inputted matrix is:\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    ans = find_determinant(matrix,size);
    printf("Your determinant is %d\n",ans);
    if(ans == 0){
        printf("Your matrix inputted in not invertible");
        return 3;
    }
    ptr = find_adj(matrix,size);
    for(i=0;i<size;i++){
        free(matrix[i]);
    }
    free(matrix);
    adjucate = tranverse(ptr,size);
    for(i=0;i<size;i++){
        free(ptr[i]);
    }
    free(ptr);
    printf("\n");
    printf("Your inverse matrix:\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("%.3f  ",adjucate[i][j]/ans);
        }
        printf("\n");
        printf("\n");
    }
    for(i=0;i<size;i++){
        free(adjucate[i]);
    }
    free(adjucate);
    return 0;
}

int find_determinant(int** matrix, int size){
    int** ptr;
    int sum = 0;
    if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    }
    for(int i=0;i<size;i++){
        ptr = new_matrix(matrix,size-1,i);
        if(i%2 == 0){
            sum = sum + matrix[0][i]*find_determinant(ptr,size-1);
        }else{
            sum = sum - matrix[0][i]*find_determinant(ptr,size-1);
        }
        for(int j=0;j<size-1;j++){
            free(ptr[j]);
        }
        free(ptr);
    }
    return sum;
}

int** new_matrix(int** matrix,int size,int i){
    int** ptr;
    int k,j,l;
    ptr = malloc(sizeof(int*)*size);
    for(k=0;k<size;k++){
        *(ptr+k) = malloc(sizeof(int)*size);
    }
    
    if(i == 0){
        for(k=0;k<size;k++){
            for(j=0;j<size;j++){
                ptr[k][j] = matrix[k+1][j+1];
            }
        }
    }
    
    if(i == size){
        for(k=0;k<size;k++){
            for(j=0;j<size;j++){
                ptr[k][j] = matrix[k+1][j];
            }
        }
    }
    
    if(i>0 && i<size){
        for(k=0;k<size;k++){
            l=0;
            for(j=0;j<size+1;j++){
                if(j != i){
                    ptr[k][l] = matrix[k+1][j];
                    l++;
                }
            }
        }
    }
    return ptr;
}

int** find_adj(int** matrix,int size){
    int** ptr = (int**)malloc(sizeof(int*)*size);
    int** ptr2;
    int i,j,k;
    for(i=0;i<size;i++){
        ptr[i] = (int*)malloc(sizeof(int)*size);
    }
    
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            ptr2 = new_matrix2(matrix,i,j,size-1);
            if((j+i)%2 == 0){
                ptr[i][j] = find_determinant(ptr2,size-1);
            }else{
                ptr[i][j] = -find_determinant(ptr2,size-1);
            }
            for(k=0;k<size-1;k++){
                free(ptr2[k]);
            }
            free(ptr2);
        }
    }
    return ptr;
}

float** tranverse(int** ptr,int size){
    int i,j;
    float** trans = (float**)malloc(sizeof(float*)*size);
    for(i=0;i<size;i++){
        trans[i] = (float*)malloc(sizeof(float)*size);
    }
    
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            trans[i][j] = ptr[j][i]; 
        }
    }
    
    return trans;
}

int** new_matrix2(int** matrix,int row,int col, int size){
    int** ptr = (int**)malloc(sizeof(int*)*size);
    int i,j,k,m,l;
    for(i=0;i<size;i++){
        ptr[i] = (int*)malloc(sizeof(int)*size);
    }
    
    if(row == 0 && col == 0){
        for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                ptr[i][j] = matrix[i+1][j+1];
            }
        }    
    }
    
    if(row == size && col == 0){
        for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                ptr[i][j] = matrix[i][j+1];
            }
        }    
    }
    
    if(row == 0 && col == size){
       for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                ptr[i][j] = matrix[i+1][j];
            }
        }     
    }
    
    if(row == size && col == size){
        for(i=0;i<size;i++){
            for(j=0;j<size;j++){
                ptr[i][j] = matrix[i][j];
            }
        }    
    }
    
    if((row == 0) && (col != 0 && col != size )){
        for(i=0;i<size;i++){
            k = 0;
            for(j=0;j<size+1;j++){
                if(j != col){
                    ptr[i][k] = matrix[i+1][j];
                    k++;
                }else{
                    continue;
                }
            }
        }    
    }
    
    if((row == size) && (col != 0 && col != size )){
        for(i=0;i<size;i++){
            k = 0;
            for(j=0;j<size+1;j++){
                if(j != col){
                    ptr[i][k] = matrix[i][j];
                    k++;
                }else{
                    continue;
                }
            }
        }    
    }
    
    if((col == 0) && (row != 0 && row != size )){
        for(i=0;i<size+1;i++){
            if(i<=row){
                for(j=0;j<size;j++){
                    if(i != row){
                        ptr[i][j] = matrix[i][j+1];
                    }else{
                        break;
                    }
                }
            }else{
                for(j=0;j<size;j++){
                        ptr[i-1][j] = matrix[i][j+1];
                }
            }
        }
    }
    
    if((col == size) && (row != 0 && row != size )){
        for(i=0;i<size+1;i++){
            if(i<=row){
                for(j=0;j<size;j++){
                    if(i != row){
                        ptr[i][j] = matrix[i][j];
                    }else{
                        break;
                    }
                }
            }else{
                for(j=0;j<size;j++){
                        ptr[i-1][j] = matrix[i][j];
                }
            }
        }
    }
    
    if((row != 0 && row != size) && (col != 0 && col != size)){
        m = 0;
        for(i=0;i<size+1;i++){
            l=0;
            for(j=0;j<size+1;j++){
                if((i != row ) && (j != col)){
                    if(i<=row){
                        ptr[m][l] = matrix[i][j];
                        l++;
                    }else{
                        ptr[m-1][l] = matrix[i][j];
                        l++;
                    }
                }else{
                    if(i == row){
                        break;
                    }
                    if(j == col){
                        continue;
                    }
                }
            }
            m++;
        }
    }
    return ptr;
}