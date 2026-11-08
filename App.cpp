#include "App.h"
#include "Utility.h"
#include "Command.h"


App &App::getApp() {
    static App theApp;
    return theApp; 
}

void App::run() {
    print();

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        std::vector<std::string> tokens = Utility::split(command, ' ');

        if (tokens.size() == 0)
            continue;
        
        std::string commandName = tokens[0];
        tokens.erase(tokens.begin());

        commandName = Utility::toLower(commandName);

        try {
            Command command = Command(commandName, tokens);

            std::cout << std::endl;
            command.eval();
        }
        catch (const std::exception& exception) {
            std::cout << exception.what() << std::endl;
        }

        if (commandName == "exit")
            break;

        std::cout << std::endl;
    }
    
     
}

void App::print() {
        std::cout << "\n\n";
        std::cout << "Available Commands:\n";
        std::cout << "-------------------\n";
        std::cout << "open <file_path>\t\tLoad a table from the specified file path.\n";
        std::cout << "close\t\t\t\tClose the currently opened table.\n";
        std::cout << "edit <row> <col> <value>\tModify a specific cell in the table.\n";
        std::cout << "print\t\t\t\tDisplay the contents of the table.\n";
        std::cout << "save\t\t\t\tSave the current table to the file it was opened from.\n";
        std::cout << "save as <file_path>\t\tSave the current table to a new file.\n";
        std::cout << "exit\t\t\t\tTerminate the application.\n";
        std::cout << "-------------------\n";
        std::cout << "\n\n";
}

void App::setPath(const std::string &path) {
    this->path = path;
}

Table& App::getTable() {
    return Table::getInstance();
}

std::string App::getPath() const {
    return this->path;
}
