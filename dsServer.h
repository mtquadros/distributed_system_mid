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

    dsServer(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alived);
    ~dsServer() = default;

    //used for threading
    void operator()() const;

private:

    // A std::vector object that eventually will contain messages proposed by all hosts
    // that was able to send their set of proposed messages
    tableOfMessages _tableOfProposed;
    tableOfMessages _tableOfAlived;

    std::set<neighborID> neighbors;

    //To protect valuesReceived from race conditions
    //mutable char buffer[bufferSize];
    std::mutex& _mutex;

};

#endif //SERVER_H
