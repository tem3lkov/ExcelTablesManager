#pragma once
#include "Cell.h"

class Row
{
public:
    Row();
    Row(const std::size_t size);

    Row(const Row& other);
    Row& operator=(const Row& other);
    ~Row();

    Cell* operator[] (const std::size_t index);
    const Cell* operator[] (const std::size_t index) const;

    std::size_t getCapacity() const {return this->capacity;}
    std::size_t getSize() const {return this->size;}

    void push_back(const Cell& cell);
    void changeCell(const std::size_t index, const Cell& cell); 

private:
    void copy(const Row& other);
    void free();
    void resize();

    std::size_t size;
    std::size_t capacity;
    Cell** data;
};