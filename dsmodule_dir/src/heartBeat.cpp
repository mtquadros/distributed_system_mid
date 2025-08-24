

#include <ds/heartBeat.hpp>

std::time_t HeartBeat::getTimeStamp() const
{
    return _timestamp;
}

std::string HeartBeat::getMemberID() const
{
    return _memberID;
}

void HeartBeat::setTimeStamp()
{
    // Obtém o time_point atual
    auto now = std::chrono::system_clock::now();

    // Converte para tempo desde epoch em segundos
    _timestamp = std::chrono::system_clock::to_time_t(now);
}

std::ostream& operator <<(std::ostream& os, const HeartBeat& beat)
{
    os << beat._memberID;
    return os;
}

std::istream& operator >>(std::istream& is, HeartBeat& beat)
{
    is >> beat._memberID;
    beat.setTimeStamp();
    return is;
}

