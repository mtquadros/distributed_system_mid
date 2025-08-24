//
// Created by dev on 14/07/25.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <ds/definitions.hpp>
#include <shared_mutex>
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

    explicit dsClient(HB::memberID& id): _myID(id){ };

    void operator()();

    //protected members
    protected:
    HB::memberID _myID;

}; //class dsClient


#endif //CLIENT_H
