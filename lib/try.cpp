#include <stdio.h>
#include <limits.h> // For INT_MAX
#include <string.h>  // Include the string.h header for strcmp
#include <stdlib.h>  // Include the stdlib.h header for atoi
#include "message_queue_writer.h"
#include <iostream>
#include <stdlib.h>  // For the itoa function
#include "message_queue_reader.h"


int main()
{
    MessageQueueWriter writer;
    writer.filename("/fdfd");
    writer.writeToMessageQueue("WORKING or NOT");

    char message[100];

    MessageQueueReader reader ;
    reader.filename("/fdfd" , 0);
    int result = reader.readFromMessageQueue(message );
    std::cout << "Received message :  " <<  message << std::endl;

    return 0 ;






}