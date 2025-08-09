//
// Created by dev on 26/07/25.
//

#include <iostream>
#include <iomanip>
#include <ds/manageTable.hpp>
#include <mutex>
#include <chrono>
#include <ctime>

int col = 0, row = 0;

void manageTable::operator()()
{
    // Cabeçalho
    while (true)
    {
        {
            col = 2;
            row = 2;
            std::lock_guard<std::mutex> lock(_mutex);
            hideCursor();
            moveCursor(col,row);
            print_separator();
            moveCursor(col,++row);
            print_header("Member", "Last TimeStamp");
            moveCursor(col,++row);
            print_separator();
            moveCursor(col,++row);
            int counter = 0;
            for (const auto& item : _tableOfAlive)
            {
                // Dados
                //print_row(std::to_string(++counter), vec[counter]);
                print_row(item.first, item.second);
                moveCursor(col,++row);
                print_separator();
                moveCursor(col,++row);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        showCursor();
    }
}

void manageTable::print_header(const std::string& col1, const std::string& col2)
{
    std::cout << "| " << std::setw(20) << std::left << col1 << " | "
        << std::setw(20) << std::left << col2 << " |";
}

void manageTable::print_row(const std::string& col1, const heartBeat::timestamp_t& time)
{
    std::cout << "| " << std::setw(20) << std::left << col1 << " | "
        << std::setw(20) << std::left << time << " |" ;
}

void manageTable::print_separator()
{
    std::cout << "+"
        << std::string(22, '-') << "+"
        << std::string(22, '-') << "+";
}

int manageTable::countTable()
{
    return _tableOfAlive.size();
}

void manageTable::moveCursor(int col, int row)
{
    std::cout << "\033[" << row << ";" << col << "H";
}

