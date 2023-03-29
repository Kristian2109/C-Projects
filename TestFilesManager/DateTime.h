#pragma once
#include "Date.h"
#include "Time.h"
class DateTime
{
private:

	Date date;
	Time time;
	void setDate(size_t day, size_t month, size_t year);
	void setTime(size_t hours, size_t mins, size_t seconds);

public:
	DateTime(size_t day, size_t month, size_t year, size_t hours, size_t mins, size_t seconds);
	DateTime();

	int compare(const DateTime& anotherDateTime) const;
	void setDateTime(size_t day, size_t month, size_t year, size_t hours, size_t mins, size_t seconds);
	void print() const;
};

