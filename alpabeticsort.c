#include <stdio.h>
#include <string.h>

#define MAXDESCLEN 51

int alphabet(char s1[MAXDESCLEN], char s2[MAXDESCLEN]) {
    int i, state = 1;

    for (i = 0; i < MAXDESCLEN; i++) {
        if (s1[i] > s2[i]) {
            state = 0;
        }
    }
    return state;
}

int main() {
    char s1[MAXDESCLEN] = "AAAAR";
    char s2[MAXDESCLEN] = "AAAAC";


    int state;
    state = alphabet(s1, s2);

    printf("s1 vem primeiro alfabeticamente que s2: %d", state);
    
    return 0;
} 