#include <cstring>
#include <iostream>
#include <shared_mutex>
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
    std::shared_mutex mutex;
    HB::tblOfAlive tbl_of_alive;
    HB::memberID myMemberID;

    std::ostringstream oss;
    oss << std::this_thread::get_id();
    myMemberID = oss.str();

    manageTable printer(mutex, tbl_of_alive);
    //must have movable/copiable constructor to work on threads
    dsServer server(myMemberID, mutex, tbl_of_alive);

    //must have movable/copiable constructor to work on threads
    dsClient client(myMemberID);


    std::thread t1(server);
    std::thread t2(client);
    std::thread t3(printer);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}