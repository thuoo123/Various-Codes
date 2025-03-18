#include <stdio.h>
#include <string.h>
int main() {
    char arr[300];
    int l;
    int i;
    printf("enter a number chain:\n");
    scanf("%s",&arr);
    printf("number chain input: %s",arr);
    printf("\n");
    l = strlen(arr);
    printf("Reverse number chain:");
    for(i=l-1;i>=0;i--){
        printf("%c",arr[i]);
    }
    return 0;
}