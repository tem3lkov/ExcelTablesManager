#pragma once
#include "Cell.h"

class DoubleCell: public Cell
{
public:
    explicit DoubleCell(const std::string& string);
    
    virtual std::size_t getSize() const override;
    virtual double eval() const override;
    virtual Cell* clone() const override;
    virtual void print() const override;
    
    virtual ~DoubleCell() = default;

    static bool isDouble(const std::string& string);
private:
    double value;    
};

class DoubleCellCreator: public CellCreator
{
public:
    DoubleCellCreator(): CellCreator() {}

    virtual Cell* createCell(const std::string& string) const override;
    virtual bool isValid(const std::string& string) const override;
};
