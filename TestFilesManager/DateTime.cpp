#include "DateTime.h"

DateTime::DateTime(size_t day, size_t month, size_t year,
				   size_t hours, size_t mins, size_t seconds)
				   : date(day, month, year), time(hours, mins, seconds)
{}

DateTime::DateTime() : date(1, 1, 2022), time()
{}

void DateTime::setDate(size_t day, size_t month, size_t year)
{
	this->date.setDay(day);
	this->date.setMonth(month);
	this->date.setYear(year);
}

void DateTime::setTime(size_t hours, size_t mins, size_t seconds)
{
	this->time.setHours(hours);
	this->time.setMins(mins);
	this->time.setSeconds(seconds);
}

void DateTime::setDateTime(size_t day, size_t month, size_t year,
	size_t hours, size_t mins, size_t seconds)
{
	setDate(day, month, year);
	setTime(hours, mins, seconds);
}

int DateTime::compare(const DateTime& anotherDateTime) const
{
	int resultComparisonDate = this->date.compare(anotherDateTime.date);
	if (resultComparisonDate != 0)
		return resultComparisonDate;
	else
	{
		return this->time.compare(anotherDateTime.time);
	}
}

void DateTime::print() const
{
	time.print();
	std::cout << ' ';
	date.print();
}