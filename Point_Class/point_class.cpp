// point_class.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include"point_class.h"

#include <iostream>
#include<math.h>
using namespace std;

//====================== Constructors======================
Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(const int& inX, const int& inY)
{
	x = inX;
	y = inY;
}

Point::Point(const Point& obj)
{
	x = obj.x;
	y = obj.y;
}
//========================Methods===============================

int Point::GetX() const
{
	return x;
}

int Point::GetY() const
{
	return y;
}

void Point::SetX(const int& inX)
{
	x = inX;
}

void Point::SetY(const int& inY)
{
	y = inY;
}

//=================================overloading operator===================
std::ostream& operator <<(std::ostream& os, const Point& obj)
{
	
	os << "(" << obj.x << ", " << obj.y << ")";
	return os;
}

Point& Point::operator=(const Point& obj)
{
	x = obj.x;
	y = obj.y;
	return *this;
}
Point& Point::operator+=(const Point& obj)// phuc vu cho toan hang ben trai 
{
	x += obj.x;//
	y += obj.y;//
	return *this;// obj.func();=obj+
}

Point& Point::operator-=(const Point& obj)
{
	x -= obj.x;
	y -= obj.y;
	return *this;
}

Point& Point::operator*=(const int& number)
{
	x *= number;
	y *= number;
	return *this;
}

Point& Point::operator/=(const int& number)
{
	x /= number;
	y /= number;
	return *this;
}

Point operator+(const Point& obj1, const Point& obj2)// a toan hang trai, b toan hang phai
{
	Point temp(obj1);
	return (temp += obj2); //temp = temp + obj2 ( khong dc )
	//c=a+b=temp;
}




Point operator-(const Point& obj1, const Point& obj2)
{
	Point temp(obj1);
	return (temp -= obj2);
}


Point operator*(const Point& obj1, const int& number)
{
	Point temp(obj1);
	temp *= number;
	return temp;
}


Point operator/(const Point& obj1, const int& number)
{
	Point temp(obj1);
	return (temp /= number);
}

//=======================================Distance, dotProduct======================
double Distance(const Point& obj1, const Point& obj2)
{
	double distance = sqrt(pow(obj2.x - obj1.x, 2) + pow(obj2.y - obj1.y,2));
	return distance;
}

double DotProduct(const Point& obj1, const Point& obj2)
{
	double dotProduct = (double (obj1.x) * obj1.y) + (double (obj2.x) * obj2.y);
	return dotProduct;
}

