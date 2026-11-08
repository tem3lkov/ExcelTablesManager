#pragma once
#include "Cell.h"

class StringCell: public Cell
{
public:
    explicit StringCell(const std::string& string);
    
    virtual std::size_t getSize() const override;
    virtual double eval() const override;
    virtual Cell* clone() const override;
    virtual void print() const override;

    virtual ~StringCell() = default;

    static bool isString(const std::string& string);
private:
    std::string value;
};

class StringCellCreator: public CellCreator
{
public:
    StringCellCreator(): CellCreator() {}

    virtual Cell* createCell(const std::string& string) const override;
    virtual bool isValid(const std::string& string) const override;
};