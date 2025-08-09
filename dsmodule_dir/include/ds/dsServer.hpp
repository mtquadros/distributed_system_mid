//!
//! Created by Mauricio T. Quadros on 10/07/25.
//! mauriciotq@gmail.com
//!

#ifndef SERVER_H
#define SERVER_H

#include <ds/definitions.hpp>
#include <mutex>

class dsServer
{
public:

    /*!
    * Parameterized Constructor to allow sharing mutex and tables of proposed values and hosts alive
    * @param  mutex The mutex shared with server class
    * @param  table_of_alived Table of hosts alive
    */
    dsServer(heartBeat::memberID& member, std::mutex& mutex, heartBeat::tblOfAlive& table_of_alive);
    ~dsServer() = default;

    //! used for threading
    void operator()();

private:
    heartBeat::memberID& _myID;
    heartBeat::tblOfAlive& _tableOfAlive;


    //To protect valuesReceived from race conditions
    std::mutex& _mutex;

}; //class dsServer

#endif //SERVER_H
