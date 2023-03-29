#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Student.h"
#include "RenderFunctions.h"
#include "FileFunctions.h"
#include "HelperFunctions.h"

const int MAX_GROUPS_COUNT = 8;

bool IsValidStudentData(Student student) {
	return isValidName(student.getName()) && isRightIdNumber(student.getId()) &&
		student.getGroup() <= MAX_GROUPS_COUNT;
}

void SetGrade(Student& student) {
	double grade = 0; int counter = 0;

	while (counter < 3) {
		PrintCenterLine("Type the grade between 2 and 6, if you don't have type \"0\":  ");
		string gradeString;
		getline(cin, gradeString);
		grade = stod(gradeString);
		if ((grade >= 2 && grade <= 6) || grade == 0) {
			student.setNote(grade);
			return;
		}
		PrintCenterLine("Incorrect note. Try again");
		counter++;
	}
	student.setNote(0);
	PrintCenterLine("You've made 3 wrong attempts. The note is set to \"0\".");
}

void SetDiscipline(Student& student) {
repeat :
	string discipline;
	PrintCenterLine("Discipline:  ");
	getline(cin, discipline);
	if (discipline.size() < 30) {
		student.setDiscipline(discipline);
		SetGrade(student);
	}
	else {
		PrintCenterLine("The name of the discipline is too long.");
		goto repeat;
	}
}

void SetDisciplines(Student& student) {
	int countDisciplines = 0;
	while (countDisciplines < 1 || countDisciplines > 10) {
		PrintCenterLine("Type the number of your disciplines, at least 1 up to 10:  ");
		countDisciplines = GetChar() - '0';
	}
	for (int i = 1; i <= countDisciplines; i++) {
		SetDiscipline(student);
	}
}

void DeleteStudent(vector<Student>& students, int indexStudent) {
	vector<Student>::iterator itr;
	itr = students.begin() + indexStudent;
	students.erase(itr);
}
