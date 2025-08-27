//
// Created by dev on 05/07/25.
//

#include <sstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <ds/dsServer.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/multicast.hpp>
#include <ds/definitions.hpp>
#include <ds/heartBeat.hpp>

using boost::asio::ip::udp;

void dsServer::operator()()
{
    try
    {
        boost::asio::io_context context;

        udp::socket socket(context);

        socket.open(udp::v4());

        socket.set_option(udp::socket::reuse_address(true));
        udp::endpoint listen_endpoint(udp::v4(), HB::serverPortNumber);
        socket.bind(listen_endpoint);

        socket.set_option(boost::asio::ip::multicast::join_group(
            boost::asio::ip::make_address(HB::localHostsGroupIp)));

        /*! Junta-se ao grupo multicast definido pelo ip multicast e porta (aleatória disponível)
         *  TODO: Criar um meio de comunicação em outra porta pré-determinada para troca de valores propostos
         *  TODO: Criar uma porta pré-determinada de servidor para multicast
         */

        // Cria uma string para ser utilizada como buffer pelo socket
        // TODO: Replace array by std::string
        std::array<char, HB::buffer_size> buffer;
        udp::endpoint sender_endpoint;
        while (true)
        {
            buffer.fill(0);
            size_t bytes_received = socket.receive_from(boost::asio::buffer(buffer), sender_endpoint);
            // Transforma dados brutos em input string stream
            std::string xstr;
               try
               {
                   xstr.append(sender_endpoint.address().to_string());

               }
               catch (const std::exception& e)
               {
                   std::cout << e.what() << std::endl;

               }
            xstr.append(":");
            xstr.append(std::to_string(sender_endpoint.port()));
            HeartBeat heartbeat;
            std::string data(buffer.data(), bytes_received);
            std::istringstream iss(data);
            iss >> heartbeat;
            std::unique_lock<std::shared_mutex> write(_mutex);
           //_tableOfAlive[heartbeat.getMemberID()] = heartbeat.getTimeStamp();
           _tableOfAlive[xstr] = heartbeat.getTimeStamp();
            write.unlock();
            // -----------------------------------------------------------------
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "\nSERVER Erro: " << e.what() << "\n";
        showpos(std::cerr);
    }
}

dsServer::dsServer(HB::memberID& member, std::shared_mutex& mutex, HB::tblOfAlive& table_of_alive):
    _myID(member), _mutex(mutex), _tableOfAlive(table_of_alive)
{
}




