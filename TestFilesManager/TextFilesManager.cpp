#include "TextFilesManager.h"

namespace messages
{
	const char notExisting[MAX_LEN_NAME] = "Not existing file!\n";
}

TextFilesManager::TextFilesManager(int countFiles)
{
	this->countFiles = 0;
	this->maxCountFiles = countFiles;
	this->files = new File[countFiles];
}

TextFilesManager::~TextFilesManager()
{
	delete[] this->files;
}

int TextFilesManager::getFileIndexByName(const char* fileName) const
{
	for (size_t i = 0; i < this->countFiles; i++)
	{
		if (strcmp(fileName, this->files[i].getName()) == 0)
		{
			return i;
		}
	}

	return -1;
}

void TextFilesManager::addFile(const char* fileName,
	size_t hours, size_t mins, size_t seconds,
	size_t day, size_t month, size_t year, const char* rightsStr)
{
	this->files[this->countFiles].initFile(fileName, day, month, year, hours, mins, seconds, rightsStr);
	this->countFiles++;
}

void TextFilesManager::editFile(const char* fileName, const char* text,
	size_t hours, size_t mins, size_t seconds,
	size_t day, size_t month, size_t year, char role)
{
	int fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}
	this->files[fileIndex].overwrite(text, day, month, year, hours, mins, seconds, role);
}

void TextFilesManager::addInFile(const char* fileName, const char* text,
	size_t hours, size_t mins, size_t seconds,
	size_t day, size_t month, size_t year, char role)
{
	int fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}
	this->files[fileIndex].append(text, day, month, year, hours, mins, seconds, role);
}

//??? I shoud ask
void TextFilesManager::deleteFile(const char* fileName)
{
	int fileIndex = getFileIndexByName(fileName);
	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}

	this->files[fileIndex] = this->files[this->countFiles - 1];
	this->files[this->countFiles - 1].setDefaultValues();
	this->countFiles--;
}

void TextFilesManager::changeRights(const char* fileName, char role, char right)
{
	int fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}
	this->files[fileIndex].changeRights(role, right);
}

// Prints the content of the file
void TextFilesManager::printFile(const char* fileName, char role) const
{
	int fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}
	this->files[fileIndex].print(role);
}

void TextFilesManager::printFileInfo(const char* fileName) const
{
	int fileIndex = getFileIndexByName(fileName);

	if (fileIndex == -1)
	{
		std::cout << messages::notExisting;
		return;
	}
	this->files[fileIndex].printInfo();
}

void TextFilesManager::print() const
{
	for (size_t i = 0; i < this->countFiles; i++)
	{
		std::cout << this->files[i].getName();

		if (i != countFiles - 1) std::cout << '\n';
	}
	std::cout << std::endl;
}// Prints the names of all files

int compare(const File& file1, const File& file2, SortOptions criteria)
{
	switch (criteria)
	{
	case SortOptions::name:
		return strcmp(file1.getName(), file2.getName());
	case SortOptions::creationTime:
		return file1.getCreatedAt().compare(file2.getCreatedAt());
	case SortOptions::modificationTime:
		return file1.getLastlyModified().compare(file2.getLastlyModified());
	case SortOptions::size:
		if (file1.getSize() > file2.getSize())
			return 1;
		else if (file1.getSize() > file2.getSize())
			return -1;
		else return 0;
	default:
		return 1;
	}
	return 1;
}

void TextFilesManager::sort(SortOptions criteria)
{
	for (size_t i = 0; i < this->countFiles - 1; i++)
	{
		int maxIndex = i;
		for (size_t fileIndex = i + 1; fileIndex < countFiles; fileIndex++)
		{
			if (compare(this->files[fileIndex], this->files[maxIndex], criteria) > 0)
			{
				maxIndex = fileIndex;
			}
		}
		std::swap(this->files[maxIndex], this->files[i]);
	}
}