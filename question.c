#include <stdio.h>

int main() {
    int a[2][2] = {{1,2},{3,4}};
    printf("%p\n",a);
    printf("%p\n",a[0]);
    printf("%p\n",&a[0][0]);

    printf("%d\n",*a);
    printf("%d\n",a[0]);
    printf("%d\n",*a[0]);
    printf("%d\n",a[0][0]);
    return 0;
}