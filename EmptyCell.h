#pragma once
#include "Cell.h"

class EmptyCell : public Cell
{
public:
    EmptyCell();
    
    virtual std::size_t getSize() const override;
    virtual double eval() const override;
    virtual Cell* clone() const override;
    virtual void print() const override;

    virtual ~EmptyCell() = default;
};

class EmptyCellCreator : public CellCreator
{   
public:
    EmptyCellCreator(): CellCreator() {}

    virtual Cell* createCell(const std::string&) const override;
    virtual bool isValid(const std::string& string) const override;
};