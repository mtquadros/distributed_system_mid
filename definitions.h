//
// Created by dev on 10/07/25.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <fstream>

// include headers that implement a archive in simple text format
#include <boost/asio.hpp>
#include <map>
#include <chrono>
#include <mutex>


/*!
 * Set to false switch the behaviour of the system for working in simulation mode in a single host
 * with many threads, if it is set to true change to remote mode with many host connect by a local network
 */
#define REMOTE_DISTRIBUTED_SYSTEM  false
namespace heartBeat
{
    //using uuidHostId = boost::uuids::uuid;
    using hostPort   = std::string;
    using hostIP     = std::string;

    constexpr  boost::asio::ip::port_type serverPortNumber = 50130; // server listen on this port
    constexpr  size_t  numberOfHosts    = 10;
    constexpr  std::string localHostsGroupIp ("239.255.0.1");
/*!
 *  Use to define the type of the ID
 */
#if REMOTE_DISTRIBUTED_SYSTEM == true
    using memberID = hostIP;
    using neighborID = hostIP;
#elif REMOTE_DISTRIBUTED_SYSTEM == false
    using memberID = hostPort;
    using neighborID = memberID;
#else
#    error "Missing #define REMOTE_DISTRIBUTED_SYSTEM directive to true or false"
#endif

    using timestamp_t  = std::time_t;

    using controlFlag   = int64_t;

    const controlFlag flag = 0x0101010101010101;

    constexpr uint8_t buffer_size = 128;
    // ---------------------------------------------------------------------------
    using tblOfBeats  = std::multimap<timestamp_t, controlFlag>;
    using tblOfAlive  = std::map<neighborID, tblOfBeats>;
    //-----------------------------------------------------------------------------
    using rowOfAlive  = std::pair<neighborID, tblOfBeats>;
    using rowOfBeats  = std::pair<timestamp_t, controlFlag>;

    constexpr  std::chrono::milliseconds  periodMillisecs(3000);

    void printTable(std::mutex& mutex, const tblOfAlive& table_of_alive);

} //namespace message

#endif //DEFINITIONS_H
