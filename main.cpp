#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include "dsClient.h"
#include "dsServer.h"
#include "definitions.h"
#include "manageTable.h"


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    std::mutex mutex;
    heartBeat::tblOfAlive tbl_of_alive;
    heartBeat::memberID myMemberID;

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

    return 0;
}