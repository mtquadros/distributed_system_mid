//
// Created by dev on 10/07/25.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/serialization/map.hpp>
#include <boost/asio.hpp>
#include <string>


using uuidHostId   = boost::uuids::uuid;
using contentType  = int;
constexpr  boost::asio::ip::port_type serverPortNumber = 50130; // server listen on this port
constexpr  boost::asio::ip::port_type  clientPortNumber = 30031; // client listen on this port

constexpr  size_t  numberOfHosts    = 10;
constexpr  std::string localThreadedGroupIp {"127.255.255.255"};
constexpr  std::string localHostsGroupIp {"192.168.1.255"};

using neighborID = boost::asio::ip::port_type;

//Representa uma das linhas uma tabela implementada por multimap
struct messageCore
{
    std::string  memberIpAdrress;
    neighborID   port;  // used at first glance just to simulate the algorithm with many processes in
                        // one host. So the port serves to identify the processes
    uuidHostId   uuidMembertId;
    contentType  contentReceived;
};
//For distributed system simulation in a unique host

// A set of messages proposed by the hosts in the distributed system
// It contains the id of the host whom transmited the message and content proposed by it
using messageMap = std::multimap<neighborID,struct messageCore>;

constexpr  size_t      bufferSize   = sizeof(messageMap) * numberOfHosts;
constexpr  contentType invalidValue = -1;

#endif //DEFINITIONS_H
