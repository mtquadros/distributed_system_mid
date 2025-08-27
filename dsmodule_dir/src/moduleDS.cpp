//
// Created by dev on 25/08/2025.
//

#include <ds/moduleDS.hpp>

void moduleDS::sendMessageTask()
{
    clockTick(context::SendMessage);
    sendMessage();
}
void moduleDS::receiveMessageTask()
{
    clockTick(context::ReceiveMessage);
    receiveMessage();
}
void moduleDS::processingTask()
{
    clockTick(context::Processing);
    processing();
}
