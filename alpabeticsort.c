#include <stdio.h>
#include <string.h>

#define MAXDESCLEN 51

int alphabet(char s1[], char s2[]) {
    int i;

    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] > s2[i]) {
            return 0;
        }
        else if (s1[i] < s2[i]) {
            return 1;
        }
    }
    return 1;
}

int main() {
    char s1[MAXDESCLEN] = "rui";
    char s2[MAXDESCLEN] = "sofia";

    int state;
    state = alphabet(s1, s2);

    printf("%s vem primeiro alfabeticamente que %s: %d", s1, s2, state);
    
    return 0;
} 