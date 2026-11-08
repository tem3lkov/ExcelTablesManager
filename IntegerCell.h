#pragma once 

#include "Cell.h"

class IntegerCell : public Cell
{
public:
    explicit IntegerCell(const std::string& string);
    
    virtual std::size_t getSize() const override;
    virtual double eval() const override;
    virtual Cell* clone() const override;
    virtual void print() const override;
    
    virtual ~IntegerCell() = default;

    static bool isInteger(const std::string& string);
private:
    int value;
};

class IntegerCellCreator: public CellCreator
{
public:
    IntegerCellCreator(): CellCreator() {}

    virtual Cell* createCell(const std::string& string) const override;
    virtual bool isValid(const std::string& string) const override;
};