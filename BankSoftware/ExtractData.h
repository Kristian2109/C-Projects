/**
*
* Solution to course project # 9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Kristian Petrov
* @idnumber 8MI0600201
* @compiler MSVC
*
* <header with functions for extracting data from the arrays>
*
*/

#pragma once
#include <iostream>
#include <limits>

#include "HelperFunctions.h"
using namespace std;

int checkNameEndIndex(char* line, char* name) {
    int index = 0;
    while (name[index] != '\0') {
        if (line[index] != name[index]) {
            return 0;
        }
        index++;
    }
    return ((line[index] == ':') ? index : 0);
}
int findUserIndexByName(char** fileData, char* name) {
    int index = 0;
    while (fileData[index][0] != '\0') {
        if (checkNameEndIndex(fileData[index], name) != 0) {
            return index;
        }
        index++;
    }
    return -1;
}
double getAmountOfMoneyFromUserLine(char* line, int indexToBegin) {
    double result = 0;
    bool isNegative = false;
    if (line[indexToBegin] == '-') {
        isNegative = true;
        indexToBegin++;
    }

    while (line[indexToBegin] != '\0') {
        if (line[indexToBegin] == '.') {
            indexToBegin++;
            continue;
        }
        result *= 10;
        result += fromCharToInt(line[indexToBegin++]);
    }
    return ((isNegative) ? -(result / 100) : (result / 100));
}

double getBallanceInDouble(char** data, int index, int infoIndex) {
    int beginIndexBalance = findBeginIndexData(data[index], 2);
    return getAmountOfMoneyFromUserLine(data[index], beginIndexBalance);
}

void getBallanceChar(char** fileData, char* ballance, int indexUser) {
    int beginIndexBalance = findBeginIndexData(fileData[indexUser], 2);
    int index = 0;

    while (fileData[indexUser][beginIndexBalance] != '\0') {
        ballance[index++] = fileData[indexUser][beginIndexBalance++];
    }
}

double turnCharIntoDouble(char* doubleChar) {
    double result = 0;
    int index = 0;
    int numberToAdd = 0;
    int numberOfDigitsAfterPoint = 0;
    bool isWithComa = false;
    while (doubleChar[index] != '\0') {
        numberToAdd = (doubleChar[index++] - 48);
        if (numberToAdd < 0 || numberToAdd > 9) {
            isWithComa = true;
            continue;
        }
        if (isWithComa) {
            if (numberOfDigitsAfterPoint == 2) {
                break;
            }
            numberOfDigitsAfterPoint++;
        }
        result *= 10;
        result += numberToAdd;
    }
    return result / (pow(10, numberOfDigitsAfterPoint));
}