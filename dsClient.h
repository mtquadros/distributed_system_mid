//
// Created by dev on 14/07/25.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <memory>
#include <boost/asio/io_service.hpp>
#include <iostream>

class dsClient
{
    //public members
    public:

    ~dsClient();
    dsClient();
    dsClient(dsClient const&)
    {
        std::cout << "\nThread calls Copy constructor" << std::endl;
    };
    dsClient(dsClient&&)
    {
        std::cout << "\nThread calls Move constructor" << std::endl;
    };

    void operator()() const;

    //protected members
    protected:
    void joinGroup();
    inline void propose();
    inline void leaveGroup();
    inline void decide();
};


#endif //CLIENT_H
