#include <stdio.h>

int main() {
    int num;
    char str[10];

    scanf("%d %[^\n]", &num, str);
    printf("num:%d\n", num);
    printf("str:%s\n", str);


    return 0;
}

