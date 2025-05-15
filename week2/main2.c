#include <stdio.h>
int add1(int a, int b) { return a * 10 + b; }
int add2(int a, int b) { return a + b * 10; }

int main() {
    // Declare a function pointer
    int (*operation)(int, int);

    // Prompt user to choose a function
    int choice;
    printf("Choose function: 1 for add1, 2 for add2: ");
    scanf("%d", &choice);

    // Assign the chosen function to the function pointer
    if (choice == 1) {
        operation = add1;
    } else if (choice == 2) {
        operation = add2;
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    // Call the chosen function
    printf("Result: %d\n", operation(3, 4));

    return 0;
}