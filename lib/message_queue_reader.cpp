#include "message_queue_reader.h"

MessageQueueReader::MessageQueueReader(){} ;

int MessageQueueReader::filename(const char* filename , bool sync) {

    mqd_t mq_receive1;
/*
    if(sync)
    { mq_receive1 = mq_open(filename , O_RDONLY | O_CREAT , 0777 , NULL );}

    else    
    { mq_receive1 = mq_open(filename, O_RDONLY | O_CREAT | O_NONBLOCK ,  0777 , NULL );}
*/

    mq_receive1 = mq_open(filename , O_RDONLY | O_CREAT , 0777 , NULL );

   // Open the message queue for receiving
    //mqd_t mq_receive1 = mq_open(filename, O_RDONLY | O_CREAT  , 0644 , NULL );
    if (mq_receive1 == (mqd_t)-1) {
        perror("mq_open receive");
        return 1;
    }
    msgid = mq_receive1 ;
    //appname = filename ;
    return 0 ;

    
}

MessageQueueReader::~MessageQueueReader() {

    mq_close(msgid);

}

int MessageQueueReader::readFromMessageQueue(char* message ) {

    
    char received_message[500];  // Adjust the buffer size as needed
    unsigned int prio;          // Priority of the received message

    if (mq_receive(msgid, received_message, sizeof(received_message), &prio) == -1) {
        perror("mq_receive");
        return 1;
    }

    std::cout<<"RECIEVED MESSAGE IS "<<received_message<<"AND SIZE IS "<<sizeof(received_message)<<std::endl ;

    strncpy(message, received_message, sizeof(received_message));
    message[sizeof(received_message) - 1] = '\0';  // Null-terminate the message
    //std::cout<<appname<<std::endl;
    

    return 0 ;

}
        






