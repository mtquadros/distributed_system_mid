//
// Created by dev on 28/07/25.
//

#ifndef MANAGETABLE_H
#define MANAGETABLE_H

#include <ds/definitions.hpp>

class manageTable
{
public:
    manageTable(std::mutex& mutex, HB::tblOfAlive& table_of_alive): _mutex(mutex), _tableOfAlive(table_of_alive){}
    ~manageTable() = default;
    void operator()();

private:
    std::mutex& _mutex;
    HB::tblOfAlive& _tableOfAlive;
    inline void print_header(const std::string& col1, const std::string& col2);
    inline void print_row(const std::string& col1, const HB::timestamp_t& time);
    inline void print_separator();
    inline int  countTable();
    inline void moveCursor(int col, int row);
    inline void hideCursor(){ std::cout << "\033[?25l"; };
    inline void showCursor(){ std::cout << "\033[?25h"; };
};


#endif //MANAGETABLE_H
