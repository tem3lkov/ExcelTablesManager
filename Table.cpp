#include "Table.h"
#include "Utility.h"
#include "CellFactory.h"
#include "EmptyCell.h"
#include "FormulaCell.h"

Table &Table::getInstance()
{
    static Table instance;
    return instance;
}

void Table::load(const std::vector<std::string> &rows)
{
    std::size_t commasCount = 0;

    for (std::size_t i = 0; i < rows.size(); i++)
        commasCount = std::max(commasCount, Utility::countCommas(rows[i]));

    for(std::size_t i = 0; i < rows.size(); i++) {
        Row row;
        std::vector<std::string> tokens = Utility::split(Utility::trim(rows[i]), ',');
        
        for(std::size_t j = 0; j < tokens.size(); j++) {
            std::string type = Utility::trim(tokens[j]);
     
            Cell* cell = CellFactory::getFactory().createCell(type);

            if(cell)
                row.push_back(*cell);
            
            else {
                bool missingComma = Utility::countCommas(rows[i]) < commasCount;

                if (missingComma) {
                        std::cout << "Missing comma in cell " << "R" << i+1 << "C" << j + 1 << std::endl;
                        throw std::runtime_error("Formatting error. Check your data input!");
                }

                std::cout << "Cell type of cell " << "R" << i+1  << "C" << j + 1 << " not recognized. Value was: " << type << std::endl;;
                throw std::runtime_error("Error while parsing cell!");
            }

            delete cell;
        }
        addRow(row);
    }

    fillTable();
    calculateFormulas();
}

void Table::calculateFormulas() {
    for (std::size_t i = 0; i < table.size() ; i++) {
        for (std::size_t j = 0; j < table[i].getSize(); j++) {
            try {
                table[i][j]->eval();
            }
            catch(const std::exception& e) {
                std::cout << "Invalid value for: R" << i + 1 << "C" << j + 1  << " : " << table[i][j]->getContent() << std::endl;
                throw;
            }
        }
    }
}


std::vector<std::string> Table::save() const {
    std::vector<std::string> result;

    for(const Row& row : table) {
        std::string token;
        for(std::size_t j = 0; j < row.getSize(); j++) {
            token += row[j]->getContent();

            if(j != row.getSize() - 1)
                token += ", ";
        }
        result.push_back(token);
    }

    return result;
}

const Cell *Table::getCell(size_t row, size_t col) const
{
    if(row > table.size() || col > table[row].getSize())
        return nullptr;
    
    return this->table[row][col];
}

void Table::addRow(Row &row)
{
    this->table.push_back(row);
}

void Table::fillTable()
{
    std::size_t maxRowSize = table[0].getSize();

    for (std::size_t i = 0; i < table.size(); i++)
        maxRowSize = std::max(maxRowSize, table[i].getSize());

    for (std::size_t i = 0; i < table.size(); i++) {
        if (table[i].getSize() != maxRowSize) {
            std::size_t cellsToAdd = maxRowSize - table[i].getSize();

            for (std::size_t j = 0; j < cellsToAdd; j++) {
                table[i].push_back(EmptyCell());
            }
        }
    }
}

void Table::edit(const std::size_t row, const std::size_t col, const std::string &content)
{
    if (row >= this->table.size() || col >= this->table[row].getSize())
        throw std::out_of_range("Invalid index for changing cells!");

    Cell* cell = CellFactory::getFactory().createCell(content);

    if (!cell)
        throw std::invalid_argument("Invalid cell value!");

    table[row].changeCell(col, *cell);

    delete cell;
    calculateFormulas();
}

void Table::clear()
{
    this->table.clear();
}

void Table::print() const
{
    if (this->table.empty()) 
        return;

    std::vector<std::size_t> maxColWidths(table[0].getSize());
    
    for (const Row& row : table) {
        for (std::size_t col = 0; col < row.getSize(); ++col) {
            if (row[col]) {
                maxColWidths[col] = std::max(maxColWidths[col], row[col]->getSize());
            }
        }
    }

    for (std::size_t i = 0; i < table.size(); i++) {
        std::cout << "|";
        for (std::size_t j = 0; j < table[i].getSize(); j++) {
            std::cout << " ";
            if (table[i][j]) {

                table[i][j]->print();
                std::size_t printedSize = table[i][j]->getSize();

                if (maxColWidths[j] > printedSize)
                    std::cout << std::string(maxColWidths[j] - printedSize, ' ');
                    
            } else {
                std::cout << std::string(maxColWidths[j], ' ');
            }
            std::cout << " |";
        }
        std::cout << std::endl;
    }
}