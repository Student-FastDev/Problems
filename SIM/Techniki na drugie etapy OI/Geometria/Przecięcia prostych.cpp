#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double detFunction(double A, double B, double C, double D) {
    return A * D - B * C;
}

bool intersection(Point p1, Point p2, Point p3, Point p4, Point &intersect) {
    double d1 = detFunction(p1.x, p1.y, p2.x, p2.y);
    double d2 = detFunction(p3.x, p3.y, p4.x, p4.y);
    double d3 = detFunction(p1.x - p2.x, p1.y - p2.y, p3.x - p4.x, p3.y - p4.y);

    if (d3 == 0) {
        return false;
    }
    
    double dx = detFunction(d1, p1.x - p2.x, d2, p3.x - p4.x);
    double dy = detFunction(d1, p1.y - p2.y, d2, p3.y - p4.y);

    intersect.x = dx / d3;
    intersect.y = dy / d3;
    
    return true;
}

bool onSegment(Point p, Point p1, Point p2) {
    return min(p1.x, p2.x) <= p.x && p.x <= max(p1.x, p2.x) &&
           min(p1.y, p2.y) <= p.y && p.y <= max(p1.y, p2.y);
}

int main() {
    int N;
    cin >> N;

    while (N--) {
        Point p1, p2, p3, p4;
        cin >> p1.x >> p1.y >> p2.x >> p2.y;
        cin >> p3.x >> p3.y >> p4.x >> p4.y;
        
        Point intersect;
        
        if (intersection(p1, p2, p3, p4, intersect)) {
            if (onSegment(intersect, p1, p2) && onSegment(intersect, p3, p4)) {
                cout << fixed << setprecision(2) << intersect.x << " " << intersect.y << endl;
            } else {
                cout << "NIE" << endl;
            }
        } else {
            cout << "NIE" << endl;
        }
    }

    return 0;
}
