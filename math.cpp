#include <stdio.h>
#include <limits.h> // For INT_MAX
#include <string.h>  // Include the string.h header for strcmp
#include <stdlib.h>  // Include the stdlib.h header for atoi
#include "lib/message_queue_writer.h"
#include "lib/math_functions.h"
#include <iostream>
#include <stdlib.h>  // For the itoa function

int main(int argc, char *argv[]) {

    MessageQueueWriter writer;
    writer.filename("/maths1111");

    if (argc < 2) {
        printf("Insufficient arguments. Usage: YourProgramName [operation] [operand1] [operand2]\n");
        return 1;
    }
    
    char *operation = argv[1];
    
    if (strcmp(operation, "--help") == 0) {
        displayHelp();
        return 0;
    }
    
    if (argc < 4) {
        printf("Insufficient arguments. Usage: YourProgramName [operation] [operand1] [operand2]\n");
        return 1;
    }
    
    int operand1 = atoi(argv[2]);
    int operand2 = atoi(argv[3]);
    int result ;
    
    if (strcmp(operation, "--add") == 0) {
        result = add(operand1, operand2);
    } else if (strcmp(operation, "--subtract") == 0) {
        result = subtract(operand1, operand2);
    } else if (strcmp(operation, "--multiply") == 0) {
        result = multiply(operand1, operand2);
    } else if (strcmp(operation, "--sqrt") == 0) {
        result = calculateSquareRoot(operand1);
    } else {
        printf("Invalid operation.\n");
        return 1;
    }

    std::string tobesend =   operation  ; 
    tobesend += std::to_string(operand1)   ;
    tobesend += std::to_string(operand2) ;
    tobesend += " = " ;
    tobesend += std::to_string(result) ;
    tobesend += "\0" ;

    writer.writeToMessageQueue(tobesend.c_str());
    
    return 0;
}

