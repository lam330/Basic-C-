#include"point_class.h"
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;

//#define pi 3.14;

class Shape
{
public:

	Shape() {}
	virtual ~Shape() {}

	virtual double GetPerimeter() = 0;
	virtual double GetArea() = 0;
	virtual Shape *FromString(const string&) = 0;// get data from file
	virtual string ToString() = 0;// write data to file
	
};

//==============================================inheritance=========================
class Triangle :public Shape
{
private:
	Point point1;
	Point point2;
	Point point3;
public:
	Triangle() : point1{ 0,0 }, point2{ 0,0 }, point3{ 0,0 } {}
	Triangle(const Point& p1, const Point& p2, const Point& p3) : point1{ p1 }, point2{ p2 }, point3{ p3 } {}
	
	void SetPoint1(const Point&);
	void SetPoint2(const Point&);
	void SetPoint3(const Point&);

	Point GetPoint1() const;
	Point GetPoint2() const;
	Point GetPoint3() const;

	double GetPerimeter();
	double GetArea();
	Shape *FromString(const string&);
	string ToString();

};

class Rectangle :public Shape
{
private:
	Point center;
	int length;
	int witdh;
public:
	Rectangle() :center{ 0,0 }, length{ 0 }, witdh{ 0 }{}
	Rectangle(const Point& p, const int& iplength, const int& ipwitdh) :center{ p }, length{ iplength }, witdh{ ipwitdh }{}
	~Rectangle() {}

	void SetCenter(const Point&);
	void SetLength(const int&);
	void SetWitdh(const int&);

	Point GetCenter() const;
	int GetLength() const;
	int GetWitdh() const;

	double GetPerimeter();
	double GetArea();
	Shape* FromString(const string&);
	string ToString();
};

class Circle :public Shape
{
private:
	Point center;
	int radius;
public:
	Circle() :center{ 0,0 }, radius{ 0 }{}
	Circle(const Point& p, const int& ipRadius) :center{ p }, radius{ ipRadius }{}
	~Circle() {}

	void SetCenter(const Point&);
	void SetRadius(const int&);

	Point GetCenter() const;
	int GetRadius() const;

	double GetPerimeter();
	double GetArea();
	Shape* FromString(const string&);
	string ToString();
};

class Elipse :public Shape
{
private:
	Point center;
	int RadiusX;
	int RadiusY;
public:
	Elipse() :center{ 0,0 }, RadiusX{ 0 }, RadiusY{ 0 }{}
	Elipse(const Point& p, const int& ipRx, const int& ipRy) :center{ p }, RadiusX{ ipRx }, RadiusY{ ipRy }{}
	~Elipse(){}
	
	void SetCenter(const Point&);
	void SetRadiusX(const int&);
	void SetRadiusY(const int&);

	Point GetCenter() const;
	int GetRx() const;
	int GetRy() const;

	double GetPerimeter();
	double GetArea();
	Shape* FromString(const string&);
	string ToString();

};

//=============================================methods==================================

//-------------------------------------------Triangle-------------------------------------

void Triangle::SetPoint1(const Point& p1)
{
	point1 = p1;
}

void Triangle::SetPoint2(const Point& p2)
{
	point2 = p2;
}

void Triangle::SetPoint3(const Point& p3)
{
	point3 = p3;
}

Point Triangle::GetPoint1() const
{
	return point1;
}

Point Triangle::GetPoint2() const
{
	return point2;
}

Point Triangle::GetPoint3() const
{
	return point3;
}

double Triangle::GetPerimeter()
{
	double side1 = Distance(point1, point2); //Distance (friend func)2.2
	double side2 = Distance(point2, point3);//18.7
	double side3 = Distance(point3, point1);//20
	double pereimeter = side1 + side2 + side3;

	return pereimeter;
}

double Triangle::GetArea()
{
	double halfPeri = GetPerimeter() / 2;
	double area = sqrt(halfPeri * (halfPeri - Distance(point1, point2)) * 
	(halfPeri - Distance(point2, point3)) * (halfPeri - Distance(point3, point1)));

	return area;
}

Shape* Triangle::FromString(const string& s)// convert string to => data (output: pointer to tri obj (da dc set) )
{
	if (s[0] != '0')
	{
		return (this);//  default triangle
	}
	
	vector<int> elements{};// vector contains value = each element in line (file)
	int value;
	stringstream buff(s);// buff << s: take data from string to buffer of obj
	
	while (buff >> value)// >>: take data from buffer of obj to string || int value => cast
	{
		elements.push_back(value);
	}

	//elements[0] => kind => no need
	
	//new data from line (file)
	Point A{ elements[1], elements[2] };
	Point B{ elements[3], elements[4] };
	Point C{ elements[5], elements[6] };

	point1 = A;
	point2 = B;
	point3 = C;

	return (this);// new data (p1,p2,p3)
}

