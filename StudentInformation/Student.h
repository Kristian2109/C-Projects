#pragma once
#include <string>
#include <vector>
#include "Student.h"
using namespace std;

class Student {
	private:
		string name;
		string idNumber;
		vector <string> disciplines;
		vector <double> notes;
		int group;
		double averageNote;
public:
	Student(string name, string idNumber, int group) {
		this->setName(name);
		this->setIdNumber(idNumber);
		this->group = group;
	}

	Student(string name, string idNumber, vector<string> disciplines, vector <double> notes) {
		this->setName(name);
		this->setIdNumber(idNumber);
		for (int i = 0; i < disciplines.size(); i++) {
			this->setDiscipline(disciplines[i]);
			this->setNote(notes[i]);
		}
	}
	string getName() {
		return this->name;
	}
	string getId() {
		return this->idNumber;
	}
	int getGroup() {
		return this->group;
	}
	vector<string> & getDisciplines() {
		return this->disciplines;
	}
	vector<double> & getNotes() {
		return this->notes;
	}
	double getAvgNote() {
		if (this->notes.size() == 0) return 0.0;
		return this->averageNote;
	}
	bool setName(string name) {
		this->name = name;
		return true;
	}
	bool setIdNumber(string idNumber) {
		this->idNumber = idNumber;
		return true;
	}
	double findAverageNote() {
		double sumNotes = 0;
		for (double note : this->notes) {
			if (note != 0) sumNotes += note;
		}

		double avgNote = sumNotes / this->notes.size();
		return round(avgNote * 100) / 100;
	}
	bool setNote(double note) {
		this->notes.push_back(note);
		this->averageNote = findAverageNote();
		return true;
	}
	bool setDiscipline(string discipline) {
		this->disciplines.push_back(discipline);
		return true;
	}
	void showDisciplines() {
		for (string disc : this->disciplines) {
			cout << disc << "  ";
		}
	}
	void showNotes() {
		for (double note : this->notes) {
			cout << note << "  ";
		}
	}
};
