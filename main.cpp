#include <iostream>
#include <memory>
#include <thread>
#include "dsClient.h"
#include "dsServer.h"


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    dsServer server; //must have movable/copiable constructor to work on threads
    dsClient client; //must have movable/copiable constructor to work on threads
    std::thread t1(server);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(client);

    t1.join();
    t2.join();

    return 0;
}