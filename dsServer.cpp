//
// Created by dev on 05/07/25.
//

#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <sstream>
#include <iostream>
#include <string>
#include <thread>
#include <shared_mutex>
#include "dsServer.h"
#include <memory>
#include <boost/asio.hpp>
#include "definitions.h"

using boost::asio::ip::udp;

void dsServer::operator()() const
{
    try {
        boost::asio::io_context io;

        // Socket para receber no endereço ANY e porta 30001
        udp::endpoint listen_endpoint(udp::v4(), 30001);
        udp::socket socket(io);
        socket.open(listen_endpoint.protocol());
        socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        socket.bind(listen_endpoint);

        // Junta-se ao grupo multicast 239.255.0.1
        boost::asio::ip::address multicast_address = boost::asio::ip::make_address("239.255.0.1");
        socket.set_option(boost::asio::ip::multicast::join_group(multicast_address));

        char buffer[1024];
        udp::endpoint sender_endpoint;

        std::cout << "Servidor ouvindo multicast..." << std::endl;

        while (true) {
            size_t bytes_received = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
            std::unique_lock<std::mutex> lock(_mutex);
            std::cout << "Recebido de " << sender_endpoint << ": ";
            std::cout.write(buffer, bytes_received);
            std::cout << std::endl;
        }

    } catch (std::exception& e) {
        std::cerr << "\nErro: " << e.what() << "\n";
    }
}


dsServer::dsServer(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alive): _mutex(mutex),
                _tableOfProposed(table_of_proposed), _tableOfAlive(table_of_alive)
{

}




