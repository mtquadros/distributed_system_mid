//!
//! Created by Mauricio T. Quadros on 10/07/25.
//! mauriciotq@gmail.com
//!

#ifndef SERVER_H
#define SERVER_H

#include <ds/definitions.hpp>
#include <shared_mutex>

class dsServer
{
public:

    /*!
    * Parameterized Constructor to allow sharing mutex and tables of proposed values and hosts alive
    * @param  mutex The mutex shared with server class
    * @param  table_of_alived Table of hosts alive
    */
    dsServer(HB::memberID& member, std::shared_mutex& mutex, HB::tblOfAlive& table_of_alive);
    ~dsServer() = default;

    //! used for threading
    void operator()();

private:
    HB::memberID& _myID;
    HB::tblOfAlive& _tableOfAlive;


    //To protect valuesReceived from race conditions
    std::shared_mutex& _mutex;

}; //class dsServer

#endif //SERVER_H
