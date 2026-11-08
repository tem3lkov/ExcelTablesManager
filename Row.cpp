#include "Row.h"

Row::Row()
: size(0), capacity(2), data(nullptr)  {
    this->data = new Cell*[capacity];
}

Row::Row(const std::size_t size)
: size(0), capacity(size), data(nullptr) {
    this->data = new Cell*[capacity];
}

Row::Row(const Row &other)
: data(nullptr) {
    copy(other);
}

void Row::push_back(const Cell &cell) {
    if(size == capacity)
        resize();

    data[size++] = cell.clone();
}

void Row::changeCell(const std::size_t index, const Cell &cell) {
    if (index >= this->size)
        throw std::out_of_range("Invalid index for changing cells!");

    delete this->data[index];
    this->data[index] = cell.clone();
}

void Row::copy(const Row &other) {
    this->size = other.size;
    this->capacity = other.capacity;

    this->data = new Cell*[capacity];
    for(std::size_t i = 0; i < size; i++) {
        this->data[i] = other.data[i]->clone();
    }
}

void Row::free() {
    for(std::size_t i = 0; i < size; i++) {
        delete this->data[i]; 
    }
    
    delete[] this->data;
    this->data = nullptr;

    this->size = this->capacity = 0;
}

void Row::resize() {
    std::size_t newCap = capacity * 2;
    Cell** tempData = new Cell*[newCap];

    for(std::size_t i = 0; i < size; i++) {
        tempData[i] = this->data[i];
    }

    delete[] this->data;
    this->data = tempData;

    this->capacity = newCap;
}



Row &Row::operator=(const Row &other) {
    if(this != &other) {
        free();
        copy(other);
    }
    return *this;
}

Row::~Row() {
    free();
}

Cell *Row::operator[](const std::size_t index) {
    return this->data[index];
}

const Cell *Row::operator[](const std::size_t index) const {
    return this->data[index];
}
