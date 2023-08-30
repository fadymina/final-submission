#include "math_functions.h"
#include <stdio.h>
#include <math.h>

int64_t add(int32_t operand1, int32_t operand2) {
    int64_t result = (int64_t)operand1 + operand2;
    printf("Addition Result: %ld\n", result);
    return result;
}

int32_t subtract(int32_t operand1, int32_t operand2) {
    int32_t result = operand1 - operand2;
    printf("Subtraction Result: %d\n", result);
    return result;
}

double calculateSquareRoot(int64_t num) {
    if (num < 0) {
        printf("Invalid Input for Square Root Calculation\n");
        return -1.0;
    }
    double result = sqrt((double)num);
    printf("Square Root Result: %lf\n", result);
    return result;
}

int64_t multiply(int32_t operand1, int32_t operand2) {
    int64_t result = (int64_t)operand1 * operand2;
    printf("Multiplication Result: %ld\n", result);
    return result;
}

void displayHelp() {
    printf("Usage: YourProgramName [operation] [operand1] [operand2]\n");
    printf("Operations:\n");
    printf("  --add      : Perform addition\n");
    printf("  --subtract : Perform subtraction\n");
    printf("  --multiply : Perform multiplication\n");
    printf("  --sqrt     : Calculate square root\n");
}

