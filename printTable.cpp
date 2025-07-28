//
// Created by dev on 26/07/25.
//

#include "definitions.h"
#include <iostream>

void heartBeat::printTable(std::mutex& mutex, const tblOfAlive& table_of_alive)
{
    std::cout.clear();
    std::cout.flush();
/*    std::cout << "\033[2K"; // limpa a linha inteira
    std::cout.width(42);
    // Move cursor para linha 5, coluna 10
    std::cout << "\033[0;0H";
    std::cout << "Group Members Alive:" << std::endl;
    std::cout.fill('+');
    std::cout.width(21);
    std::cout <<  std::endl;*/
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::unique_lock<std::mutex> lock(mutex);
    for (auto item : table_of_alive)
    {
        std::cout << item.first << std::endl << std::flush;
    }
    mutex.unlock();
    std::this_thread::sleep_for(periodMillisecs);
}