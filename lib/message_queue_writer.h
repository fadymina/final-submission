// message_queue_writer.h

#ifndef MESSAGE_QUEUE_WRITER_H
#define MESSAGE_QUEUE_WRITER_H


#define MAX_MESSAGE_SIZE 33

class MessageQueueWriter {
public:
    MessageQueueWriter();
    ~MessageQueueWriter();
    int writeToMessageQueue(const char *message);
    int filename(const char* filename);

private:
    int msgid;

    struct mesg_buffer {
        long mesg_type;
        char mesg_text[MAX_MESSAGE_SIZE];
    };
};

#endif
