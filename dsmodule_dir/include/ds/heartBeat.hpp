//
// Created by dev on 19/08/2025.
//

#ifndef DISTRIBUTED_GROUP_HEARTBEAT_H
#define DISTRIBUTED_GROUP_HEARTBEAT_H

#include <iostream>
#include <ds/definitions.hpp>

class HeartBeat{
    friend std::ostream& operator <<(std::ostream& os, const HeartBeat& beat);
    friend std::istream& operator >>(std::istream& is, HeartBeat& beat);
private:
    //this members must to be serializable
    std::string _memberID;
    std::time_t _timestamp;

    void setTimeStamp();

public:
    HeartBeat(std::string& id):_memberID(id){ setTimeStamp(); };
    HeartBeat(std::string&& id):_memberID(id){ setTimeStamp(); };
    ~HeartBeat() = default;

    std::time_t getTimeStamp() const;
    std::string getMemberID() const;

};



#endif //DISTRIBUTED_GROUP_HEARTBEAT_H