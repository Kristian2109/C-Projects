#pragma once
#include "DateTime.h"
const unsigned MAX_LEN_NAME = 64;
const unsigned MAX_LEN_CONTENT = 512;
const unsigned SIZE_RIGHTS = 10;
const unsigned SIZE_RIGHTS_USER = 3;

class File
{
	char name[MAX_LEN_NAME];
	char content[MAX_LEN_CONTENT];
	size_t sizeInBytes;
	DateTime createdAt;
	DateTime lastModifiedAt;
	char rights[SIZE_RIGHTS];

	bool areRoleRightsValid(const char* roleStr) const;
	bool isRightsStrValid(const char* rightsStr) const;
	bool validateAction(char action) const;
	bool validateRole(char action) const;
	bool isAuthorized(char role, char right) const;
	void setLastModified(size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds);
	void setCreatedAt(size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds);
	void changeRight(char& rightString, char right);
	void appendContent(const char* text);
	void setSize();
	void setContent(const char* text);
	bool validateContentSize(const char* text);
	void freeContent();

public:
	File(const char* fileName,
		size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds,
		const char* rightsStr);

	File();

	bool initFile(const char* fileName,
		size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds,
		const char* rightsStr);

	const char* getName() const;
	bool setName(const char* fileName);
	bool setRights(const char* rightsStr);

	size_t getSize() const;
	const DateTime& getCreatedAt() const;
	const DateTime& getLastlyModified() const;

	bool overwrite(const char* text,
		size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds,
		char role);

	bool append(const char* text,
		size_t day, size_t month, size_t year,
		size_t hours, size_t mins, size_t seconds,
		char role);

	bool changeRights(char role, char rightToChange);

	void print(char role) const;

	void printInfo() const;

	void setDefaultValues();
};
