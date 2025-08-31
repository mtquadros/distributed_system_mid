//
// Created by dev on 14/07/25.
//

#include <ds/dsClient.hpp>
#include <ds/dsServer.hpp>
#include <iostream>
#include <thread>
#include <ds/message.hpp>


using namespace boost::asio::ip;

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

        while (true)
        {
            /*message* _message = message::getNewInstance();
            std::string id;
            id.append(socket.local_endpoint().address().to_string());
            id.append(":");
            id.append(std::to_string(socket.local_endpoint().port()));
            _message->setMessageType(message::MsgType::Heartbeat);
            _message->setMessageMemberID(id);
            */
            // put the data in the output stream ------------------------------------------

            std::ostringstream oss;
            oss << socket.local_endpoint().address().to_string();
            oss << ":" << socket.local_endpoint().port();
            // send the raw data (it is a blocking mode)--MTU limits to 1472 bytes of payload--
            socket.send_to(boost::asio::buffer(oss.str()), multicast_endpoint);

            // Wait for period between heartbeats
            std::this_thread::sleep_for(HB::periodMillisecs);
        }

    } catch (std::exception& e) {
        std::cerr << "\nClient Error: " << e.what() << std::endl;
    }
}
