//
// Created by jjangchan 2021-05-12.
//

#ifndef EX2_NEW_DELETE_H_EX3_MATH_H
#define EX2_NEW_DELETE_H_EX3_MATH_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>

class Point{
public:
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    int GetX() const {return  x;}
    int GetY() const {return  y;}

private:
    int x, y;
};

class Geometry{
private:
    int num_point;
    Point* point_array[100];
public:
    Geometry(){
        num_point = 0;
    }

    ~Geometry(){
        for(int i=0; i<num_point; i++){
            delete point_array[i];
            point_array[i] = nullptr;
        }
    }

    void AddPoint(const Point &point){
        if(num_point == 100){
            std::cout << "Over Limit Instance....." << std::endl;
            return;
        }
        point_array[num_point++] = new Point(point.GetX(), point.GetY());
    }

    void PrintDistance(){
        if(num_point <= 1){
            std::cout << "please add point" << std::endl;
            return;
        }
        int current_x = point_array[0]->GetX();
        int current_y = point_array[0]->GetY();
        double sum_distance = 0;
        for(int i = 1; i<num_point; i++){
            CalculateDistance(current_x, current_y, i, sum_distance);
            current_x = point_array[i]->GetX();
            current_y = point_array[i]->GetY();
        }
        cout << "total distance : " << sum_distance << endl;
    }

    void PrintNumMeets(){
        std::queue<pair<Point*, Point*>> meets;
        std::vector<std::vector<Point*>> lines;
        InsertMeetsData(meets, lines);
        cout << "vector size : " << lines.size() << endl;
        while (!meets.empty()){
            Point* point1 = meets.front().first;
            Point* point2 = meets.front().second;
            meets.pop();
            cout << "[Point1] x : " << point1->GetX() << " y : " << point1->GetY() << endl;
            cout << "[Point2] x : " << point2->GetX() << " y : " << point2->GetY() << endl;
        }
    }

private:
    int CalculateDistance(const int x, const int y, const int index, double &sum_distance){
        if(index == num_point)
            return -1;
        int current_x = point_array[index]->GetX();
        int current_y = point_array[index]->GetY();
        double distance = std::sqrt(std::pow((x-current_x),2)+std::pow((y-current_y),2));
        std::cout << "distance : " << distance << endl;
        sum_distance += distance;
        return CalculateDistance(x, y, index+1, sum_distance);
    }

    void InsertMeetsData(std::queue<pair<Point*, Point*>> &meets, std::vector<std::vector<Point*>> &lines){
        for(int i=1; i<num_point; i++){
            pair<Point*, Point*> points = make_pair(point_array[0], point_array[i]);
            meets.push(points);
            std::vector<Point*> line;
            InsertLineData(line, 1, i);
            lines.push_back(line);
        }

    }

    int InsertLineData(std::vector<Point*> &line, const int index, const int end){
        if(index == num_point)
            return -1;
        if(index == end)
            return InsertLineData(line, index+1, end);
        line.push_back(point_array[index]);
        return  InsertLineData(line, index+1, end);
    }


    //vertex is the intersection = nC2
    int Factorial(int value, int num){
        if(num <= 1) return  value;
        return Factorial(value*(--num), num);
    }

    int CalculateN(const int n, const int r, const int value = 1){
        if(0 >= r) return  value;
        return CalculateN(n-1, r-1, value*n);
    }

    int Combination(int n, int r){
        int rum = r;
        return CalculateN(n, r)/ Factorial(rum, rum);
    }
};

#endif //EX2_NEW_DELETE_H_EX3_MATH_H
