//
// Created by dev on 05/07/25.
//

#include <sstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "dsServer.h"
#include <boost/asio.hpp>
#include <boost/asio/ip/multicast.hpp>
#include "definitions.h"
#include <cassert>
using boost::asio::ip::udp;

void dsServer::operator()()
{
    try {
        boost::asio::io_context context;

        udp::socket socket(context);

        socket.open(udp::v4());

        udp::endpoint listen_endpoint(udp::v4(),heartBeat::serverPortNumber);
        socket.set_option(udp::socket::reuse_address(true));
        socket.bind(listen_endpoint);


        socket.set_option(boost::asio::ip::multicast::join_group(
        boost::asio::ip::make_address(heartBeat::localHostsGroupIp)));


        /*! Junta-se ao grupo multicast definido pelo ip multicast e porta (aleatória disponível)
         *  TODO: Criar um meio de comunicação em outra porta pré-determinada para troca de valores propostos
         *  TODO: Criar uma porta pré-determinada de servidor para multicast
         */


        std::cout << "Servidor ouvindo multicast..." << std::endl;

        // Cria uma string para ser utilizada como buffer pelo socket
        std::array<char, heartBeat::buffer_size> buffer;
        udp::endpoint sender_endpoint;
        while (true) {
            buffer.fill(0);
            size_t bytes_received = socket.receive_from(boost::asio::buffer(buffer),sender_endpoint);

            // Transforma dados brutos em input string stream
            std::string data(buffer.data(), bytes_received);
            std::istringstream iss(data);

            heartBeat::memberID member_id;
            heartBeat::timestamp_t timestamp;
            heartBeat::controlFlag ctrlFlag;

            iss >> member_id;
            iss >> timestamp;
            iss >> ctrlFlag;

            {
                std::lock_guard<std::mutex> lock(_mutex);
                std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
                std::cout << "Server receiving from: " << sender_endpoint << std::endl;
                std::cout << "Bytes Received: " << bytes_received << std::endl;
                std::cout <<  member_id << std::endl;
                std::cout << timestamp << std::endl;
                std::cout << ctrlFlag << std::endl;
                std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
                //std::chrono::local_t time_stamp;
            }

            //std::unique_lock<std::mutex> lock(_mutex);
            // --- update the table -------------------------------------------
            //heartBeat::tblOfBeats& beats = _tableOfAlive[id.c_str()];
            // ctrlFlag was design to provided some autenticity
            //beats.emplace(timeToken, ctrlFlag);
            //_mutex.unlock();
            // -----------------------------------------------------------------
        }
    } catch (std::exception& e) {
        std::cerr << "\nSERVER Erro: " << e.what() << "\n";
    }
}

dsServer::dsServer(heartBeat::memberID& member, std::mutex& mutex, heartBeat::tblOfAlive& table_of_alive):
                _myID(member), _mutex(mutex), _tableOfAlive(table_of_alive)
{

}




