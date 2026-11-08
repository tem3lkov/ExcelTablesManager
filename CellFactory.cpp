#include "CellFactory.h"

CellFactory &CellFactory::getFactory() {
    static CellFactory theFactory;
    return theFactory;
}

void CellFactory::registerCell(const CellCreator *creator) {
    assert(this->cnt < CellFactory::MAX_NUMBER_OF_CREATORS);

    if(this->cnt >= CellFactory::MAX_NUMBER_OF_CREATORS)
        throw std::runtime_error("Maximum number of cell creators reached!");

    this->creators[cnt++] = creator;
}

Cell *CellFactory::createCell(const std::string &string) const {
    const CellCreator* creator = getCreator(string);

    if(creator)
        return creator->createCell(string);

    return nullptr;
}

const CellCreator *CellFactory::getCreator(const std::string &string) const {
    for(std::size_t i = 0; i < cnt; i++) {
        if(creators[i]->isValid(string))
            return creators[i];
    }
    return nullptr;
}
