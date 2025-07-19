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

        // Cria um endpoint local na porta 30000
        udp::endpoint listen_endpoint(udp::v4(), serverPortNumber);

        // Abre o socket
        udp::socket socket(io);
        socket.open(listen_endpoint.protocol());

        // Permite reuso de endereço para evitar erro "address already in use"
        socket.set_option(boost::asio::socket_base::reuse_address(true));

        // Liga o socket ao endpoint
        socket.bind(listen_endpoint);

        std::cout << "Servidor aguardando mensagens broadcast na porta " <<  serverPortNumber << "...\n";

        // Buffer para receber dados
        char buffer[1024];
        udp::endpoint remetente;

        while (true) {
            //size_t bytes = socket.receive_from(boost::asio::buffer(buffer), remetente);
            size_t bytes = socket.receive(boost::asio::buffer(buffer));
            std::cout << "\nRecebido de " << remetente.address().to_string()
                      << ":" << remetente.port()
                      << " => " << std::string(buffer, bytes) << "\n";
        }

    } catch (std::exception& e) {
        std::cerr << "\nErro: " << e.what() << "\n";
    }
}


dsServer::dsServer(std::mutex& mutex, tableOfMessages& table_of_proposed, tableOfMessages& table_of_alived): _mutex(mutex),
                _tableOfProposed(table_of_proposed), _tableOfAlived((table_of_alived))
{

}




