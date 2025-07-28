//
// Created by dev on 14/07/25.
//

#include "dsClient.h"
#include "definitions.h"
#include <iostream>
#include <boost/asio.hpp>
#include <mutex>

using namespace boost::asio::ip;

dsClient::dsClient(heartBeat::memberID& member, std::mutex& mutex, heartBeat::tblOfAlive& table_of_alive):
                _myID(member), _mutex(mutex), _tableOfAlive(table_of_alive)
{
        //parameterized constructor
}

void dsClient::operator()()
{
    try {
        //Initialize the socket
        boost::asio::io_context io;

        udp::socket socket(io);
        socket.open(udp::v4());

        udp::endpoint multicast_endpoint(address::from_string(heartBeat::localHostsGroupIp),
                heartBeat::serverPortNumber);

        //Defines the ID of the host in the distributed system platform
        {
            std::lock_guard<std::mutex> lock1(_mutex);
            _myID = std::to_string(multicast_endpoint.port());
        }
        std::string buffer;
        while (true)
        {
            //buffer.resize(heartBeat::buffer_size);
            std::ostringstream oss;  // Nao tem tamanho pre-definido, primeiro se escreve nele, depois coloca em um beffer
            // prepare the timestamp format
            // Obtem timestamp como número de milissegundos desde epoch
            auto now = std::chrono::high_resolution_clock::now();
            auto time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                              now.time_since_epoch()).count();
            // put the data in the output stream ------------------------------------------
            {
                std::lock_guard<std::mutex> lock(_mutex);
                oss << _myID << " ";
            }

            oss << time_stamp << " " << heartBeat::flag << " ";
            {
                std::lock_guard<std::mutex> lock(_mutex);
                std::cout << "--------------------------------------------------" << std::endl;
                std::cout << "Cliente [ " << socket.local_endpoint() << " ] enviando :" << std::endl;
                std::cout << _myID << std::endl;
                std::cout << time_stamp  << std::endl;
                std::cout << heartBeat::flag << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;
            }
            // escreve no buffer o conteudo do stream
            buffer.clear();
            buffer += oss.str();
            // send the raw data --------------------------------
            socket.send_to(boost::asio::buffer(buffer), multicast_endpoint);

            // Wait for period between heartbeats
            std::this_thread::sleep_for(heartBeat::periodMillisecs);

        }

    } catch (std::exception& e) {
        std::cerr << "\nClient Error: " << e.what() << std::endl;
    }
}
