#pragma once

class Point {
    int x;
    int y;

public:
    Point(int xVal, int yVal) : x(xVal), y(yVal) {}
    Point() : x(0), y(0) {}
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int xVal) { x = xVal; }
    void setY(int yVal) { y = yVal; }

    // Declaration of the equality operator as a member function
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
};
