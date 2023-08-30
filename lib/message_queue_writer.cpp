// message_queue_writer.cpp

#include "message_queue_writer.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <mqueue.h>
#include <cstring> // For memset
#include <ctime>   // For time and timespec
#include <cerrno>  // For errno
#include <cstdlib> // For exit
#include <thread>  // For std::this_thread::sleep_for
#include <string.h>

int MessageQueueWriter::filename(const char* filename) {

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 33 ;
    attr.mq_curmsgs = 0;

    // Open the message queue for sending
    mqd_t mq = mq_open(filename, O_WRONLY  , 0777 , &attr );
    if (mq == (mqd_t)-1) {

        perror("mq_open send");
        return 1;
        
    }    

    std::cout << "Message queue opened successfully!" << std::endl;
    msgid = mq ;
    return mq ;

}


MessageQueueWriter::MessageQueueWriter() {



}

MessageQueueWriter::~MessageQueueWriter() {
    // Cleanup if needed
     mq_close(msgid);
}

int MessageQueueWriter::writeToMessageQueue(const char *message) {

    // Prepare the message to send
    if (mq_send(msgid, message, sizeof(message)+1 , 0) == -1) {
        perror("mq_send");
        std::cout<<"ERROR HERE "<<std::endl ;
        return 1;
    }
    std::cout << "Message sent: " << message << std::endl;
    mq_close(msgid);
    return 0 ;
}
