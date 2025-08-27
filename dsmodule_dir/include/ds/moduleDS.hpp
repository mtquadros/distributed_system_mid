//
// Created by dev on 25/08/2025.
//

#ifndef DISTRIBUTED_GROUP_MODULEDS_H
#define DISTRIBUTED_GROUP_MODULEDS_H

#include <ds/definitions.hpp>
#include <thread>
#include <shared_mutex>
#include <vector>
class base_moduleDS
{
public:
    virtual void sendMessage() = 0;
    virtual void receiveMessage() = 0;;
    virtual void processing() = 0;

};


class moduleDS
{
private:
    enum class context { ReceiveMessage, SendMessage, Processing};
    HB::logical_clock _logicalClock;
    std::vector<std::thread> _threads;
    std::shared_mutex _mutex;
    void sendMessageTask();
    void receiveMessageTask();
    void processingTask();
    void clockTick(context _context);

public:
    moduleDS();
    ~moduleDS();
    void sendMessage() override;
    void receiveMessage() override;
    void processing() override;

};


#endif //DISTRIBUTED_GROUP_MODULEDS_H