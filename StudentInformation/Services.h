#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Student.h"
#include "RenderFunctions.h"
#include "FileFunctions.h"
#include "HelperFunctions.h"
#include "UpdateData.h"
using namespace std;

void ExecuteSort(vector<Student>& students) {
	PrintCenterLine("Sort the students, type \"ID\" or \"Grade\":  ");
	string criteria; getline(cin, criteria);
	if (criteria != "ID" && criteria != "Grade") {
		criteria = "ID";
	}
	SortAllStudents(students, criteria);
}

void RegisterStudent(vector<Student>& students) {
	string name;
	string idNumber;
	string discipline;
	PrintCenterLine("Enter your three names:  ");
	getline(cin, name);
	PrintCenterLine("Enter your ID number:  "); 
	getline(cin, idNumber);;
	PrintCenterLine("Enter your group:  ");
	int group = GetChar() - '0';
	
	Student student(name, idNumber, group);
	if (FindUserById(students, student.getId()) >= 0) {
		PrintCenterLine("User with this ID is existing!");
		Pause();
		return;
	}
	if (IsValidStudentData(student)) {
		SetDisciplines(student);
		students.push_back(student);
		PrintCenterLine("You've succesfully registered ");
		cout << student.getName() << ".";
		Pause();
		return;
	}

	PrintCenterLine("Invalid student data. The names should be 3.");
	PrintCenterLine("Every begins with high letter, don't put additional spaces.");
	PrintCenterLine("Id Number should have only letters and digits.");
	Pause();
}

void RemoveDiscipline(Student& student) {
	string disciplineToRemove;
	getline(cin, disciplineToRemove);
	vector<string>::iterator itrDisc;
	int indexNoteToRemove = -1;
	for (itrDisc = student.getDisciplines().begin(); itrDisc < student.getDisciplines().end(); itrDisc++) {
		indexNoteToRemove++;
		if (*itrDisc == disciplineToRemove) {
			student.getDisciplines().erase(itrDisc);
			break;
		}
		if (itrDisc + 1 == student.getDisciplines().end()) {
			PrintCenterLine("Not such a discipline!");
			return;
		}
	}
	vector<double>::iterator itrNotes;
	itrNotes = student.getNotes().begin() + indexNoteToRemove;
	student.getNotes().erase(itrNotes);
}

void ChangeGrade(Student& student) {
	string discipline;
	PrintCenterLine("Enter the discipline which grade you want to change:  ");
	getline(cin, discipline);

	int indexNote = -1;
	for (int i = 0; i < student.getDisciplines().size(); i++) {
		if (student.getDisciplines().at(i) == discipline) {
			indexNote = i;
		}
	}
	if (indexNote == -1) {
		PrintCenterLine("Unexisting discipline!");
		return;
	}

	PrintCenterLine("Enter the new note:  ");
	double newNote;
	cin >> newNote;
	student.getNotes().at(indexNote) = newNote;
}

void ChangeStudentData(vector<Student>& students, Student& student, int indexStudent) {
	char userAction = '0';
	while (userAction != 's' && userAction != 'S') {
		RenderStudentDataWithOptions(students.at(indexStudent));
		RenderChangeOptions();
		userAction = GetCharInput();
		switch (userAction)
		{
		case 'A':
		case 'a':
			SetDiscipline(student);
			PrintCenterLine("The actual disciplines are:  \n");
			PrintDisciplines(student);
			Pause();
			break;
		case 'D':
		case 'd':
			DeleteStudent(students, indexStudent);
		case 'R':
		case 'r':
			PrintCenterLine("Type the name of the discipline:  ");
			RemoveDiscipline(student);
			Pause();
			break;
		case 'G':
		case 'g':
			ChangeGrade(student);
			break;
		case '!':
			PrintCenterLine("Incorrect input!");
			break;
		default:
			break;
		}
	}
	
}

void ExecuteChangeStudentData(vector<Student>& students) {
	if (students.size() == 0) {
		PrintCenterLine("This specialty is empty!");
		Pause();
		return;
	}
	PrintSymbol('=', 120);
	PrintCenterLine("Give the ID:  ");
	string searchedId; getline(cin, searchedId);
	int indexStudent = FindUserById(students, searchedId);
	if (indexStudent == -1) {
		PrintCenterLine("Invalid user ID. Try again.");
		Pause();
		return;
	}
	ChangeStudentData(students, students.at(indexStudent), indexStudent);
}

void ShowStudents(vector<Student> students, int forGroup) {
	system("CLS");
	if (students.size() == 0) {
		PrintCenterLine("This specialty is empty!");
		Pause();
		return;
	}
	ExecuteSort(students);
	int group = 0;
	if (forGroup) {
		PrintCenterLine("Which group you want to see?:  ");
		group = GetChar() - '0';
		if (group <= 1 || group >= 8) {
			PrintCenterLine("Invalid group. Groups are from 1 to 8.");
			Pause();
			return;
		}
	}
	PrintHeaderOfColumns();
	for (Student student : students) {
		if (group == 0 || student.getGroup() == group) {
			PrintStudent(student);
		}
	}
	Pause();
}
