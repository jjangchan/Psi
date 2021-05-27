#include "Example/Ex3_Math.h"

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

int main() {
    //Point *point1 = new Point(0, 0);
    //Point *point2 = new Point(3, 4);
    //Point *point3 = new Point(0, 1);
    //Point *point4 = new Point(3, 1);
    //std::cout << GetInterSectionPoint(point1, point2, point4, point3);

    Point point1 = Point(0, 0);
    Point point2 = Point(3, 4);
    Point point3 = Point(0, 1);
    Point point4 = Point(3, 1);
    Point point5 = Point(15, 5);
    Geometry *geometry = new Geometry();
    geometry->AddPoint(point1);
    geometry->AddPoint(point2);
    geometry->AddPoint(point3);
    geometry->AddPoint(point4);
    geometry->AddPoint(point5);
    //geometry->PrintDistance();
    geometry->PrintNumMeets();

    return 0;
}
