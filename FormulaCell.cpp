#include "FormulaCell.h"
#include "IntegerCell.h"
#include "DoubleCell.h"
#include "StringCell.h"

#include "Utility.h"


FormulaCell::FormulaCell(const std::string &string, bool hasResult)
: Cell(string), hasResult(hasResult) {}

std::size_t FormulaCell::getSize() const {
    if(!hasResult)
        return std::string("ERROR").size();

    bool isInt = IntegerCell::isInteger(this->value);
    bool isDouble = DoubleCell::isDouble(this->value);

    if (!isInt && !isDouble) {
        return this->value.size();
    } else {
        double fractionalPart = std::stod(this->value) - static_cast<long long>(std::stod(this->value));

        if(this->value.size() == 1)
            return this->value.size();

        if (std::fabs(fractionalPart) <= 0.0001) {
            return this->value.size() - 7;
        } else {
            return this->value.size() - 3;
        }
    }
}

double FormulaCell::eval() const {
    double formulaValue  = 0.0;
        try {
            std::vector<std::string> tokens = parse(content);
            
            formulaValue = evaluate(tokens);

            this->value = std::to_string(formulaValue);
            this->hasResult = true;

        } catch (const std::exception& e) {;
            this->hasResult = false;

            if(e.what() != std::string("Division by zero"))
                throw;
        }

    this->visited.clear();
    return formulaValue;
}

Cell *FormulaCell::clone() const {
    return new FormulaCell(*this);
}

void FormulaCell::print() const {
    if(!hasResult) {
        std::cout << "ERROR";
        return;
    }

    bool isInt = IntegerCell::isInteger(this->value);
    bool isDouble = DoubleCell::isDouble(this->value);

    if (!isInt && !isDouble) {
        std::cout << this->value;
    } else {
        double fractionalPart = std::stod(this->value) - static_cast<long long>(std::stod(this->value));

        if (std::fabs(fractionalPart) <= 0.0001) {
            std::cout << std::stoll(this->value);
        } else {
            std::cout.precision(3); std::cout << std::fixed << std::stod(this->value);
        }
    }
}

bool FormulaCell::isFormula(const std::string &string) {
    return !string.empty() && string[0] == '=';
}

double FormulaCell::evaluate(const std::vector<std::string>& tokens) const {
    double result = 0.0;
    double value = 0.0;

    bool operatorFound = false;
    bool expectedNumber = false;

    std::size_t numberOfCells = 0;
    std::string op = "+";

    for (std::size_t i = 0; i < tokens.size(); i++) {
        if(numberOfCells >= 2)
            throw std::invalid_argument("Invalid value for formula cell!");

        std::string token = StringCell::isString(tokens[i]) ? Utility::removeEscapeCharacters(tokens[i]) : tokens[i];

        if(isOperator(Utility::trim(token))) {
            if(expectedNumber)
                throw std::invalid_argument("Invalid value for formula cell!");
            if(numberOfCells == 0 && token != "+" && token != "-")
                throw std::invalid_argument("Invalid value for formula cell!");
                
            op = token;
            expectedNumber = true;
            operatorFound = true;

            continue;
        }
        else if (isReference(token)) {
            std::size_t row, col;
            parseReference(token, row, col);
            row--; col--;

            for (std::size_t j = 0; j < visited.size(); ++j) {
                if (visited[j].first == row && visited[j].second == col) {
                    throw std::runtime_error("Circular reference detected!");
                }
            }

            visited.push_back({row, col});
            const Cell* cell = Table::getInstance().getCell(row, col);
            if (!cell) {
                value = 0;
            }
            else value = cell->eval();    
        
            visited.pop_back();

            numberOfCells++;
            expectedNumber = false;
        } else if (isNumber(token)) {
            numberOfCells++;
            expectedNumber = false;
            value = std::stod(token);
        }
        else if(StringCell::isString(tokens[i])) {
            expectedNumber = false;
            numberOfCells++;
            value = 0;
        }
        else throw std::invalid_argument("Invalid value for formula cell!");

        if (op == "+") result += value;
        else if (op == "-") result -= value;
        else if (op == "*") result *= value;
        else if (op == "/") {
            if (value == 0) 
                throw std::runtime_error("Division by zero");
            result /= value;
        }
        else if (op == ">") 
            result = result > value ? 1.0 : 0.0;
        else if (op == "<") 
            result = result < value ? 1.0 : 0.0;
        else if (op == ">=") 
            result = result >= value ? 1.0 : 0.0;
        else if (op == "<=") 
            result = result <= value ? 1.0 : 0.0;
        else if (op == "==") 
            result = result == value ? 1.0 : 0.0;
        else if (op == "!=") 
            result = result != value ? 1.0 : 0.0;
    }

    if((!operatorFound && tokens.size() >= 2) || (operatorFound && expectedNumber) || tokens.size() == 0)
        throw std::invalid_argument("Invalid value for formula cell!");

    return result;
}

std::vector<std::string> FormulaCell::parse(const std::string &input) const {
    std::vector<std::string> tokens;
    std::string currentToken;
    bool inString = false;

    for (size_t i = 1; i < input.length(); i++) {
        char c = input[i];

        if (c == '"' && (i == 0 || input[i-1] != '\\')) {
            inString = !inString;
            currentToken += c;
            if (!inString) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            continue;
        }

        if (inString) {
            currentToken += c;
        } else {
            if (isspace(c)) {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
            } else if (isOperator(std::string(1, c))) {
                if (!currentToken.empty()) {
                    tokens.push_back(currentToken);
                    currentToken.clear();
                }
                currentToken += c;
                if (i+1 < input.length() && input[i+1] == '=') {
                    currentToken += '=';
                    ++i;
                }
                tokens.push_back(currentToken);
                currentToken.clear();
            } else {
                currentToken += c;
            }
        }
    }
    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

bool FormulaCell::isOperator(const std::string& op) const
{
     return op == "+" || op == "-" || op == "*" || op == "/" ||
           op == ">" || op == "<" || op == ">=" || op == "<=" ||
           op == "==" || op == "!=";
}

bool FormulaCell::isReference(const std::string& token) const {
    return token.size() > 2 && token[0] == 'R' && token.find('C') != std::string::npos;
}

bool FormulaCell::isNumber(const std::string &token) const {
    bool isInt = IntegerCell::isInteger(token);
    bool isDouble = DoubleCell::isDouble(token);

    return isInt || isDouble;
}

void FormulaCell::parseReference(const std::string& ref, std::size_t& row, std::size_t& col) const {
    size_t cPos = ref.find('C');
    row = std::stoull(ref.substr(1, cPos - 1));
    col = std::stoull(ref.substr(cPos + 1));
}


Cell *FormulaCellCreator::createCell(const std::string &string) const {
    return new FormulaCell(string);
}

bool FormulaCellCreator::isValid(const std::string &string) const {
    return FormulaCell::isFormula(string);
}

static FormulaCellCreator _fcC;
