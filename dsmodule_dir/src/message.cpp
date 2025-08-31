//
// Created by dev on 28/08/2025.
//

#include <ds/message.hpp>

message::message()
{
}

message::~message()
{
}

void message::setMessageType(MsgType header)
{
    messageType = header;
}

void message::setMessageData(std::string& data)
{
    messageData = data;
}

void message::setMessageData(std::string&& data)
{
    messageData = std::move(data);
}

void message::setMessageMemberID(std::string& member_id)
{
    memberID = member_id;
}

message::MsgType message::getMessageType()
{
    return messageType;
}

const std::string& message::getMessageData()
{
    return messageData;
}

std::string message::getMessageMemberID()
{
    return memberID;
}

std::ostream& operator<<(std::ostream& os, const message& beat)
{
    os << static_cast<unsigned int>(beat.messageType) << " " << beat.memberID << " " << beat.messageData;
    return os;
}

std::istream& operator>>(std::istream& is, message& beat)
{
    unsigned int temp;
    is >> temp;
    beat.messageType = static_cast<message::MsgType>(temp);
    is >> beat.memberID >> beat.messageData;
    return is;
}
