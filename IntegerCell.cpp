#include "IntegerCell.h"


IntegerCell::IntegerCell(const std::string &string)
: Cell(string), value(std::stoi(string)) {}

std::size_t IntegerCell::getSize() const {
    return std::to_string(value).size();
}

double IntegerCell::eval() const {
    return static_cast<double>(value);
}

Cell *IntegerCell::clone() const {
    return new IntegerCell(*this);
}

void IntegerCell::print() const {
    std::cout << this->value;
}

bool IntegerCell::isInteger(const std::string &string) {
    std::size_t pos = 0;
    try {
        std::stoi(string, &pos);
        return pos == string.size();
    } catch (std::exception& exception) {
        return false;
    }
};

Cell *IntegerCellCreator::createCell(const std::string &string) const {
    return new IntegerCell(string);
}

bool IntegerCellCreator::isValid(const std::string &string) const {
    return IntegerCell::isInteger(string);
}

static IntegerCellCreator _icC;