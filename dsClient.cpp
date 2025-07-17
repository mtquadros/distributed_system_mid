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

dsClient::~dsClient()
{

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

dsClient::dsClient()
{

}

inline void dsClient::propose()
{
}

void dsClient::joinGroup()
{
    try {
        boost::asio::io_context io;
        udp::socket socket(io);
        socket.open(udp::v4());

        // Habilita broadcast no socket
        socket.set_option(boost::asio::socket_base::broadcast(true));

        udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::broadcast(), 30000);
        std::cout << boost::asio::ip::address_v4::broadcast() << std::endl;
        std::string mensagem = "Mensagem de broadcast UDP";

        while (true) {
            socket.send_to(boost::asio::buffer(mensagem), broadcast_endpoint);
            std::cout << "Mensagem enviada: " << mensagem << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    } catch (std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

}



inline void dsClient::leaveGroup()
{
}

inline void dsClient::decide()
{
}