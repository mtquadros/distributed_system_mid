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

/*!
 * Parameterized Constructor to allow sharing mutex and tables of proposed values and host alived
 * @param - mutex shared with server class
 *        - table of values proposed by the group of host alive in the system
 *        - table of host alive
 */
dsClient::dsClient(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alived): _mutex(mutex),
                _tableOfProposed(table_of_proposed), _tableOfAlived((table_of_alived))
{
        //parameterized constructor
}

void dsClient::operator()() const
{
    try {
        boost::asio::io_context io;
        udp::socket socket(io);
        socket.open(udp::v4());

        // Habilita broadcast no socket
        socket.set_option(boost::asio::socket_base::broadcast(true));

        udp::endpoint broadcast_endpoint(boost::asio::ip::make_address_v4(localThreadedGroupIp), serverPortNumber);

        // Consulta o endpoint local usado
        int counter = 0;
        while (true) {
            std::string data(std::to_string(++counter));
            socket.send_to(boost::asio::buffer(data), broadcast_endpoint);
            udp::endpoint local = socket.local_endpoint();
            std::cout << "\nMensagem broadcast UDP " << data << " enviada de " << local.address().to_string() << ", Port: " << local.port() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

    } catch (std::exception& e) {
        std::cerr << "\nErro: " << e.what() << std::endl;
    }}
