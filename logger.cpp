#include "lib/Logger.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "lib/message_queue_reader.h"
#include <sys/epoll.h>

int main() {

    std::string logFilePath = "./my_logs_oop.txt";
    Logger logger(logFilePath);
    std::string logs = "daemon logger";
    

    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cout << "couldn't open config file "<<std::endl ;
        logger.LogMessage("couldn't open config file ",logs ,LogLevel::ERROR);
        return 1;
    }

    std::vector<std::string> queueNames;
    std::string line;
    while (std::getline(configFile, line)) {
        queueNames.push_back(line);
    }
    configFile.close();

    const int maxQueues = queueNames.size();
    std::cout<<maxQueues<<std::endl;
    MessageQueueReader instanceArray[maxQueues];
    int y = queueNames.size();

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cout << "couldn't create epoll instance "<<std::endl ;
        logger.LogMessage("couldn't create epoll instance ",logs ,LogLevel::ERROR);
        perror("epoll_create1");
        return 1;
    }

    struct epoll_event event[maxQueues];


    for (int x = 0; x < y; x++ ) {
        
        const std::string& queueName = "/"+ queueNames[x];
        int fd1 = instanceArray[x].filename(queueName.c_str() , 1);

        logger.LogMessage("initialized queue named :" + queueName, logs ,LogLevel::TRACE);
        std::cout << "Initialized queue: " << queueName << "\n";

        event[x].data.fd = fd1;
        event[x].events = EPOLLIN;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, instanceArray[x].msgid , &event[x]) == -1) 
        {
            logger.LogMessage("problem with epoll ctl",logs ,LogLevel::ERROR);
            perror("epoll_ctl");
            return 1;
        }

    }

    logger.LogMessage("initialized all queues ",logs ,LogLevel::TRACE);
    

    char message[MAX_MESSAGE_SIZER]; // Allocate memory to store the message
    struct epoll_event epollEvents[maxQueues];

    while (1) {
        
        int num_events = epoll_wait(epoll_fd, epollEvents, maxQueues, -1);

        if (num_events == -1) {
            perror("epoll_wait");
            logger.LogMessage("problem with epoll wait",logs ,LogLevel::ERROR);
            return 1;
        }
        logger.LogMessage("call from message queue(woke from epoll-wait)",logs ,LogLevel::TRACE);

        
        
        for (int i = 0; i < maxQueues; i++) {

        int result = instanceArray[i].readFromMessageQueue(message );
        std::cout << "Received message :  " <<  message << std::endl;            

            if (result == 0) {
                std::cout << "Received message :  " <<  message << std::endl;
                logger.LogMessage( message, " " , LogLevel::TRACE);
            } else if (result == -1) {
                std::cout << "Timeout occurred on fd " <<": No message received." << std::endl;
                logger.LogMessage("Received message : TIMEOUT " , " " , LogLevel::TRACE);
            } else {
                std::cout << "Error occurred while reading from fd " << std::endl;
                logger.LogMessage("Received message :  ERROR ", " " , LogLevel::ERROR);
            }
        }
        
    }
    return 0;
}
