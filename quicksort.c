#include <stdio.h>

int list[9] = {2, 5, 1, 3, 4, 6, 9, 7, 8};

/* QUICK SORT */
/*int partition(int list[], int start, int end) {
    int pivot = list[start], i = start, j = end, temp;

    while (j > i) {
        while (list[i] < pivot && i <= end)
            i++;
        while (list[j] > pivot && j >= 0)
            j++;
        if (j > i) {
            temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
    }
    list[i] = list[j];
    list[j] = pivot;
    return j;
}*/

int partition(int list[], int start, int end) {
    int pivot = list[end], i = start, temp, j;
    for (j = start; j < end; j++) {
        if (list[j] <= pivot) {
            temp = list[j];
            list[j] = list[i];
            list[i] = temp;
            i += 1;
        }
    }
    temp = list[end];
    list[end] = list[i];
    list[i] = temp;
    return i;
}


void quicksort(int list[], int left, int right) {
    int part;
    if (right > left) {
        part = partition(list, left, right);

        quicksort(list, left, part-1);
        quicksort(list, part+1, right);
    }
}

int main() {
    int list_counter = 8, right, left;

    int list[20] = {2, 5, 1, 3, 4, 6, 9, 7, 8};

    quicksort(list, 0, list_counter);

    printf("%d %d %d %d %d %d %d %d %d\n", list[0], list[1], list[2], list[3], list[4], list[5], list[6], list[7], list[8]);

    return 0;
} 