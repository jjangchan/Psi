#include "Example/Ex1_Reference.h"
#include "Example/Ex2_New_Delete.h"
#include "Example/Ex3_Math.h"

using namespace std;


int main() {
    Point point1 = Point(0, 0);
    Point point2 = Point(3, 4);
    Point point3 = Point(3, 6);
    Geometry *geometry = new Geometry();
    geometry->AddPoint(point1);
    geometry->AddPoint(point2);
    geometry->AddPoint(point3);
    //geometry->PrintDistance();
    geometry->PrintNumMeets();
    return 0;
}
