#include"point_class.h"
#include<iostream>
using namespace std;

int main()
{
	int x0, y0, x1, y1;
	cout << "Enter coordinate of point 1"<<endl;
	cout << "x0: ";
	cin >> x0;
	cout << "y0: ";
	cin >> y0;
	
	Point p1(x0, y0);
	cout << "Point 1: " << p1;

	cout << "\nEnter coordinate of point 2" << endl;
	cout << "x1: ";
	cin >> x1;
	cout << "y1: ";
	cin >> y1;

	Point p2(x1, y1);
	cout << "Point 2: " << p2;

	//calculate
	cout << "Distance point 1 and point 2: " << Distance(p1, p2)<<endl;
	cout << "Dot Product vecto p1 and vecto p2 :" << DotProduct(p1, p2)<<endl;

	Point p3 = p1 + p2;
	cout << "Coordinate of vecto p3: " << p3<<endl;
	Point p4 = p3 - p2;
	cout << "Coordinate of vecto p4: " << p4<<endl;

	int number;
	cout << "Enternumber"<<endl;
	cout << "number: ";
	cin >> number;
	
	p1 = p1 * number;
	cout << "Vecto p1 after multiplating: " << p1<<endl;
	
	p2 = p2 / number;
	cout << "Vecto p2 after divising: " << p2;





}