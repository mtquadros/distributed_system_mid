//
// Created by dev on 10/07/25.
//

#ifndef SERVER_H
#define SERVER_H

#include "definitions.h"
#include <atomic>
#include <set>

class dsServer
{
public:

    dsServer();
    ~dsServer();

    //used for threading
    void operator()() const;

    void listen();
private:

    inline void deliver();
    // A std::vector object that eventually will contain messages proposed by all hosts
    // that was able to send their set of proposed messages
    messageMap mapOfMessagesProposed;
    std::set<neighborID> neighbors;

    //To protect valuesReceived from race conditions
    mutable char buffer[bufferSize];


};

#endif //SERVER_H
