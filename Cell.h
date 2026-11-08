#pragma once
#include <string>
#include <iostream>

class Cell
{
public:
    Cell();
    explicit Cell(const std::string& string);

    virtual ~Cell() = default;

    virtual std::size_t getSize() const = 0;
    virtual double eval() const = 0;
    virtual Cell* clone() const = 0;
    virtual void print() const = 0;

    const std::string& getContent() const {return content;}
protected:
    std::string content;
};

class CellCreator
{
public:
    CellCreator();

    virtual ~CellCreator() = default;

    virtual Cell* createCell(const std::string& string) const = 0;
    virtual bool isValid(const std::string& string) const = 0;
};