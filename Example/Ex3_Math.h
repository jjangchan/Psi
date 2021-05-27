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

    // 꼭짓점은 교점 이므로, 꼭짓점이 아닌 좌표만 검증 하면 된다.
    void PrintNumMeets(){
        int total_count = combination(combination(num_point, 2), 2);
        int vertex = 0;
        int intersection_count = 0;

        for(int i=0; i<num_point-3; i++){
            for(int j = i+1; j < num_point; j++){
                std::pair<Point*, Point*> points = std::make_pair(point_array[i], point_array[j]);
                std::vector<Point*> line;
                InsertLineData(line, i+1, j);
                intersection_count += SearchInterSection(points, line, vertex);
            }
        }
        vertex = total_count - vertex;
        int sum_count = vertex + intersection_count;
        std::cout << "\nintersection line = " << sum_count << std::endl;
    }

private:
    int SearchInterSection(const std::pair<Point*, Point*> left_points, const std::vector<Point*> right_points, int &vertex){
        int intersection = 0;
        for(std::vector<int>::size_type i = 0; i < right_points.size(); i++){
            for(int j = i+1; j < right_points.size(); j++){
                std::cout << "==========================================" << std::endl;
                std::cout << "[left] (" << left_points.first->GetX() << "," << left_points.first->GetY() << ") , (" << left_points.second->GetX() << "," << left_points.second->GetY() << ")" << std::endl;
                std::cout << "[right] (" << right_points[i]->GetX() << "," << right_points[i]->GetY() << ") , (" << right_points[j]->GetX() << "," << right_points[j]->GetY() << ")" << std::endl;
                if(GetInterSectionPoint(left_points.first, left_points.second, right_points[i], right_points[j]))
                    std::cout << "InterSection" << std::endl;
                intersection += (GetInterSectionPoint(left_points.first, left_points.second, right_points[i], right_points[j])) ? 1 : 0;
                vertex += 1;
            }
        }
        return intersection;
    }

    // 직선의 내분점 공식 활용
    bool GetInterSectionPoint(const Point* p1,
                              const Point* p2,
                              const Point* p3,
                              const Point* p4){
        double t,s;
        double denominator = (p4->GetY()-p3->GetY())*(p2->GetX()-p1->GetX()) - (p4->GetX()-p3->GetX())*(p2->GetY()-p1->GetY());
        if(denominator == 0) return false;
        double t_numerator = (p4->GetX()-p3->GetX())*(p1->GetY()-p3->GetY()) - (p4->GetY()-p3->GetY())*(p1->GetX()-p3->GetX());
        double s_numerator = (p2->GetX()-p1->GetX())*(p1->GetY()-p3->GetY()) - (p2->GetY()-p1->GetY())*(p1->GetX()-p3->GetX());

        if(t_numerator == 0 && s_numerator == 0) return false;

        t = t_numerator/denominator;
        s = s_numerator/denominator;
        return !(t<0.0 || t > 1.0 || s < 0.0 || s > 1.0);
    }



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

    int InsertLineData(std::vector<Point*> &line, const int index, const int end, const int count = 0){
        if(index == num_point)
            return count;
        if(index == end)
            return InsertLineData(line, index+1, end, count);
        line.push_back(point_array[index]);
        return  InsertLineData(line, index+1, end, count+1);
    }

    //intersection = (nC2)C2
    int combination(int n, int r)
    {
        if(n == r || r == 0)
            return 1;
        else
            return combination(n - 1, r - 1) + combination(n - 1, r);
    }
};

#endif //EX2_NEW_DELETE_H_EX3_MATH_H
