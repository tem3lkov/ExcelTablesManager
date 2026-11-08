#pragma once
#include "Row.h"
#include "Cell.h"
#include <vector>

class Table
{
public:
    static Table& getInstance();

    Table(const Table& other) = delete;
    Table& operator=(const Table& other) = delete;

    void load(const std::vector<std::string>& rows);
    std::vector<std::string> save() const;
    
    void addRow(Row& row);
    void edit(const std::size_t row, const std::size_t col, const std::string& content);

    void clear();
    void fillTable();
    void calculateFormulas();

    void print() const;

    const Cell* getCell(size_t row, size_t col) const;

private:
    Table() = default;
    std::vector<Row> table;
};