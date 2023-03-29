#include <iostream>
#include "Services.h"
#include "FileFunctions.h"
#include "RenderFunctions.h"
vector<Student> students;
const vector<string> SPECIALTIES = { "Mathematics", "Software engineering", "Hardware engineering", "Computer Science", "Informatics" };

void RenderSpecialties() {
	PrintSymbol('=', 120); PrintSymbol('\n', 1);
	PrintCenterLine("These are the specialties you can choose from.\n");
	PrintSymbol('=', 120); PrintSymbol('\n', 1);
	for (int i = 0; i < SPECIALTIES.size(); i++) {
		cout << "\n\t\t\t\t\t" << i << " - " << SPECIALTIES.at(i);
	}
}

void ExecuteSpecialty(string specialty) {
	string fileName = specialty;
	fileName.append(".txt");
	GetDataFromFile(students, fileName);
	char action = 0;
	while (action != 'Q' && action != 'q') {
		system("CLS");
		RenderLogo(specialty);
		action = GetCharInput();
		switch (action) {
		case 'R':
		case 'r':
			RegisterStudent(students);
			break;
		case 'A':
		case 'a':
			ShowStudents(students, 0);
			break;
		case 'G':
		case 'g':
			ShowStudents(students, 1);
			break;
		case 'C':
		case 'c':
			ExecuteChangeStudentData(students);
			break;
		default:
			break;
		}
	}
	OverwriteFile(students, fileName);
}

void ExecuteStudentInformationProject() {
	string choise = "0";
	string specialty;
	while (true) {
		system("CLS");
		RenderGreeting();
		RenderSpecialties(); PrintSymbol('\n', 1);
		PrintCenterLine("Enter the specialty you want to access:  ");

		getline(cin, choise);
		int indexSpecialty = choise.at(0) - '0';
		if (choise.size() == 1 && indexSpecialty >= 0 && indexSpecialty <= SPECIALTIES.size()) {
			specialty = SPECIALTIES.at(indexSpecialty);
			ExecuteSpecialty(specialty);
		}
		else if (choise == "-1") {
			PrintCenterLine("You've successfuly quited the program.");
			return;
		}
		else {
			PrintCenterLine("Incorrect input! Try again.");
			Pause();
		}
	}
}

int main()
{
	ExecuteStudentInformationProject();
}
