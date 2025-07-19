//
// Created by dev on 14/07/25.
//

#include "dsClient.h"
#include "definitions.h"
#include <iostream>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/multicast.hpp>
#include <boost/asio.hpp>


using namespace boost::asio::ip;

dsClient::dsClient(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alived): _mutex(mutex),
                _tableOfProposed(table_of_proposed), _tableOfAlived((table_of_alived))
{
        //parameterized constructor
}

void dsClient::operator()() const
{
    try {
        boost::asio::io_context io;

        udp::endpoint multicast_endpoint(
            boost::asio::ip::make_address("239.255.0.1"), 30001
        );

        udp::socket socket(io, udp::v4());

        int counter = 0;
        while (true)
        {
            std::string mensagem = std::to_string(++counter);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            socket.send_to(boost::asio::buffer(mensagem), multicast_endpoint);
            std::lock_guard<std::mutex> lock(_mutex);
            std::cout << "Mensagem ( " << mensagem << " ) enviada para " << multicast_endpoint << std::endl;
        }


    } catch (std::exception& e) {
        std::cerr << "\nErro: " << e.what() << std::endl;
    }
}
