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

    /*!
    * Parameterized Constructor to allow sharing mutex and tables of proposed values and hosts alive
    * @param  mutex The mutex shared with server class
    * @param  table_of_proposed Table of values proposed by the group of host alive in the system
    * @param  table_of_alived Table of hosts alive
    */
    dsServer(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alive);
    ~dsServer() = default;

    //used for threading
    void operator()() const;

private:

    // A std::vector object that eventually will contain messages proposed by all hosts
    // that was able to send their set of proposed messages
    tableOfMessages _tableOfProposed;
    tableOfMessages _tableOfAlive;

    std::set<neighborID> neighbors;

    //To protect valuesReceived from race conditions
    //mutable char buffer[bufferSize];
    std::mutex& _mutex;

};

#endif //SERVER_H
