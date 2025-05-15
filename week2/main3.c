#include <stdio.h>


void sort(int *array, int n, int (*compare)(int, int)) {
    int i, j, tmp;
    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
        if (compare(array[j], array[j+1]) > 0) {
          tmp = array[j];
          array[j] = array[j+1];
          array[j+1] = tmp;
        }
      }
    }
  }



int ascending(int a, int b) {
    return a - b;
}

int descending(int a, int b) {
    return b - a;
}

int main() {
    int numbers[] = {5, 2, 8, 1, 9};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int i;

    // Sorting in ascending order.
    sort(numbers, n, ascending);
    printf("Ascending order:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Reset the array for descending sort.
    int numbersDesc[] = {5, 2, 8, 1, 9};

    // Sorting in descending order.
    sort(numbersDesc, n, descending);
    printf("Descending order:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", numbersDesc[i]);
    }
    printf("\n");

    return 0;
}