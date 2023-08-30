// message_queue_reader.h
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring> // For memset
#include <ctime>   // For time and timespec
#include <cerrno>  // For errno
#include <cstdlib> // For exit
#include <thread>  // For std::this_thread::sleep_for
#include <sys/epoll.h>
#include <unistd.h>
#include <mqueue.h>

#ifndef MESSAGE_QUEUE_READER_H
#define MESSAGE_QUEUE_READER_H

#define MAX_MESSAGE_SIZER 50

class MessageQueueReader {
public:
    MessageQueueReader();
    ~MessageQueueReader();
    int readFromMessageQueue(char* message);
    int filename(const char* filename , bool sync );
    int msgid;
    const char* appname ;

private:
    char receivedMessage[MAX_MESSAGE_SIZER];


};

#endif
