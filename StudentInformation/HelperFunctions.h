#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Student.h"
using namespace std;
const int NUM_TABS_CENTER = 5;

void GetName(string rawData, string& name) {
	int index = 0;
	while (rawData[index] != ';') {
		if (index != 0 && isHighLetter(rawData[index])) {
			name.push_back(' ');
		}
		name.push_back(rawData[index]);
		index++;
	}
}

vector<int> DelimiterIndexes(string rawData) {
	vector<int> indexes;
	for (int i = 0; i < rawData.size(); i++) {
		if (rawData[i] == ';') indexes.push_back(i);
	}
	return indexes;
}

void SplitDisciplines(string rawDisciplines, vector<string>& disciplines) {
	int currentIndex = 0;
	for (int i = 0; i < rawDisciplines.size(); i++) {
		if (rawDisciplines[i] == ',') {
			currentIndex++; i++;
		}
		if (disciplines.size() == currentIndex) {
			string newString;
			disciplines.push_back(newString);
		}
		disciplines[currentIndex].push_back(rawDisciplines[i]);
	}
}

void SplitNotes(string rawNotes, vector<double>& notes) {
	string noteString;
	for (int i = 0; i < rawNotes.size(); i++) {
		if (rawNotes[i] == ',') {
			i++;
			double note = stod(noteString);
			notes.push_back(note);
			noteString.clear();
		}
		noteString.push_back(rawNotes[i]);
		if (i + 1 == rawNotes.size()) {
			double note = stod(noteString);
			notes.push_back(note);
		}
	}
}

void SplitStudentData(string rawData, string& name, string& idNumber, double& group, vector<string>& disciplines, vector<double>& notes) {
	GetName(rawData, name);
	vector<int> delimiters = DelimiterIndexes(rawData);
	idNumber = rawData.substr(delimiters[0] + 1, delimiters[1] - delimiters[0] - 1);
	group = rawData[delimiters[1] + 1] - '0';
	if (delimiters.size() > 2) {
		string rawDisciplines = rawData.substr(delimiters[2] + 1, delimiters[3] - delimiters[2] - 1);
		SplitDisciplines(rawDisciplines, disciplines);
		string rawNotes = rawData.substr(delimiters[3] + 1);
		SplitNotes(rawNotes, notes);
	}
}

bool isHighLetter(char letter) {
	return (letter >= 'A' && letter <= 'Z');
}

bool isLowLetter(char letter) {
	return (letter >= 'a' && letter <= 'z');
}

bool isValidName(string name) {
	if (!isHighLetter(name[0])) return false;

	int countSpaces = 0;
	for (int i = 1; i < name.size(); i++) {
		if (name[i] == ' ') {
			countSpaces++; i++;
			if (i < name.size() && !isHighLetter(name[i])) {
				return false;
			}
		}
		else {
			if (!isLowLetter(name[i])) {
				return false;
			}
		}
	}
	return countSpaces == 2;
}

bool isDigit(char digit) {
	return digit >= '0' && digit <= '9';
}

bool isRightIdNumber(string IdNumber) {
	for (int i = 0; i < IdNumber.size(); i++) {
		if (!isLowLetter(IdNumber[i]) && !isHighLetter(IdNumber[i]) &&
			!isDigit(IdNumber[i])) {
			return false;
		}
	}
	return true;
}

void SwapStudent(Student& student1, Student& student2) {
	Student tempStudent = student1;
	student1 = student2;
	student2 = tempStudent;
}

void PrintSymbol(char symbol, int times) {
	for (int i = 0; i < times; i++) cout << symbol;
}

void PrintCenterLine(string text) {
	cout << '\n';
	PrintSymbol('\t', NUM_TABS_CENTER);
	cout << text;
}

void Pause() {
	PrintCenterLine("Press enter to continue.");
	system("pause");
}

char GetCharInput() {
	PrintCenterLine("Enter :  ");
	string someAction;
	getline(cin, someAction);
	return (someAction.size() > 1) ? '!' : someAction[0];
}

char GetChar() {
	string someAction;
	getline(cin, someAction);
	return (someAction.size() > 1) ? '!' : someAction[0];
}

int FindUserById(vector<Student> students, string ID) {
	for (int i = 0; i < students.size(); i++) {
		if (students.at(i).getId() == ID) return i;
	}
	return -1;
}

void SortAllStudents(vector<Student>& students, string criteria) {
	for (int i = 0; i < students.size() - 1; i++) {
		for (int j = 0; j < students.size() - 1 - i; j++) {
			if (criteria == "ID") {
				if (students[j].getId() > students[j + 1].getId()) {
					SwapStudent(students[j], students[j + 1]);
				}
			}
			else if (criteria == "Grade") {
				if (students[j].getAvgNote() < students[j + 1].getAvgNote()) {
					SwapStudent(students[j], students[j + 1]);
				}
			}
		}
	}
}

