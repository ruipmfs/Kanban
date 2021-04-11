#include <stdio.h>

/* QUICK SORT */

int partition(int lst[], int left, int right) {
    int pivot = lst[left];
    int left_extr = left;
    int i, temp;

    for (i = left + 1; i < right; i++) {
        if (lst[i] < pivot) {
            //swap
            temp = lst[i];
            lst[i] = lst[left_extr];
            lst[left_extr] = temp;

            left_extr += 1;
        }
    }
    //swap
    temp = pivot;
    pivot = lst[left_extr];
    lst[left_extr] = temp;

    return left_extr;
}

void quicksort(int lst[], int left, int right) {
    int pivot;
    if (left < right) {
        pivot = partition(lst, left, right);
        quicksort(lst, left, pivot);
        quicksort(lst, pivot+1, right);
    }
}

int main() {
    int list[20] = {2, 5, 1, 3, 4, 6, 9, 7, 8};
    int lst_counter = 8, right, left;

    right = (lst_counter+1) / 2;
    left = (lst_counter+1) / 2 + (lst_counter+1) % 2;

    printf("r: %d\n", right);
    printf("l: %d\n", left);

    quicksort(list, left, right);

    printf("%d %d %d %d %d %d %d %d %d\n", list[0], list[1], list[2], list[3], list[4], list[5], list[6], list[7], list[8]);

    return 0;
} 
 

