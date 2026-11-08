#include "EmptyCell.h"

EmptyCell::EmptyCell()
: Cell() {}

std::size_t EmptyCell::getSize() const {
    return 0;
}

double EmptyCell::eval() const {
    return 0.0;
}

Cell *EmptyCell::clone() const {
    return new EmptyCell(*this);
}

void EmptyCell::print() const {
    std::cout << "";
}

Cell *EmptyCellCreator::createCell(const std::string &) const {
    return new EmptyCell();
}

bool EmptyCellCreator::isValid(const std::string &string) const {
    return string.size() == 0;
}

static EmptyCellCreator _ecC;