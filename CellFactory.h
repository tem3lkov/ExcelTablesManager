#pragma once
#include "Cell.h"
#include <cassert>

class CellFactory
{
public:
    static CellFactory& getFactory();

    void registerCell(const CellCreator* creator);

    Cell* createCell(const std::string& string) const;

private:
    CellFactory(): cnt(0) {};
    CellFactory(const CellFactory&) = delete;
    CellFactory& operator= (const CellFactory&) = delete;

    ~CellFactory() = default;
private:
    const CellCreator* getCreator(const std::string& string) const;

private:
    std::size_t cnt;
    static constexpr std::size_t MAX_NUMBER_OF_CREATORS = 5;

    const CellCreator* creators[MAX_NUMBER_OF_CREATORS];
};