#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

class Date{
    private:
        int day;
        int month;
        int year;
        int hour;
        int minute;
        int second;
        // string weekday;

    public:
        Date();
        Date(int day, int month, int year, int hour, int minute, int second);
        Date(const Date &date);
        ~Date() = default;

        // Getters
        Date& operator=(const Date& date) = default;
        int getDay() const;
        int getMonth() const;
        int getYear() const;
        int getHour() const;
        int getMinute() const;
        int getSecond() const;
        std::string getDateBystring() const;

        // ======= Setters =======

        void setDay(int day);
        void setMonth(int month);
        void setYear(int year);
        void setHour(int hour);
        void setMinute(int minute);
        void setSecond(int second);
        void setDateBystring(const std::string& dateStr);

        // ======= Methods =======

        void updateDate(int day, int month, int year, int hour, int minute, int second);
        void updateDate(const Date &date);
        void updateDate();
        
        void printDate() const;
};

#endif // DATE_H