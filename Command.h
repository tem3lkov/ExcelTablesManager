#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Command
{
public:
    Command(const std::string& command, const std::vector<std::string>& arguments);

    void open();
    void close();

    void save();
    void saveAs();

    void eval();
    void edit();

    void print();
    void help();

    void exit();
private:
    std::string command;
    std::vector<std::string> arguments;
};