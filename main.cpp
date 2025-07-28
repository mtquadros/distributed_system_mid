#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include "dsClient.h"
#include "dsServer.h"
#include "definitions.h"




// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    std::mutex mutex;
    heartBeat::tblOfAlive tbl_of_alive;
    heartBeat::memberID myMemberID;
    //must have movable/copiable constructor to work on threads
    dsServer server(std::ref(myMemberID), std::ref(mutex),std::ref(tbl_of_alive));

    //must have movable/copiable constructor to work on threads
    dsClient client(std::ref(myMemberID), std::ref(mutex),std::ref(tbl_of_alive));

    std::thread t1(server);
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::thread t2(client);
    //std::thread t3(heartBeat::printTable, std::ref(mutex), std::ref(tbl_of_alive));

    t1.join();
    t2.join();
    //t3.join();

    return 0;
}