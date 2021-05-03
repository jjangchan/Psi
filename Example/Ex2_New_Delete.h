//
// Created by jjangchan on 2021-04-30.
//

#ifndef PSI_EX2_NEW_DELETE_H
#define PSI_EX2_NEW_DELETE_H

#include <string>
#include <iostream>

#define YEAR (60*60*24*365)
#define DAY (60*60*24)
#define INITYEAR 1970

class Data{
private:
    int year_;
    int month_;
    int day_;

    //utc+0
    int unix_time;
    int month_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum_array[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

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
        int month = month_+increase;
        year_ += month/12;
        //month_array[1] = CalculateLeap();
    }

    void AddYear(int increase)
    {
        year_ += increase;
        //month_array[1] = CalculateLeap();
    }

private:
    int CalculateLeap(const int year_distance)
    {
        int leap = (year_distance+2)/4;
        int cal_leap = ((year_distance+2)%4 == 0 && month_ < 3) ? --leap : leap;
        return cal_leap;
    }


    int DateToUnix()
    {
        int unix = 0;
        int year_distance = year_-INITYEAR;
        unix = (year_distance * YEAR) + ((day_+sum_array[month_-1]+CalculateLeap(year_distance)-1)*DAY);
        return unix;
    }

    void UnixToDate()
    {
        double year = (double)unix_time/(double)YEAR;
        year_ = INITYEAR+(int)year;
        int year_distance = year_-INITYEAR;
        double day = (year-(int)year) * 365;
        cout << year_ << endl;
        int weight = (year_%4 == 0) ? 1 : 0;
        day = day-CalculateLeap(year_distance)+1+weight;
        cout << "day : " << day << endl;
        cout << weight << endl;
        day = (day < 0) ? 365+day: day;
        int month = BinarySearchToValue(day, 0, 11);
        cout << "month : " << month_<< endl;
        cout << "day : " << day << endl;
    }

    double CalculateDay(const int* array, const int index, const int day)
    {
        if(index == 3)
        {
            return (double)day/365.0;
        }
        return CalculateDay(array, index+1, day/array[index]);
    }

    int BinarySearchToValue(const double price, const int low, const int high)
    {
        if (low > high)
        {
            return low;
        }
        int mid = (low + high) / 2;
        if (sum_array[mid] == price)
        {
            return mid;
        }
        else if (sum_array[mid] < price)
        {
            return BinarySearchToValue(price, mid + 1, high);
        }
        else
        {
            return BinarySearchToValue(price, low, mid - 1);
        }
    }


    std::string CheckNoiseData(const int year,const int month, const int day)
    {
        std::string str = "[Info] Data Setup Completed";
        year_ = year;
        month_ = month;
        day_ = day;

        if(year < 1970)
        {
            str = "[Error] the year must be greater than 1969";
            return  str;
        }

        if(month <= 0 || month > 12)
        {
            str = "[Error] the month must be greater than 0 and less than 13";
            return str;
        }

        int leap = (year_%4 == 0) ? 29 : 28;
        month_array[1] = leap;
        if(day <= 0 || month_array[month-1] < day)
        {
            str = "[Error] the data must be greater than 0 and less than "+std::to_string(month_array[month-1]);
            return  str;
        }
        unix_time = DateToUnix();
        std::cout << "unxi time : " << unix_time << endl;
        UnixToDate();
        return  str;
    }
};

#endif //PSI_EX2_NEW_DELETE_H
