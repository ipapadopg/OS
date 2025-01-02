#include <stdio.h>

// Add function
int add(int *a, int *b, int *c) {
    return *a + *b + *c;
}

int main() {
    int x, y, z;

    // Wait for the user to input 3 integers
    printf("Please enter 3 integers: ");
    scanf("%d %d %d", &x, &y, &z);

    // Call the add function
    int result = add(&x, &y, &z);
    printf("%d + %d + %d = %d\n", x, y, z, result);

    return 0;
}
