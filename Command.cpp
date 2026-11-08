#include "Command.h"
#include "App.h"
#include "Table.h"
#include "Utility.h"

Command::Command(const std::string &command, const std::vector<std::string> &arguments)
: command(command), arguments(arguments)
{}

void Command::open()
{
    if(arguments.size() != 1)
        throw std::invalid_argument("Invalid number of arguments!");

    if(!App::getApp().getPath().empty())
        throw std::invalid_argument("Another table is already opened!");

    std::ifstream iFile(arguments[0]);

    if(!iFile)
        throw std::invalid_argument("File not found!");

    std::string line;
    std::vector<std::string> vectorTable;

    while(!iFile.eof()) {
        std::getline(iFile, line);
        vectorTable.push_back(line);
    }

    iFile.close();

    try {
        Table::getInstance().load(vectorTable);
        App::getApp().setPath(arguments[0]);
    }
    catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        App::getApp().getTable().clear();
        App::getApp().setPath("");

        throw std::runtime_error("Invalid table input data!");
    }

    std::cout << "Table " << arguments[0] << " successfully loaded!" << std::endl;    
}

void Command::close()
{
    if(arguments.size() != 0)
        throw std::invalid_argument("Invalid number of arguments!");

    if(App::getApp().getPath().empty())
        throw std::runtime_error("No table is currently opened!");

    App::getApp().getTable().clear();
    App::getApp().setPath("");

    std::cout << "Table closed successfully!" << std::endl;
}

void Command::save()
{
    if(arguments.size() != 0)
        throw std::invalid_argument("Invalid number of arguments!");

    if(App::getApp().getPath().empty())
        throw std::runtime_error("No table is currently opened!");

    std::ofstream oFile(App::getApp().getPath());
    if(!oFile)
        throw std::runtime_error("File not found!");

    std::vector<std::string> vectorTable = App::getApp().getTable().save();

    for(std::size_t i = 0; i < vectorTable.size(); i++) {
         oFile << vectorTable[i];
            if(i != vectorTable.size() - 1)
                oFile << std::endl;
    }

    oFile.close();

    std::cout << "Table saved successfully!" << std::endl;
}

void Command::saveAs()
{
    if(arguments.size() != 1)
        throw std::invalid_argument("Invalid number of arguments!");

    if(App::getApp().getPath().empty())
        throw std::runtime_error("No table is currently opened!");

    std::ofstream oFile(arguments[0]);
    if(!oFile)
        throw std::runtime_error("File not found!");

    std::vector<std::string> vectorTable = App::getApp().getTable().save();
    
    for(std::size_t i = 0; i < vectorTable.size(); i++) {
         oFile << vectorTable[i];
            if(i != vectorTable.size() - 1)
                oFile << std::endl;
    }

    oFile.close();
    std::cout << "Table saved successfully!" << std::endl;
}

void Command::help()
{
    if(arguments.size() != 0)
        throw std::invalid_argument("Invalid number of arguments!");

    App::getApp().print();
}

void Command::exit()
{
    if(arguments.size() != 0)
        throw std::invalid_argument("Invalid number of arguments!");

    std::cout << "Goodbay!" << std::endl;
}

void Command::print()
{
    if(arguments.size() != 0)
        throw std::invalid_argument("Invalid number of arguments!");

    if(App::getApp().getPath().empty())
        throw std::runtime_error("No table is currently opened!");

    App::getApp().getTable().print();
}

void Command::edit()
{
    if(arguments.size() <= 2)
        throw std::invalid_argument("Invalid number of arguments!");

    if(App::getApp().getPath().empty())
        throw std::runtime_error("No table is currently opened!");

    std::size_t row = static_cast<std::size_t>(std::stoi(arguments[0]) - 1);
    std::size_t col = static_cast<std::size_t>(std::stoi(arguments[1]) - 1);

    std::string value = "";

    for (std::size_t i = 2; i < arguments.size(); i++) {
        value += arguments[i];
        value += " ";
    }

    value = Utility::trim(value);

    Table::getInstance().edit(row, col, value);

    std::cout << "Cell R" << row + 1 << "C" << col + 1 << " has been modified successfully!" << std::endl;
}

void Command::eval()
{
    if(command == "open")
        open();
    else if(command == "close")
        close();
    else if(command == "save")
        save();
    else if(command == "saveas")
        saveAs();
    else if(command == "help")
        help();
    else if(command == "exit")
        exit();
    else if(command == "print")
        print();
    else if(command == "edit")
        edit();
    else
        throw std::invalid_argument("Invalid command!");
}