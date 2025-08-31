//
// Created by dev on 28/08/2025.
//

#ifndef DISTRIBUTED_GROUP_MESSAGE_H
#define DISTRIBUTED_GROUP_MESSAGE_H

#include <ds/definitions.hpp>

/*
#ifdef  __GNUC__

#elifdef __
#endif
*/
class message
{
    friend std::ostream& operator <<(std::ostream& os, const message& beat);
    friend std::istream& operator >>(std::istream& is, message& beat);

public:
    ~message();

    enum class MsgType { Req = 2, Ack = 4, Commit = 5, Heartbeat = 6 };
    static message* getNewInstance() { return new message{};}

    inline __attribute__((__always_inline__)) void setMessageType(MsgType header);
    inline __attribute__((__always_inline__)) void setMessageData(std::string& data);
    inline __attribute__((__always_inline__)) void setMessageData(std::string&& data);
    inline __attribute__((__always_inline__)) void setMessageMemberID(std::string& member_id);

    inline __attribute__((__always_inline__)) MsgType getMessageType();
    inline __attribute__((__always_inline__)) const std::string& getMessageData();
    inline __attribute__((__always_inline__)) std::string getMessageMemberID();

private:
    MsgType messageType;
    std::string memberID;
    std::string messageData;
    message();

};


#endif //DISTRIBUTED_GROUP_MESSAGE_H