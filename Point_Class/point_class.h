#pragma once
#include<iostream>
using namespace std;

class Point
{
private:
	int x;
	int y;
public:
	Point();
	Point(const int&, const int& );
	Point(const Point& obj);

	int GetX() const;
	void SetX(const int& );
	int GetY() const;
	void SetY(const int&);

	friend std::ostream& operator <<(std::ostream&, const Point&);

	Point& operator=(const Point&);
	Point& operator+=(const Point&);
	Point& operator-=(const Point&);
	Point& operator*=(const int&);
	Point& operator/=(const int&);

	friend double Distance(const Point&, const Point&);
	friend double DotProduct(const Point&, const Point&);

	
	
};
// 2 ngoi
Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);
Point operator*(const Point&, const int&);
Point operator/(const Point&, const int&);
