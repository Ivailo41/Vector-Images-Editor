#ifndef SVG_PROJECT_POINT_H
#define SVG_PROJECT_POINT_H
#include <iostream>
#include <cmath>

struct Point
        {
            double x;
            double y;

            Point(double x, double y) : x(x), y(y) {}
            Point() : x(0), y(0) {}

            friend std::ostream& operator<<(std::ostream& out, const Point& point)
            {
                out << "(" << point.x << ", " << point.y << ")";
                return out;
            }

            bool isInside(Point topLeft, Point bottomRight) const
            {
                return x >= topLeft.x && x <= bottomRight.x && y <= topLeft.y && y >= bottomRight.y;
            }

            bool operator==(const Point& other) const
            {
                return x == other.x && y == other.y;
            }

            bool operator<=(const Point& other) const
            {
                return x <= other.x && y <= other.y;
            }

            bool operator>=(const Point& other) const
            {
                return x >= other.x && y >= other.y;
            }

            bool operator<(const Point& other) const
            {
                return x < other.x && y < other.y;
            }

            bool operator>(const Point& other) const
            {
                return x > other.x && y > other.y;
            }

            Point& operator*=(const Point& other)
            {
                x *= other.x;
                y *= other.y;
                return *this;
            }

            Point operator*(const Point& other) const
            {
                Point result(*this);
                result *= other;
                return result;
            }

            Point& operator*=(double number)
            {
                x *= number;
                y *= number;
                return *this;
            }

            Point operator*(double number) const
            {
                Point result(*this);
                result *= number;
                return result;
            }

            Point& operator+=(const Point& other)
            {
                x += other.x;
                y += other.y;
                return *this;
            }

            Point operator+(const Point& other) const
            {
                Point result(*this);
                result += other;
                return result;
            }

            Point& operator-=(const Point& other)
            {
                x -= other.x;
                y -= other.y;
                return *this;
            }

            Point operator-(const Point& other) const
            {
                Point result(*this);
                result -= other;
                return result;
            }

            static double getLength(const Point& point1, const Point& point2)
            {
                return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
            }

            static double getAngleBetweenPoints(const Point& center, const Point& first, const Point& second)
            {
                double centerToFirst = getLength(center, first);
                double centerToSecond = getLength(center, second);
                double firstToSecond = getLength(first, second);

                double result = acos((pow(centerToFirst, 2) + pow(centerToSecond, 2) - pow(firstToSecond, 2)) / (2 * centerToFirst * centerToSecond));
                return result * 180/3.14159;
            }
        };
#endif //SVG_PROJECT_POINT_H
