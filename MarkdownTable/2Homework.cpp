#include <iostream>
#include <fstream>
#include <sstream>
#include "Table.h"
#include "StringFunctions.h"

namespace messages
{
    const char saveSuccess[MAX_LINE_LEN] = "File successfully saved!\n";
    const char saveFail[MAX_LINE_LEN] = "Error while saving!\n";
    const char loadSuccess[MAX_LINE_LEN] = "Table loaded successfully!\n";
    const char loadFail[MAX_LINE_LEN] = "Error while loading\n";
    const char operationSuccess[MAX_LINE_LEN] = "Operation successfully executed!\n";
    const char operationFail[MAX_LINE_LEN] = "Error while executing operation!\n";
    const char incorrectInput[MAX_LINE_LEN] = "Incorrect input!\n";
    const char incorrectRow[MAX_LINE_LEN] = "Incorrect row string!\n";
}

void executeSelect(std::stringstream& commandStream, const Table& table)
{
    char colName[MAX_SYMBOLS];
    char value[MAX_SYMBOLS];
    commandStream >> colName;
    commandStream >> value;
    table.selectRowsByValue(colName, value);
}

void executeChange(std::stringstream& commandStream, Table& table)
{
    char currentName[MAX_SYMBOLS];
    char secondValue[MAX_SYMBOLS];
    char thirdValue[MAX_SYMBOLS];
    commandStream >> currentName;
    commandStream >> secondValue;
    commandStream >> thirdValue;
    if (thirdValue[0])
    {
        table.setValue(currentName, secondValue, thirdValue);
        table.printTable();
        return;
    }
    else if (!table.setColName(currentName, secondValue))
    {
        std::cout << messages::operationFail;
        return;
    }
    std::cout << messages::operationSuccess;
}

void executeAddRow(std::stringstream& commandStream, Table& table)
{
    char rowString[MAX_LINE_LEN];
    commandStream.getline(rowString, MAX_LINE_LEN);
    castString(rowString);
    if (!table.addRow(rowString))
    {
        std::cout << messages::incorrectRow;
        return;
    }
    std::cout << messages::operationSuccess;

}

void executeSave(const char* fileName, const Table& table)
{
    if (table.saveToFile(fileName))
    {
        std::cout << messages::saveSuccess;
    }
    else { std::cout << messages::saveFail; }
}

void executeChangeRowValue(std::stringstream& commandStream, Table& table)
{
    int indexRow;
    char colName[MAX_SYMBOLS];
    char newValue[MAX_SYMBOLS];
    commandStream >> indexRow;
    commandStream >> colName;
    commandStream >> newValue;
    if (table.setValue(colName, indexRow, newValue))
    {
        std::cout << messages::operationSuccess;
        return;
    }
    std::cout << messages::operationFail;
}

void executeProgram()
{
    Table table;
    char fileName[MAX_SYMBOLS];

    std::cin.getline(fileName, MAX_SYMBOLS);
    if (!table.load(fileName))
    {
        std::cout << messages::loadFail;
        return;
    }
    std::cout << messages::loadSuccess;

    char concreteCommand[MAX_LINE_LEN];
    char fullCommand[MAX_LINE_LEN];
    while (true)
    {
        std::cin.getline(fullCommand, MAX_LINE_LEN);
        std::stringstream stream(fullCommand);
        stream >> concreteCommand;

        if (strcmp(concreteCommand, commands::print) == 0)
        {
            table.printTable();
        }
        else if (strcmp(concreteCommand, commands::save) == 0)
        {
            stream >> fileName;
            executeSave(fileName, table);
        }
        else if (strcmp(concreteCommand, commands::select) == 0)
        {
            executeSelect(stream, table);
        }
        else if (strcmp(concreteCommand, commands::addRow) == 0)
        {
            executeAddRow(stream, table);
        }
        else if (strcmp(concreteCommand, commands::changeRow) == 0)
        {
            executeChangeRowValue(stream, table);
        }
        else if (strcmp(concreteCommand, commands::change) == 0)
        {
            executeChange(stream, table);
        }
        else
        {
            std::cout << messages::incorrectInput;
        }
    }
}

int main()
{
    executeProgram();
}
