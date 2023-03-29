#include "File.h"
#include <fstream>
#include <sstream>

namespace errors
{
	const char notAuthorizedEdit[MAX_LEN_CONTENT] = "Error! You do not have the rights to edit!\n";
	const char notAuthorizedRead[MAX_LEN_CONTENT] = "Error! You do not have the rights to read!\n";
	const char notAuthorizedAppend[MAX_LEN_CONTENT] = "Error! You do not have the rights to append!\n";
}

File::File(const char* fileName,
	size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds,
	const char* rightsStr)
{
	setName(fileName);
	setCreatedAt(day, month, year, hours, mins, seconds);
	setRights(rightsStr);
	this->sizeInBytes = 0;
}

File::File()
{
	setDefaultValues();
}

bool File::initFile(const char* fileName,
	size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds,
	const char* rightsStr)
{
	setName(fileName);
	setCreatedAt(day, month, year, hours, mins, seconds);
	setLastModified(day, month, year, hours, mins, seconds);
	setRights(rightsStr);
	return true;
}


void File::setDefaultValues()
{
	setName("default");
	setRights("rwx------");
	setContent("");
	setCreatedAt(1, 1, 1, 1, 1, 1);
	setLastModified(1, 1, 1, 1, 1, 1);
	this->sizeInBytes = 0;
}

size_t File::getSize() const
{
	return this->sizeInBytes;
}

const DateTime& File::getCreatedAt() const
{
	return this->createdAt;
}

const DateTime& File::getLastlyModified() const
{
	return this->lastModifiedAt;
}

const char* File::getName() const
{
	return this->name;
}

bool File::setName(const char* fileName)
{
	if (strlen(fileName) > MAX_LEN_NAME)
	{
		return false;
	}

	strcpy_s(this->name, fileName);
	return true;
}

bool File::areRoleRightsValid(const char* roleStr) const
{
	if (roleStr[0] != 'r' && roleStr[0] != '-')
		return false;
	if (roleStr[1] != 'w' && roleStr[1] != '-')
		return false;
	if (roleStr[2] != 'x' && roleStr[2] != '-')
		return false;

	return true;
}

bool File::isRightsStrValid(const char* rightsStr) const
{
	int len = strlen(rightsStr);
	if (len != SIZE_RIGHTS - 1)
		return false;

	return areRoleRightsValid(rightsStr) &&
		areRoleRightsValid(rightsStr + 3) &&
		areRoleRightsValid(rightsStr + 6);
}

bool File::setRights(const char* rightsStr)
{
	if (!isRightsStrValid(rightsStr))
		return false;

	strcpy_s(this->rights, rightsStr);
	return true;

}

void File::setCreatedAt(size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds)
{
	this->createdAt.setDateTime(day, month, year, hours, mins, seconds);
}

void File::setContent(const char* text)
{
	std::stringstream buffer(text);
	buffer.getline(this->content, MAX_LEN_CONTENT, '\0');
	setSize();
	this->content[this->sizeInBytes] = '\0';
}

bool File::overwrite(const char* text,
	size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds,
	char role)
{

	if (!isAuthorized(role, 'w'))
	{
		std::cout << errors::notAuthorizedEdit;
		return false;
	}

	if (!validateContentSize(text))
		return false;

	setContent(text);

	setLastModified(day, month, year, hours, mins, seconds);
	std::cout << this->content << '\n';
	std::cout << "Last modified on: "; this->lastModifiedAt.print();
	return true;
}

void File::setLastModified(size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds)
{
	this->lastModifiedAt.setDateTime(day, month, year, hours, mins, seconds);
}

void File::setSize()
{
	this->sizeInBytes = strlen(this->content);
}

void File::appendContent(const char* text)
{
	std::stringstream buffer(text);
	this->content[this->sizeInBytes++] = '\n';
	this->content[this->sizeInBytes] = '\0';
	buffer.getline(this->content + strlen(this->content), MAX_LEN_CONTENT);
	setSize();
}

bool File::validateContentSize(const char* text)
{
	return this->sizeInBytes + strlen(text) < MAX_LEN_CONTENT;
}

bool File::append(const char* text,
	size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds,
	char role)
{
	if (!isAuthorized(role, 'w'))
	{
		std::cout << errors::notAuthorizedAppend;
		return false;
	}

	if (!validateContentSize(text))
		return false;

	appendContent(text);

	setLastModified(day, month, year, hours, mins, seconds);
	std::cout << this->content << '\n';
	std::cout << "Last modified on: "; this->lastModifiedAt.print();
	return true;
}

void File::print(char role) const
{
	if (!isAuthorized(role, 'r'))
	{
		std::cout << errors::notAuthorizedRead;
		return;
	}
	
	std::cout << this->content;
}

void File::printInfo() const
{
	std::cout << "Name: " << this->name << '\n';
	std::cout << "Size: " << this->sizeInBytes << '\n';
	std::cout << "Created at: "; this->createdAt.print();
	std::cout << "Last modified: "; this->lastModifiedAt.print();
	std::cout << "Rights: " << this->rights; std::cout << '\n';
}

bool File::isAuthorized(char role, char right) const
{
	int rightIndex = (right == 'r') ? 0 : (right == 'w') ? 1 : 2;

	// Here we add 3 and 6 because the rights of the group begin from the 3th index
	// These of the others begin from the 6th
	switch (role)
	{
	case 'u':
		return this->rights[rightIndex] == right;
	case 'g':
		return this->rights[rightIndex + 3] == right;
	case 'o':
		return this->rights[rightIndex + 6] == right;
	default:
		break;
	}
	return false;
}

bool File::validateAction(char action) const
{
	return action == 'w' || action == 'e' || action == 'r';
}

bool File::validateRole(char action) const
{
	return action == 'u' || action == 'g' || action == 'o';
}

void File::changeRight(char& rightString, char right)
{
	if (rightString == right)
		rightString = '-';
	else
		rightString = right;
}

bool File::changeRights(char role, char right)
{
	if (!validateAction(right) || !validateRole(role))
		return false;

	int rightIndex = (right == 'r') ? 0 : (right == 'w') ? 1 : 2;
	switch (role)
	{
	case 'u':
		changeRight(this->rights[rightIndex], right);
		break;
	case 'g':
		changeRight(this->rights[rightIndex + 3], right);
		break;
	case 'o':
		changeRight(this->rights[rightIndex + 6], right);
		break;
	default:
		return false;
		break;
	}

	return true;
}
