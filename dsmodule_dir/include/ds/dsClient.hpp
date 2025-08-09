//
// Created by dev on 14/07/25.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <ds/definitions.hpp>
#include <mutex>
#include <random>


//!  dsClient is a class that transmit the heartbeat and data to reach consensus
/*!
 * Constructor: dsClient(std::mutex& mutex)
 * Parameterized Constructor is explicit to receive a reference to a mutex that is
 * shared with dsServer and manageTable classes.
 * @param  mutex The mutex shared with dsServer class
*/
class dsClient
{
    //public members
    public:
    ~dsClient() = default;

    explicit dsClient(std::mutex& mutex);

    void operator()();

    //protected members
    protected:
    heartBeat::memberID _myID;
    std::mutex& _mutex;

}; //class dsClient


#endif //CLIENT_H
