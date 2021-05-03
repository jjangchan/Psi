//
// Created by jjangchan on 2021-04-30.
//

#ifndef PSI_EX2_NEW_DELETE_H
#define PSI_EX2_NEW_DELETE_H

#include <string>
#include <iostream>

#define YEAR 60*60*24*365
#define DAY 60*60*24

class Data{
private:
    int year_;
    int month_;
    int day_;
    int unix_time

public:
    void SetData(int year, int month, int data)
    {
        std::string str = CheckNoiseData(year, month, data);
        cout << str << endl;
    }

    void AddDay(int increase)
    {

    }

    void AddMonth(int increase)
    {

    }

    void AddYear(int increase)
    {

    }

private:
    int CalculateLastDay(const int index)
    {
        int last_day_array[3];
        // leap month
        last_day_array[2] = (year_%4 == 0) ? 29 : 28;

        // odd month
        last_day_array[1] = (month_ >= 8) ? 30 : 31;

        // even month
        last_day_array[0] = (month_ >= 8) ? 31 : 30;

        return  last_day_array[index];
    }

    std::string CheckNoiseData(const int year,const int month, const int day)
    {
        std::string str = "[Info] Data Setup Completed";
        if(year < 1970)
        {
            str = "[Error] the year must be greater than 1970";
            return  str;
        }

        if(month <= 0 || month > 12)
        {
            str = "[Error] the month must be greater than 0 and less than 13";
            return str;
        }

        if(day <= 0)
        {
            str = "[Error] the data must be greater than 0";
            return  str;
        }

        year_ = year;
        month_ = month;
        day_ = day;
        return  str;
    }
};

#endif //PSI_EX2_NEW_DELETE_H
