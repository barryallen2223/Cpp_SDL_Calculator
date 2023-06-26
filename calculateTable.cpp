#include <iostream>

int main() {
    int m = 0, b = 0;
    printf("y = mx + b\n--------------------------\n");

    printf("m: ");
    scanf("%d", &m);

    printf("b: ");
    scanf("%d", &b);
    
    int positiveSamples[10][2];
    printf("Positive samples\n");
    printf("------+------\n");
    printf("|  x  |  y  | \n");
    printf("------+------\n");
    for(int x = 0 ; x < 10 ; x++) {
        int y = (m * x) + b;
        positiveSamples[x][0] = x;
        positiveSamples[x][1] = y;
        if (y < 10) {
            printf("|  %d  |  %d  |\n", x, y);
        } else {
            printf("|  %d  |  %d |\n", x, y);
        }
    }
    printf("------+------\n");
    
    int negativeSamples[9][2];
    printf("Negative samples\n");
    printf("------+-------\n");
    printf("|  x  |   y  | \n");
    printf("------+-------\n");
    for(int x = 1 ; x < 10 ; x++) {
        int y = (m * (x * -1)) + b;
        negativeSamples[x-1][0] = x;
        negativeSamples[x-1][1] = y;
        if (y < 10) {
            printf("|  %d  |  %d  |\n", x, y);
        } else {
            printf("|  %d  |  %d |\n", x, y);
        }
    }
    printf("------+-------\n");

    // Print the stored values for positive samples
    printf("\nPositive samples stored in the array:\n");
    for (int i = 0; i < 10; i++) {
        printf("x = %d, y = %d\n", positiveSamples[i][0], positiveSamples[i][1]);
    }

    // Print the stored values for negative samples
    printf("\nNegative samples stored in the array:\n");
    for (int i = 0; i < 9; i++) {
        printf("x = %d, y = %d\n", negativeSamples[i][0], negativeSamples[i][1]);
    }

}