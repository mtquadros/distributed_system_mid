//
// Created by dev on 14/07/25.
//

#include <ds/dsClient.hpp>
#include <ds/dsServer.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <mutex>
#include <thread>

#include "ds/heartBeat.hpp"

using namespace boost::asio::ip;

dsClient::dsClient(std::mutex& mutex):_mutex(mutex)
{
        //parameterized constructor
}

/*!
 * TODO: Check all the code to eval if there are a set of instructions that must execute atomic
 * (i.e.) without be preempted by operating system
 */
void dsClient::operator()()
{
    try {
        //Initialize the socket
        boost::asio::io_context io;

        udp::socket socket(io);
        socket.open(udp::v4());

        udp::endpoint multicast_endpoint(make_address(HB::localHostsGroupIp),
                HB::serverPortNumber);
        udp::endpoint local_endpoint(udp::v4(), 0); //creates a localendpoint with port = 0
        socket.bind(local_endpoint);  //forces to define a port on the before call send_to member function

        std::string buffer;
        while (true)
        {
            // Obtem timestamp como número de milissegundos desde epoch
            auto now = std::chrono::high_resolution_clock::now();
            auto time_stamp = std::chrono::duration_cast<std::chrono::seconds>(
                              now.time_since_epoch()).count();

            std::time_t t = static_cast<std::time_t>(time_stamp);

            HB::memberID id = std::to_string(socket.local_endpoint().port());
            // put the data in the output stream ------------------------------------------

            //oss << id << ' ';
            //oss << std::put_time(std::localtime(&t), "%Y-%m-%d__%H:%M:%S") << ' ';
            // escreve no buffer o conteudo do stream
            buffer.clear();
            std::ostringstream oss;
            oss << std::this_thread::get_id();
            buffer.append(oss.str());
            // send the raw data (it is a blocking mode)--MTU limits to 1472 bytes of payload--
            socket.send_to(boost::asio::buffer(buffer), multicast_endpoint);

            // Wait for period between heartbeats
            std::this_thread::sleep_for(HB::periodMillisecs);
        }

    } catch (std::exception& e) {
        std::cerr << "\nClient Error: " << e.what() << std::endl;
    }
}
