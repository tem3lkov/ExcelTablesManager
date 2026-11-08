#include "StringCell.h"
#include "Utility.h"

StringCell::StringCell(const std::string &string)
: Cell(string), value(Utility::removeEscapeCharacters(string)) {}

std::size_t StringCell::getSize() const
{
    return this->value.size();
}

double StringCell::eval() const
{
    return 0.0;
}

Cell *StringCell::clone() const
{
    return new StringCell(*this);
}

void StringCell::print() const
{
    std::cout << this->value;
}

bool StringCell::isString(const std::string& str) {
        if (str.size() < 2 || str.front() != '\"' || str.back() != '\"')
            return false;

        for (std::size_t i = 1; i < str.size() - 1; i++) {
            if (str[i] == '\\') {
                if (i + 1 == str.size() - 1 || (str[i + 1] != '\"' && str[i + 1] != '\\')) {
                    return false;
                }
                i++; 
            } else if (str[i] == '\"') {
                return false;
            }
        }
        return true;
}



Cell * StringCellCreator::createCell(const std::string & string) const {
    return new StringCell(string);
}

bool StringCellCreator::isValid(const std::string &string) const {
    return StringCell::isString(string);
}

static StringCellCreator _scC;