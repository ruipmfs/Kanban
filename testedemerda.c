#include <stdio.h>

#define MAXDESCLEN 51
#define MAXID 1000
#define MAXUSERS 50
#define MAXACT 10
#define MAXACTLEN 21
#define MAXUSERLEN 21
#define MAXTASKS 10000

typedef struct {
    int id, duration, start_inst;
    char description[MAXDESCLEN], user, activity[MAXACTLEN];
} Task;

int alphabet(char s1[], char s2[]) {
    int i;

    for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++) {
        if (s1[i] > s2[i]) {
            return 0;
        }
    }
    return 1;
}

int partitionByAlphabet(Task list[], int start, int end) {
    /* AUX Func. of the quicksort algorithm.
       Defines a pivot and sort the list given in the input by putting
       the minor numbers (num < pivot) on the left side of the pivot
       and the major numbers (num < pivot) on the right side of the pivot */
    int i = start, j = end-1;
    Task pivot = list[end], temp;

    while (i < j) {
        while (alphabet(list[i].description, pivot.description) && i < j)
            i++;
        while (!alphabet(list[j].description, pivot.description) && j > i)
            j--;
        
        if (i < j) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    temp = list[i];
    list[i] = list[end];
    list[end] = temp;
    return i;
}

void sortByAlphabet(Task list[], int left, int right) {
    /* Main func. of the sprt algorithm.
       Divides the array and call itself by recursion with the
       splitted array */
    int part;
    if (right > left) {
        part = partitionByAlphabet(list, left, right);

        sortByAlphabet(list, left, part-1);
        sortByAlphabet(list, part+1, right);
    }
}

int main() {
    
}