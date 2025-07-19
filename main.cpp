#include <iostream>
#include <memory>
#include <thread>
#include "dsClient.h"
#include "dsServer.h"
#include "definitions.h"


// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    std::mutex mutex;
    tableOfMessages tableOfProposed;
    tableOfMessages tableOfAlived;

    //must have movable/copiable constructor to work on threads
    dsClient client(std::ref(mutex), std::ref(tableOfProposed), std::ref(tableOfAlived));

    //must have movable/copiable constructor to work on threads
    dsServer server(std::ref(mutex), std::ref(tableOfProposed), std::ref(tableOfAlived));
    std::thread t1(server);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::thread t2(client);

    t1.join();
    t2.join();

    return 0;
}