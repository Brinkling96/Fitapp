#include "Date.hpp"

const char * DateRangeException::what() const throw (){
    return "Date Range Exception, make sure to check your date is a valid date!";
}

Date::Date(unsigned short year,   unsigned short month,   unsigned short day){
    if(year >2200 || year < 1950 || month > 12 || month < 1){ //
        throw DateRangeException();
    }

    //checking valid day for each month
    switch (month){
        case 2:
            //Have to check for leap year in Feb
            if((year % 400 == 0) || ((year % 4 ==0) && (year % 100 != 0))){
                if (day > 29 || day < 1){
                    throw DateRangeException();
                }
            } else {
                if (day > 28 || day < 1){
                    throw DateRangeException();
                }
            }

            break;

        //Using fallthrough to cover 30 day months
        case 4:
        case 6:
        case 9:
        case 11:
            if (day > 30 || day < 1){
                throw DateRangeException();
            }
            break;

        //Default is 31 day months
        default:
            if (day > 31 || day < 1){
                throw DateRangeException();
            }
            break;
    }
    this->year = year;
    this->month = month;
    this->day = day;
}


Date::Date(){
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    this->year = (unsigned short) now->tm_year+1900;
    this->month= (unsigned short) now->tm_mon+1;
    this->day = (unsigned short) now->tm_mday;
}


const std::string Date::toString() const{
    std::stringstream ss;
    ss << year <<"-"<<month<<"-"<<day;
    return ss.str();
}