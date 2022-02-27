#pragma once
#include <exception>
#include <string>
#include <ctime>
#include <sstream>

class DateRangeException: public std::exception{
    const char * what() const throw ();
};


class Date{

    private:
    unsigned short year;
    unsigned short month;
    unsigned short day;

    public:
        Date(unsigned short year,   unsigned short month,   unsigned short day);
        Date();

        const std::string toString() const;
};
