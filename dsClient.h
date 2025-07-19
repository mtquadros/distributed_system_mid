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

    /*! Parameterized Constructor to support sharing of the mutex and the table
     *  of
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
