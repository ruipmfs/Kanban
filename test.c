#include <stdio.h>
#include <string.h>


typedef struct {
        char name[20];
    } Test;

int main() {

    Test ola[10];

    strcpy(ola[0].name, "ONE");
    strcpy(ola[1].name, "TWO");
    strcpy(ola[2].name, "THREE");
    strcpy(ola[3].name, "FOUR");

    printf("%s\n%s\n%s\n%s\n%s\n", ola[0].name, ola[1].name, ola[2].name, ola[3].name, ola[4].name);

    return 0;
}