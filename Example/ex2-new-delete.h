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

class Date{
private:
    int year_;
    int month_;
    int day_;
    //utc+0
    int unix_time;
    int month_array[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int sum_array[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

public:
    Date(){}
    ~Date(){}

    void SetDate(int year, int month, int Date)
    {
        std::string str = CheckNoiseData(year, month, Date);
        cout << str << endl;
    }

    void AddDay(int increase)
    {
        int current_day = sum_array[month_-1] + day_;
        current_day += increase;
        int cal_day = CalculateYear(current_day, sum_array[11]+31);
        int leap = (year_%4 == 0) ? 29 : 28;
        month_array[1] = leap;
        month_ = BinarySearchToValue(cal_day, 0, 11);
        day_ = cal_day- sum_array[month_-1];
        unix_time = DateToUnix();
        UnixToDate();
        PrintDate();
    }

    void AddMonth(int increase)
    {
        int month = month_+increase;
        int year_count = month/12;
        month %= 12;

        month_ = (month != 0) ? month : 12;
        year_ = (month == 0) ? year_+(--year_count) : year_+year_count;

        int leap = (year_%4 == 0) ? 29 : 28;
        month_array[1] = leap;
        unix_time = DateToUnix();
        UnixToDate();
    }

    void AddYear(int increase)
    {
        year_ += increase;
        int leap = (year_%4 == 0) ? 29 : 28;
        month_array[1] = leap;
        unix_time = DateToUnix();
        UnixToDate();
    }

private:
    int CalculateYear(const int day, const int total)
    {
        int cal = day/(sum_array[11]+32);
        if(cal == 0)
            return  day;
        year_ += 1;
        int leap = (year_%4 == 0) ? 29 : 28;
        month_array[1] = leap;
        InsertMonthData();
        return CalculateYear(day-total, sum_array[11]+31);
    }

    int CalculateLeap(const int year_distance)
    {
        int leap = (year_distance+2)/4;
        int cal_leap = ((year_distance+2)%4 == 0 && month_ < 3) ? --leap : leap;
        return cal_leap;
    }

    void InsertMonthData()
    {
        int sum = 0;
        sum_array[0] = 0;
        for(int i = 1; i < 12; i++)
        {
            sum += month_array[i-1];
            sum_array[i] = sum;
        }
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
        InsertMonthData();
        int year_distance = year_-INITYEAR;
        double unix = unix_time- (CalculateLeap(year_distance)*DAY);


        double year = unix/(double)YEAR;
        year_ = INITYEAR+(int)year;

        double day = (year-(int)year) * 365;
        day = ((year_distance+2)%4 == 0 && 2 < month_ ) ? day+2.0 : day+1.0;
        day += 0.5 - (day<0);

        month_ = BinarySearchToValue((int)day, 0, 11);
        day_ = day- sum_array[month_-1];
    }

    double CalculateDay(const int* array, const int index, const int day)
    {
        if(index == 3)
        {
            return (double)day/365.0;
        }
        return CalculateDay(array, index+1, day/array[index]);
    }

    int BinarySearchToValue(const int price, const int low, const int high)
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
        std::string str = "[Info] Date Setup Completed";
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
            str = "[Error] the Date must be greater than 0 and less than "+std::to_string(month_array[month-1]);
            return  str;
        }

        unix_time = DateToUnix();
        UnixToDate();
        return  str;
    }

    void PrintDate()
    {
        cout << "unix time : " << unix_time << endl;
        cout << "year : " << year_<< endl;
        cout << "month : " << month_ << endl;
        cout << "day : " << day_ << endl;
    }
};

#endif //PSI_EX2_NEW_DELETE_H
