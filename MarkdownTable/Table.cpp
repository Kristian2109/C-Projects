#include <iostream>
#include <fstream>
#include <sstream>
#include "Table.h"
#include "StringFunctions.h"

const char* getAlignmentValue(ColumnAlignment alignment)
{
switch (alignment)
{
case ColumnAlignment::center:
    return alignents::center;

case ColumnAlignment::rigth:
    return alignents::rigth;

default:
    return alignents::left;
    break;
}
}

unsigned Table::computeLeftPadding(unsigned lenValue, const ColumnAlignment& alignment) const
{
    if (alignment == ColumnAlignment::left) { return 0; }
    if (alignment == ColumnAlignment::center)
    {
        return (colWidth - lenValue) / 2;
    }
    if (alignment == ColumnAlignment::rigth)
    {
        return colWidth - lenValue;
    }
}

void Table::printValue(int indexCol, const Value& value) const
{
    unsigned lenValue = strlen(value.content);
    unsigned leftPadding = computeLeftPadding(lenValue, columnAlignments[indexCol]);

    printSymbol(' ', leftPadding);
    std::cout << value.content;
    printSymbol(' ', colWidth - leftPadding - lenValue + 1);
    std::cout << "| ";
}

void Table::printRow(const Row& row) const
{
    std::cout << "| ";
    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        printValue(i, row.values[i]);
    }
    std::cout << std::endl;
}

void Table::printHeader() const
{
    printRow(this->columnNames);
    std::cout << "| ";
    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        printSymbol('-', this->colWidth); std::cout << " | ";
    }
    std::cout << std::endl;
}

void Table::printTable() const
{
    printHeader();
    for (size_t i = 0; i < this->rowsCount; i++)
    {
        printRow(this->rows[i]);
    }
}

void Table::loadValue(std::ifstream& inFile, Value& value)
{
    inFile.getline(value.content, MAX_SYMBOLS, '|');
    std::stringstream buffer(value.content);
    castString(value.content);

}

void Table::setCountCols(std::ifstream& inFile)
{
    char buffer[1024];
    inFile.getline(buffer, 1024);

    std::stringstream stringBuffer(buffer);
    stringBuffer.getline(buffer, 1024, '|');

    while (true)
    {
        stringBuffer.getline(buffer, 1024, '|');
        if (!stringBuffer)
        {
            break;
        }
        this->columnNames.count++;
    }
    inFile.seekg(0);
}

void Table::loadRow(std::ifstream& inFile, Row& row)
{
    char buffer[MAX_SYMBOLS];
    inFile >> buffer;
    if (inFile.eof()) { return; }
    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        loadValue(inFile, row.values[i]);
    }
}

ColumnAlignment Table::setAlignValue(const char* value)
{
    int lenValue = strlen(value);

    if (lenValue < 3)
        return ColumnAlignment::left;

    bool isColonInBegin = value[0] == ':';
    bool isColonInEnd = value[lenValue - 1] == ':';

    if (isColonInBegin && isColonInEnd)
        return ColumnAlignment::center;

    if (isColonInEnd)
        return ColumnAlignment::rigth;

    return ColumnAlignment::left;
}

void Table::setAlignment(std::ifstream& inFile)
{
    char buffer[MAX_LINE_LEN];
    inFile.getline(buffer, MAX_LINE_LEN);
    inFile.getline(buffer, MAX_LINE_LEN);
    std::stringstream stringBuffer(buffer);
    stringBuffer.getline(buffer, MAX_LINE_LEN, '|');
    for (size_t i = 0; i < this->columnNames.count; i++)
    {

        stringBuffer >> buffer;
        this->columnAlignments[i] = setAlignValue(buffer);
        stringBuffer.getline(buffer, MAX_LINE_LEN, '|');
    }
}

void Table::setRows(std::ifstream& inFile)
{
    while (true)
    {
        loadRow(inFile, this->rows[this->rowsCount]);
        if (inFile.eof()) { return; }
        this->rowsCount++;
    }
}

unsigned Table::getMaxValueWidthInRow(const Row& row) const
{
    unsigned maxWidth = 0;
    unsigned valueLen = 0;

    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        valueLen = strlen(row.values[i].content);

        if (valueLen > maxWidth)
            maxWidth = valueLen;
    }

    return maxWidth;
}

void Table::setColWidth()
{
    unsigned maxWidth = 0;

    maxWidth = getMaxValueWidthInRow(this->columnNames);

    unsigned maxLenValueOfRow = 0;

    for (size_t row = 0; row < this->rowsCount; row++)
    {
        maxLenValueOfRow = getMaxValueWidthInRow(this->rows[row]);
        if (maxLenValueOfRow > maxWidth)
        {
            maxWidth = maxLenValueOfRow;
        }
    }

    this->colWidth = maxWidth;
}

