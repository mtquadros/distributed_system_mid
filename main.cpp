#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <ds/dsClient.hpp>
#include <ds/dsServer.hpp>
#include <ds/definitions.hpp>
#include <ds/manageTable.hpp>

#include <ds/heartBeat.hpp>
#include <sstream>
#include <locale>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    std::setlocale(LC_ALL, "pt_BR.UTF_8");
    std::mutex mutex;
    HB::tblOfAlive tbl_of_alive;
    HB::memberID myMemberID;

    manageTable printer(mutex, tbl_of_alive);
    //must have movable/copiable constructor to work on threads
    dsServer server(myMemberID, mutex, tbl_of_alive);

    //must have movable/copiable constructor to work on threads
    dsClient client(mutex);


    std::thread t1(server);
    std::thread t2(client);
    std::thread t3(printer);

    t1.join();
    t2.join();
    t3.join();
/*  std::string id("876");
    HeartBeat heartBeat1{id};
    const HB::timestamp_t ts1 = heartBeat1.getTimeStamp();
    std::tm* tmp = std::localtime(&ts1);
    std::cout << heartBeat1.getMemberID() << "  " << std::put_time(tmp,"%d-%m-%Y < %H:%M:%S >") << std::endl;

    std::stringstream ss;
    ss << heartBeat1;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    HeartBeat heartBeat2{};
    ss >> heartBeat2;
    const HB::timestamp_t ts = heartBeat2.getTimeStamp();
    std::tm* tempo = std::localtime(&ts);
    std::cout << heartBeat2.getMemberID() << "  " << std::put_time(tempo,"%d-%m-%Y < %H:%M:%S >") << std::endl;
*/
    return 0;
}