#pragma once
#include "Cell.h"
#include "Table.h"
#include <sstream>
#include <iostream>
#include <string>
#include <math.h>


class FormulaCell : public Cell
{
public:
    explicit FormulaCell(const std::string& string, bool hasResult = false);

    virtual std::size_t getSize() const override;
    virtual double eval() const override;
    virtual Cell* clone() const override;
    virtual void print() const override;

    virtual ~FormulaCell() = default;

    static bool isFormula(const std::string& string);
private:
    double evaluate(const std::vector<std::string>& tokens) const;
    std::vector<std::string> parse(const std::string& string) const;
    

    bool isOperator(const std::string& op) const;
    bool isNumber(const std::string& token) const;
    bool isReference(const std::string& token) const;

    void parseReference(const std::string& ref, std::size_t& row, std::size_t& col) const;
private:
    mutable std::vector<std::pair<std::size_t, std::size_t>> visited;
    mutable std::string value;
    mutable bool hasResult;
};

class FormulaCellCreator : public CellCreator
{
public:
    FormulaCellCreator(): CellCreator() {}

    virtual Cell* createCell(const std::string& string) const override;
    virtual bool isValid(const std::string& string) const override;
};