int Table::getColIndexByName(const char* name) const
{
    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        if (strcmp(name, this->columnNames.values[i].content) == 0)
        {
            return i;
        }
    }

    return -1;
}

bool Table::setColName(const char* currentName, const char* newName)
{
    unsigned lenName = strlen(newName);
    if (lenName > 20) { return false; }

    int colIndex = getColIndexByName(currentName);

    if (colIndex == -1) { return false; }

    strcpy_s(this->columnNames.values[colIndex].content, newName);
    if (lenName > this->colWidth)
    {
        this->colWidth = lenName;
    }
    return true;
}

bool Table::setValue(const char* colName, unsigned rowNumber, const char* newValue)
{
    unsigned rowIndex = rowNumber - 1;
    if ((rowIndex) > this->rowsCount) { return false; };

    unsigned lenValue = strlen(newValue);
    if (lenValue > MAX_SYMBOLS) { return false; }

    short colIndex = getColIndexByName(colName);

    if (colIndex == -1) { return false; }

    strcpy_s(this->rows[rowIndex].values[colIndex].content, newValue);
    setColWidth();
    return true;

}

bool Table::setValue(const char* colName, const char* currValue, const char* newValue)
{
    unsigned lenValue = strlen(newValue);
    if (lenValue > MAX_SYMBOLS) { return false; }

    int colIndex = getColIndexByName(colName);
    if (colIndex == -1) { return false; }

    for (size_t i = 0; i < this->rowsCount; i++)
    {
        if (strcmp(this->rows[i].values[colIndex].content, currValue) == 0)
        {
            strcpy_s(this->rows[i].values[colIndex].content, newValue);
            setColWidth();
            return true;
        }
    }

    return false;
}

// Every value should begin with high letter, so that the string is valid
bool Table::isRowStringValid(const char* rowString) const
{
    unsigned countValues = 0;
    while (rowString[0] != '\0')
    {
        if (rowString[0] >= 'A' && rowString[0] <= 'Z')
        {
            countValues++;
        }
        rowString++;
    }

    return countValues == this->columnNames.count;
}

bool Table::addRow(const char* rowString)
{
    if (!isRowStringValid(rowString)) { return false; }
    std::stringstream stream(rowString);

    Row* ptrToRow = &this->rows[this->rowsCount];

    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        stream >> ptrToRow->values[i].content;
    }

    this->rowsCount++;
    setColWidth();
    return true;
}

void Table::savePaddingToFile(std::ofstream& outFile, int times) const
{
    for (size_t i = 0; i < times; i++)
    {
        outFile << ' ';
    }
}

void Table::saveColAlignentsToFile(std::ofstream& outFile) const
{
    outFile << "| ";

    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        const char* alignmentValue = getAlignmentValue(this->columnAlignments[i]);
        outFile << alignmentValue;

        unsigned leftPadding = this->colWidth - strlen(alignmentValue);
        savePaddingToFile(outFile, leftPadding);

        outFile << " |";
        if (this->columnNames.count - 1 != i)
        {
            outFile << ' ';
        }
    }

    outFile << '\n';
}

void Table::saveRowToFile(std::ofstream& outFile, const Row& row) const
{
    outFile << "| ";
    for (size_t i = 0; i < this->columnNames.count; i++)
    {
        outFile << row.values[i].content;
        for (size_t j = 0; j < this->colWidth - strlen(row.values[i].content); j++)
        {
            outFile << ' ';
        }
        outFile << " |";

        if (this->columnNames.count - 1 != i)
        {
            outFile << ' ';
        }
    }
    outFile << '\n';
}

bool Table::saveToFile(const char* fileName) const
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        return false;
    }
    saveRowToFile(outFile, this->columnNames);
    saveColAlignentsToFile(outFile);

    for (size_t i = 0; i < this->rowsCount; i++)
    {
        saveRowToFile(outFile, this->rows[i]);
    }
    outFile.close();
    return true;
}

void Table::selectRowsByValue(const char* colName, const char* value) const
{
    printHeader();
    int indexCol = getColIndexByName(colName);
    for (size_t i = 0; i < rowsCount; i++)
    {
        const char* ptrToCurrValue = this->rows[i].values[indexCol].content;
        if (strcmp(ptrToCurrValue, value) == 0)
        {
            printRow(this->rows[i]);
        }
    }
}

bool Table::load(const char* fileName)

{
    std::ifstream inFile(fileName);
    if (!inFile.is_open())
    {
        std::cout << "File isn't open!\n";
        return false;
    }
    setCountCols(inFile);
    loadRow(inFile, this->columnNames);
    setAlignment(inFile);
    setRows(inFile);
    setColWidth();
    inFile.close();
    return true;
}