string Triangle::ToString()// prepare string (input) to add to file
{
	string s = "0 (" + to_string(point1.GetX()) + "," + to_string(point1.GetY()) + ")"// chu y, x,y
		+ " (" + to_string(point2.GetX()) + "," + to_string(point2.GetY()) + ")"//x1,y1
		+ " (" + to_string(point3.GetX()) + "," + to_string(point3.GetY()) + ")";//x2,y2
		
	return s;//s = 0 (x1,y1) (x2,y2) (x3,y3)
}

//-----------------------------------------------Rectangle-----------------------------

void Rectangle::SetCenter(const Point& ipCenter)
{
	center = ipCenter;
}

void Rectangle::SetLength(const int& ipLength)
{
	length = ipLength;
}

void Rectangle::SetWitdh(const int& ipWitdh)
{
	witdh = ipWitdh;
}

Point Rectangle::GetCenter() const
{
	return center;
}

int Rectangle::GetLength() const
{
	return length;
}

int Rectangle::GetWitdh() const
{
	return witdh;
}

double Rectangle::GetArea()
{
	double area = double(length) * witdh;
	return area;
}

double Rectangle::GetPerimeter()
{
	double peri = 2 * (double(length) + witdh);
	return peri;
}

Shape *Rectangle::FromString(const string& s)
{
	if (s[0] != '1')
	{
		return this;
	}

	vector<int> elements{};
	int value;
	stringstream read(s);// read << s: take data from string to buffer of obj

	while (read >> value)// >>: take data from buffer of obj to string || value lai la int=> cast
	{
		elements.push_back(value);
	}

	//elements[0] => kind => no need
	Point tempCenter{ elements[1],elements[2] };
	
	center = tempCenter;
	witdh = elements[3];
	length = elements[4];

	return (this);

}

string Rectangle::ToString()
{
	string s = "1 (" + to_string(center.GetX()) + "," + to_string(center.GetY())// x,y center
		+ ") " + to_string(witdh) + " " + to_string(length);// w,l

	return s;//s= 1 (x,y) witdh length
	
}

//------------------------------------Circle-------------------------------
void Circle::SetCenter(const Point& ipCenter)
{
	center = ipCenter;
}

void Circle::SetRadius(const int& ipR)
{
	radius = ipR;
}

Point Circle::GetCenter() const
{
	return center;
}

int Circle::GetRadius() const
{
	return radius;
}

double Circle::GetPerimeter()
{
	return (2 * 3.14 * radius);
}

double Circle::GetArea()
{
	return (3.14 * radius * radius);
}

Shape* Circle::FromString(const string& s)
{
	if (s[0] != '2')
	{
		return this;
	}

	vector<int> elements{};
	int value;
	stringstream read(s);// read << s: take data from string to buffer of obj

	while (read >> value)// >>: take data from buffer of obj to string || value lai la int=> cast
	{
		elements.push_back(value);
	}

	//elements[0] => kind => no need
	Point tempCenter{ elements[1],elements[2] };
	center = tempCenter;
	radius = elements[3];

	return (this);
}

string Circle::ToString()
{
	string s = "2 (" + to_string(center.GetX()) + "," + to_string(center.GetY())//x,y
		+ ") " + to_string(radius);

	return s; //s = (x,y) radius
}

//-----------------------------------------------------------Elip-----------------------------
void Elipse::SetCenter(const Point& ipCenter)
{
	center = ipCenter;
}

void Elipse::SetRadiusX(const int& ipRx)
{
	RadiusX = ipRx;
}
 
void Elipse::SetRadiusY(const int& ipRy)
{
	RadiusY = ipRy;
}

Point Elipse::GetCenter() const
{
	return center;
}

int Elipse::GetRx() const
{
	return RadiusX;
}

int Elipse::GetRy() const
{
	return RadiusY;
}

double Elipse::GetPerimeter()
{
	double peri = 2 * 3.14 * sqrt((pow(RadiusX, 2) + pow(RadiusY, 2) / 2));
	return peri;
}

double Elipse::GetArea()
{
	return (3.14 * RadiusX * RadiusY);
}

