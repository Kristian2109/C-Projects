#pragma once
#include <iostream>

#include "Student.h"
#include "HelperFunctions.h"
using namespace std;

void RenderGreeting() {
	PrintSymbol('\n', 3);
	PrintSymbol('=', 120); cout << '\n';
	cout << "\t\t\t\t\t    HELLO TO STUDENT INFORMATION!\n";
}

void RenderGreeting(string specialty) {
	PrintSymbol('\n', 3);
	PrintSymbol('=', 120); cout << '\n';
	for (int i = 1; i < specialty.size(); i++) {
		if (specialty.at(i) == 32) continue;
		specialty.at(i) -= 32;
	}
	cout << "\t\t\t\t\t    WELCOME TO " << specialty << "!\n";
}

void RenderLogo(string specialty) {
	RenderGreeting(specialty);
	PrintCenterLine("Choose one option.");
	PrintCenterLine("R - register student");
	PrintCenterLine("G - see sorted group");
	PrintCenterLine("A - see all groups");
	PrintCenterLine("C - change student data");
	PrintCenterLine("Q - quit\n");
	PrintSymbol('=', 120); cout << '\n';
}

void PrintContent(string content, int neccessarySpace) {
	cout << content;
	for (int i = 0; i < neccessarySpace - content.size(); i++) {
		cout << ' ';
	}
}

void PrintHeaderOfColumns() {
	cout << "\nName\t\t\t      " << "ID\t     " << "Group\t" << "Average Grade\n";
}

void PrintStudent(Student student) {
	PrintContent(student.getName(), 30);
	PrintContent(student.getId(), 15);
	cout << student.getGroup() << "\t\t";
	cout << student.getAvgNote();
	cout << endl;
}

void PrintDisciplines(Student student) {
	if (student.getDisciplines().size() == 0) return;
	PrintSymbol('=', 120);
	PrintCenterLine("Disciplines"); cout << "\t Notes";
	for (int i = 0; i < student.getDisciplines().size(); i++) {
		PrintSymbol('\n', 1);
		PrintSymbol('\t', 6);
		PrintContent(student.getDisciplines().at(i), 18);
		cout << student.getNotes().at(i);
	}
	PrintSymbol('\n', 1);
}

void RenderChangeOptions() {
	PrintCenterLine("You can choose from the following options:");
	PrintCenterLine("A - add discipline");
	PrintCenterLine("R - remove discipline");
	PrintCenterLine("G - change grade");
	PrintCenterLine("S - stop and get back\n");
}

void RenderStudentDataWithOptions(Student student) {
	system("CLS");
	PrintSymbol('=', 120);
	PrintHeaderOfColumns();
	PrintStudent(student); cout << '\n';
	PrintDisciplines(student);
	PrintSymbol('=', 120);
}
