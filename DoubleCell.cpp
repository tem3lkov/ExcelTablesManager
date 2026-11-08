#include "DoubleCell.h"

DoubleCell::DoubleCell(const std::string &string)
: Cell(string), value(std::stod(string)) {}

std::size_t DoubleCell::getSize() const {
    return std::to_string(value).size() - 3;
};

double DoubleCell::eval() const {
    return this->value;
};

Cell *DoubleCell::clone() const {
    return new DoubleCell(*this);
};

void DoubleCell::print() const {
    std::cout.precision(3); std::cout << std::fixed << this->value;
}

bool DoubleCell::isDouble(const std::string &string) {
    std::size_t pos = 0;
    try {
        std::stod(string, &pos);
        
        return pos == string.size() && string.find('.') != std::string::npos;
    }
    catch (std::exception& exception) {
        return false;
    }
}

Cell *DoubleCellCreator::createCell(const std::string &string) const {
    return new DoubleCell(string);
}

bool DoubleCellCreator::isValid(const std::string &string) const {
    return DoubleCell::isDouble(string);
}

static DoubleCellCreator __dcC;