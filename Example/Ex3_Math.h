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
        double sum_distance = 0;
        for(int i = 0; i<num_point; i++){
            int current_x = point_array[i]->GetX();
            int current_y = point_array[i]->GetY();
            CalculateDistance(current_x, current_y, i+1, sum_distance);
        }
        std::cout << "total distance : " << sum_distance << std::endl;
    }

    void PrintNumMeets(){
        std::queue<std::pair<Point*, Point*>> meets;
        std::vector<std::vector<Point*>> lines;
        InsertMeetsData(meets, lines);
        std::cout << "vector size : " << lines.size() << std::endl;
        while (!meets.empty()){
            Point* point1 = meets.front().first;
            Point* point2 = meets.front().second;
            meets.pop();
            std::cout << "(" << point1->GetX() << " , " << point1->GetY() << ") , (" << point2->GetX() << " , " << point2->GetY() << ")" << std::endl;
        }
    }

private:
    int CalculateDistance(const int x, const int y, const int index, double &sum_distance){
        if(index == num_point)
            return -1;
        int current_x = point_array[index]->GetX();
        int current_y = point_array[index]->GetY();
        double distance = std::sqrt(std::pow((x-current_x),2)+std::pow((y-current_y),2));
        std::cout << "distance : " << distance << std::endl;
        sum_distance += distance;
        return CalculateDistance(x, y, index+1, sum_distance);
    }

    void InsertMeetsData(std::queue<std::pair<Point*, Point*>> &meets, std::vector<std::vector<Point*>> &lines){

        int total_count = Combination(Combination(num_point, 2), 2);
        int vertex, intersection_count, sum_count = 0;

        for(int i=0; i<num_point-3; i++){
            for(int j = i+1; j < num_point; j++){
                std::pair<Point*, Point*> points = std::make_pair(point_array[i], point_array[j]);
                meets.push(points);
                std::vector<Point*> line;
                InsertLineData(line, i+1, j);
                lines.push_back(line);
            }
        }
        //sum_count =
    }

    int InsertLineData(std::vector<Point*> &line, const int index, const int end, const int count = 0){
        if(index == num_point)
            return count;
        if(index == end)
            return InsertLineData(line, index+1, end, count);
        line.push_back(point_array[index]);
        return  InsertLineData(line, index+1, end, count+1);
    }

    //intersection = (nC2)C2
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
