#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Enter_matrix(char* arr, int** matrix, int j, int size);
int find_determinant(int** matrix, int size);
int** new_matrix(int** matrix, int size, int i);

int main() {
    int size;
    int** matrix;
    char* arr;
    int i, j;
    int determinant;

    printf("Enter size of matrix:");
    scanf("%d", &size);

    matrix = (int**)malloc(sizeof(int*) * size);
    for (i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * size);
    }

    for (j = 0; j < size; j++) {
        arr = (char*)malloc(sizeof(char) * (size + 1));
        printf("Enter values in row %d:", j + 1);
        scanf("%s", arr);
        if (strlen(arr) != size) {
            printf("Enter exactly %d numbers!\n", size);
            return 1;
        }
        Enter_matrix(arr, matrix, j, size);
        free(arr); 
    }
    printf("\n");

    printf("Your input matrix is:\n");
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    determinant = find_determinant(matrix, size);
    printf("The determinant is: %d\n", determinant);

    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

void Enter_matrix(char* arr, int** matrix, int j, int size) {
    for (int i = 0; i < size; i++) {
        matrix[j][i] = arr[i] - '0';  
    }
}

int find_determinant(int** matrix, int size) {
    int** ptr;
    int sum = 0;

    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    }

    for (int i = 0; i < size; i++) {
        ptr = new_matrix(matrix, size, i);
        if (i % 2 == 0) {
            sum += matrix[0][i] * find_determinant(ptr, size - 1);
        } else {
            sum -= matrix[0][i] * find_determinant(ptr, size - 1);
        }
        for (int k = 0; k < size - 1; k++) {
            free(ptr[k]);
        }
        free(ptr);
    }

    return sum;
}

int** new_matrix(int** matrix, int size, int i) {
    int** ptr = (int**)malloc(sizeof(int*) * (size - 1));
    for (int k = 0; k < size - 1; k++) {
        ptr[k] = (int*)malloc(sizeof(int) * (size - 1));
    }

    if (i == 0) {
        for (int k = 0; k < size - 1; k++) {
            for (int j = 0; j < size - 1; j++) {
                ptr[k][j] = matrix[k + 1][j + 1];
            }
        }
    } else if (i == size - 1) {
        for (int k = 0; k < size - 1; k++) {
            for (int j = 0; j < size - 1; j++) {
                ptr[k][j] = matrix[k + 1][j];
            }
        }
    } else {
        for (int k = 0; k < size - 1; k++) {
            int l = 0;
            for (int j = 0; j < size; j++) {
                if (j != i) {
                    ptr[k][l] = matrix[k + 1][j];
                    l++;
                }
            }
        }
    }

    return ptr;
}
