//
// Created by dev on 14/07/25.
//

#ifndef CLIENT_H
#define CLIENT_H
#include "definitions.h"
#include <mutex>
#include <random>


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
    dsClient(std::mutex& mutex);

    void operator()();

    //protected members
    protected:
    heartBeat::memberID _myID;
    std::mutex& _mutex;

}; //class dsClient


#endif //CLIENT_H
