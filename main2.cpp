
#include <iostream>
#include <sstream>
#include <string>
#include <ds/heartBeat.hpp>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{

    try
    {
        std::cout << "====== Input string buffer ================" << std::endl;
        std::string id{"635"};
        HeartBeat beat2{id};
        std::stringstream ss;
        ss << beat2;
        HeartBeat beat3{};
        //std::cout << beat3 << std::endl;
        ss >> beat3;
        std::cout << "Input beat3: " << beat3.getTimeStamp() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}