Shape* Elipse::FromString(const string& s)
{
	if (s[0] != '3')
	{
		return this;
	}

	vector<int> elements{};
	int value;
	stringstream read(s);// read << s: take data from string to buffer of obj

	while (read >> value)// >>: take data from buffer of obj to string || value: int=> cast
	{
		elements.push_back(value);
	}

	//elements[0] => kind => no need
	Point tempCenter{ elements[1],elements[2] };
	center = tempCenter;
	RadiusX = elements[3];
	RadiusY = elements[4];
	

	return (this);
}

string Elipse::ToString()
{
	string s = "3 (" + to_string(center.GetX()) + "," + to_string(center.GetY())//x,y
		+ ") " + to_string(RadiusX) + " " + to_string(RadiusY);//Rx, Ry

	return s;
}

//===================================================ShapeFactory=================================
class ShapeFactory// read and write data (file)
{
public:
	ShapeFactory() {}
	~ShapeFactory() {}

	Shape* CreateShape(const int& type, const string& s);//Shape pointer => create a shape with 1 type 
	vector<Shape*> ReadShapesFromFile(const string& fileName);//list consists shapes from file
	void SaveShapesToFile(const string& fileName, const vector<Shape*>&shapes);//write list(data) to file

};

Shape* ShapeFactory::CreateShape(const int& type, const string& s)// Get data(string) from file, get one new data package 
{
	Shape* create=nullptr;//k co NULL => warning
	if (type == 0)
	{
		create = new Triangle;// 
		create->FromString(s);//=> use override func=> get data package
		return create;// return 
	}
	else if (type == 1)
	{
		create = new Rectangle;
		create->FromString(s);
		return create;
	}
	else if (type == 2)
	{
		create = new Circle;
		create->FromString(s);
		return create;
	}
	else if (type == 3)
	{
		create = new Elipse;
		create->FromString(s);
		return create;
	}
	return create;
}

vector<Shape*> ShapeFactory::ReadShapesFromFile(const string& fileName)// Read data from file (list contains list data (From file)
{
	vector<Shape*> shapeList;// contain element = data package (CreateShape <= FromFile)
	
	fstream file;
	file.open(fileName, ios::in);//open file | mode: read only
	if (file.fail())
	{
		cout << "Failed to open!";
	}

	string data;

	getline(file, data);
	vector<string>save;// list save data packages
	
	while (getline(file, data))// (file>>data) read data from file => string data | read line by line 
	{
		save.push_back(data);//push data to list
	}

	//process string by string | process in save list
	for (int i = 0; i < save.size(); i++)
	{
		cout << save.at(i);
		string data = save.at(i);

		switch (data[0])// check first char
		{
		case '0':
		{
			cout << "Create a Triangle" << endl;
			shapeList.push_back(CreateShape(0, data));//CreateShape (get data from file)=> push data to shape list
			break;
		}
		case '1':
		{
			cout << "Create a Rectangle" << endl;
			shapeList.push_back(CreateShape(1, data));
			break;
		}
		case '2':
		{
			cout << "Create a Circle" << endl;
			shapeList.push_back(CreateShape(2, data));
			break;
		}
		case '3':
		{
			cout << "Create a Ellipse" << endl;
			shapeList.push_back(CreateShape(3, data));
			break;
		}
		default:
		{
			throw("Don't have a type to push data and creat shape!!!!!!!");
		}
		}
	}
	file.close();
	return shapeList;// List contains all shapes created from FromFile();

}

void ShapeFactory::SaveShapesToFile(const string& fileName, const vector<Shape*>& shapes)// write data to file
{
	fstream f;
	f.open("output.txt", ios::out | ios::trunc);//open file | mode out: to write | mode trunc: contents are splited before open file
	
	for (int i = 0; i < shapes.size(); i++)
	{
		f << "Input: " << shapes[i]->ToString() << endl;// write string from ToString() 
		f << "Output: " << "Area = " << shapes[i]->GetArea() << " and " << "Perimeter = " << shapes[i]->GetPerimeter() << endl;
	}
}

int main()
{
	try
	{
		ShapeFactory* fac = new ShapeFactory;
		//doc file=>doc line=> create shape from line=> push shape to shape list | shape list => write file
		
		string fileName = "input.txt";
		string fileLog = "output.txt";

		vector<Shape*> shapeList;
		shapeList = fac->ReadShapesFromFile(fileName);// have lists of shapes
		fac->SaveShapesToFile(fileLog, shapeList);// write shapes (above) to fileLog

		delete fac;
		return 0;
	}
	catch (const char* msg)
	{
		cerr << msg;
	}
	
}