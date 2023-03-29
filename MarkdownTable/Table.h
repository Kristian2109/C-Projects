#pragma once

const short MAX_ROWS = 50;
const short MAX_COWS = 10;
const short MAX_SYMBOLS = 20;
const short MAX_LINE_LEN = 1024;

namespace alignents
{
    const char left[10] = ":---";
    const char rigth[10] = "---:";
    const char center[10] = ":----:";
}

namespace commands
{
    const char print[MAX_SYMBOLS] = "print";
    const char change[MAX_SYMBOLS] = "change";
    const char changeRow[MAX_SYMBOLS] = "changeRow";
    const char select[MAX_SYMBOLS] = "selectWhere";
    const char save[MAX_SYMBOLS] = "save";
    const char addRow[MAX_SYMBOLS] = "addRow";
}

struct Value
{
    char content[MAX_SYMBOLS];
};

struct Row
{
    Value values[MAX_COWS];
    size_t count = 0;
};

enum class ColumnAlignment
{
    left,
    center,
    rigth
};

const char* getAlignmentValue(ColumnAlignment alignment);

class Table
{
private:
    Row columnNames;
    Row rows[MAX_ROWS];
    unsigned rowsCount = 0;
    unsigned colWidth = MAX_SYMBOLS;
    ColumnAlignment columnAlignments[MAX_COWS];

    unsigned computeLeftPadding(unsigned lenValue, const ColumnAlignment& alignment) const;
    void printValue(int indexCol, const Value& value) const;
    void printRow(const Row& row) const;
    void printHeader() const;
    void loadValue(std::ifstream& inFile, Value& value);
    void loadRow(std::ifstream& inFile, Row& value);
    void setCountCols(std::ifstream& inFile);
    void setAlignment(std::ifstream& inFile);
    ColumnAlignment setAlignValue(const char* value);
    void setColWidth();
    void setRows(std::ifstream& inFile);
    int getColIndexByName(const char* name) const;
    bool isRowStringValid(const char* rowString) const;
    void saveRowToFile(std::ofstream& outFile, const Row& row) const;
    void saveColAlignentsToFile(std::ofstream& outFile) const;
    void savePaddingToFile(std::ofstream& outFile, int times) const;
    unsigned getMaxValueWidthInRow(const Row& row) const;

public:
    Table(const char* fileName);
    Table() {};
    bool load(const char* fileName);
    void printTable() const;
    bool setColName(const char* currentName, const char* newName);
    bool setValue(const char* colName, unsigned rowNumber, const char* newValue);
    bool setValue(const char* colName, const char* currValue, const char* newValue);
    void selectRowsByValue(const char* colName, const char* value) const;
    bool addRow(const char* rowString);
    bool saveToFile(const char* fileName) const;
};
