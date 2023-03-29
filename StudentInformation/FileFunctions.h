#pragma once

#include <iostream>
#include <fstream>
#include "Student.h"
#include "HelperFunctions.h"
using namespace std;
const string DATA_FILE = "data.txt";
const int MAX_LENGTH_LINE = 300;
const int MAX_STUDENTS_COUNT = 200;

void GetDataFromFile(vector<Student>& students, string fileName) {
	ifstream file(fileName, ios::in);
	vector<string> rawStudentData (MAX_STUDENTS_COUNT);
	
	if (!file.is_open()) return;
	int indexUnit = 0;
	while (file >> rawStudentData[indexUnit]) {
		string name;
		string idNumber;
		double group;
		vector<string> disciplines;
		vector<double> notes;
		SplitStudentData(rawStudentData[indexUnit], name, idNumber, group, disciplines, notes);
		Student student(name, idNumber, group);
		for (string disc : disciplines) {
			student.setDiscipline(disc);
		}
		for (double note : notes) {
			student.setNote(note);
		}
		students.push_back(student);
		indexUnit++;
	}
	file.close();
}

string NameWithoutSpaces(string name) {
	string result;
	for (char symbol : name) {
		if (symbol != ' ') result.push_back(symbol);
	}
	return result;
}

void AppendStudentToFile(Student student, string fileName) {
	ofstream file(fileName, ios::out | ios::app);
	string name = NameWithoutSpaces(student.getName());
	file << name << ';' << student.getId() << ';'
		 << student.getGroup();
	if (student.getDisciplines().size() > 0) {
		file << ';';
		for (int i = 0; i < student.getDisciplines().size(); i++) {
			file << student.getDisciplines()[i];
			if ((i + 1) != student.getDisciplines().size()) file << ',';
		}
		file << ';';
		for (int i = 0; i < student.getNotes().size(); i++) {
			file << student.getNotes()[i];
			if ((i + 1) != student.getNotes().size()) file << ',';
		}
	}
	file << '\n';
	file.close();
}

void OverwriteFile(vector<Student> students, string fileName) {
	ofstream file(fileName, ios::out);
	file.close();
	for (Student student : students) {
		AppendStudentToFile(student, fileName);
	}
}