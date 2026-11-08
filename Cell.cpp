#include "Cell.h"
#include "CellFactory.h"

Cell::Cell()
: content() { }

Cell::Cell(const std::string &string)
: content(string) {}

CellCreator::CellCreator() {
    CellFactory::getFactory().registerCell(this);
}
