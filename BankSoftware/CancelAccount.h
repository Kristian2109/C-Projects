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
* <header with functions for canceling account>
*
*/

#pragma once
#include <iostream>
#include <limits>

#include "HelperFunctions.h"
#include "ExtractData.h"
#include "LogIn.h"
using namespace std;

void deleteUserLine(char* userLine) {
    for (int i = 0; i < MAX_NAME; i++) {
        userLine[i] = '\0';
    }
}

void moveLineUpwards(char* lineToMove, char* lineToDelete) {
    //lineToMove = lineToDelete;
    deleteUserLine(lineToDelete);
    int index = 0;
    while (lineToMove[index] != '\0') {
        lineToDelete[index] = lineToMove[index];
        index++;
    }
    lineToDelete[index] = '\0';
}

void removeUserProfile(char** fileData, int indexLine) {
    while (fileData[indexLine][0] != '\0') {
        moveLineUpwards(fileData[indexLine + 1], fileData[indexLine]);
        indexLine++;
    }
}

void executeCancelAccount(char** fileData, char* name, int authCode) {
    system("CLS");
    cin.ignore(1);
    int counter = 0;
    while (counter < 3) {
        char password[MAX_PASS];
        enterUserDetails(password, 0);
        if (willGoBack(password)) {
            return;
        }
        system("CLS");
        int userIndex = getUserIndex(fileData, name, password);
        if (userIndex == authCode &&
            getBallanceInDouble(fileData, authCode, 2) == 0) {
            removeUserProfile(fileData, authCode);
            centerText("You've canceled your account.\n", 6);
            Pause(5);
            return;
        }
        else if (userIndex != authCode) {
            centerText("Wrong password. Try again.", 6);
        }
        else {
            centerText("The sum in your account is not 0 leva.\n\n", 5);
            Pause(5);
            return;
        }
        counter++;
    }
    system("CLS"); cout << "\n\n";
    centerText("You've entered your password wrong 3 times. Try again later.\n\n", 4);
    Pause(5);
}