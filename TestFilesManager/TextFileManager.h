#pragma once
#include <iostream>
#include "File.h"

enum class SortOptions 
{
	Name,
	CreationTime,
	ModificationTime,
	Size
};

class TextFileManager
{
private:
	unsigned maxCountFiles;
	unsigned countFiles;
	File* files;
	int getFileIndexByName(const char* fileName) const;
	bool isFileInManager(const char* fileName) const;

public:

	TextFileManager(int countFiles);
	void addFile(const char* fileName, size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds, const char* rightsStr);

	void editFile(const char* fileName, const char* text, size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds, char role);

	void addInFile(const char* fileName, const char* text, size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds, char role);

	void deleteFile(const char* fileName);

	void changeRights(const char* fileName, char role, char right);

	void printFile(const char* fileName, char role) const;

	void printFileInfo(const char* fileName) const;

	void print() const; // Prints the names of all files

	void sort(SortOptions criteria);

	~TextFileManager();
};
