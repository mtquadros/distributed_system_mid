//
// Created by dev on 14/07/25.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <memory>
#include <boost/asio/io_service.hpp>
#include <iostream>
#include "definitions.h"

class dsClient
{
    //public members
    public:

    ~dsClient() = default;

    /*!
    * Parameterized Constructor to allow sharing mutex and tables of proposed values and hosts alive
    * @param  mutex The mutex shared with server class
    * @param  table_of_proposed Table of values proposed by the group of host alive in the system
    * @param  table_of_alived Table of hosts alive
    */
    dsClient(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alived);

    void operator()() const;

    //protected members
    protected:
    std::mutex& _mutex;
    tableOfMessages& _tableOfProposed;
    tableOfMessages& _tableOfAlived;

};


#endif //CLIENT_H
