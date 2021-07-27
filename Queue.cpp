// Queue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<iomanip>
#include<Windows.h>

using namespace std;

struct Student
{
	string account;
	string name;
	string id;

	Student()
	{
		account = "empty";
		name = "empty";
		id = "empty";
	}
	Student(const string& ipAcc, const string& ipName, const string& ipId)
		: account{ ipAcc }, name{ ipName }, id{ ipId }{}

	void DisplayOne()
	{
		cout << "==============" << endl;
		cout << "Account: " << account << endl;
		cout << "Name: " << name << endl;
		cout << "ID: " << id << endl;
		cout << "==============" << endl;

	}


};

template<class Type>// class

class Queue
{
private:

	int number;
	Type* arr;
public:
	Queue()
	{
		number = 0;
		arr = new Type[number];
	}
	void PrintList()// Student
	{
		cout << "Tale of SinhVien:\n";
		cout << "STT " << setw(17) << "Account" << setw(20) << "Name" << setw(19) << "ID" << endl;
		for (int index = 0; index < number; index++)
		{
			cout << index << setw(20) << arr[index].account << setw(20) << arr[index].name
				<< setw(20) << arr[index].id << endl;
		}
	}

	void PrintNumberList()// int, double
	{
		cout << "\n List of numbers: ";
		for (int i = 0; i < number; i++)
		{
			cout << arr[i] << " ";
		}
	}
	

	void Enqueue(const Type& obj)
	{
		if (number < 15)
		{
			Type* tempList = new Type[number + 1];
			for (int i = 0; i < number; i++)
			{
				tempList[i] = arr[i];
			}
			tempList[number] = obj;
			number++;
			arr = tempList;
			
		}
		else
		{
			throw("Queue is full=> can't add data");
		}

	}

	
	void Dequeue()//remove first ele
	{
		if (number > 0)
		{
			int newNumber = number - 1;
			Type* tempList = new Type[newNumber];
			int j = 0;
			for (int i = 1; i < number; i++)
			{
				tempList[j] = arr[i];
				j++;
			}

			arr = tempList;
			number--;

		}
	}

	Student Peek()// get first ele
	{
		if (number < 10)
		{
			return arr[0];
		}
		throw("Queue is empty => can't get information ");
	}

};

int main()
{
	Queue <Student> list;

	try
	{
		Student a("Lam1", "Lam", "01");
		list.Enqueue(a);
		Student b("Phu2", "Phu", "02");
		list.Enqueue(b);
		Student c("Trang3", "Trang", "03");
		list.Enqueue(c);
		Student d("Trieu4", "Trieu", "04");
		list.Enqueue(d);
		Student e("Duyet5", "Duyet", "05");
		list.Enqueue(e);
		Student f("Dau6", "Dau", "06");
		list.Enqueue(f);
		Student g("Nhat7", "Nhat", "07");
		list.Enqueue(g);
		Student h("Sang8", "Sang", "08");
		list.Enqueue(h);
		Student j("Vu9", "Vu", "09");
		list.Enqueue(j);
		Student k("Nguyen10", "Nguyen", "10");
		list.Enqueue(k);
		list.PrintList();

		Sleep(3000);
		system("cls");

		//removed 5 
		list.Dequeue();
		list.Dequeue();
		list.Dequeue();
		list.Dequeue();
		list.Dequeue();
		cout << "\nList after removing 5 students";
		list.PrintList();
		Sleep(3000);
		system("cls");

		//add 10
		Student l("Trinh11", "Trinh", "11");
		list.Enqueue(l);
		Student m("Hang12", "Hang", "12");
		list.Enqueue(m);
		Student n("Tu13", "Tu", "13");
		list.Enqueue(n);
		Student o("Doi14", "Doi", "14");
		list.Enqueue(o);
		Student p("Anh15", "Anh", "15");
		list.Enqueue(p);
		Student q("Viet16", "Viet", "16");
		list.Enqueue(q);
		Student r("Tan17", "Tan", "17");
		list.Enqueue(q);
		Student s("Quang18", "Quang", "18");
		list.Enqueue(s);
		Student t("Sang19", "Sang", "19");
		list.Enqueue(t);
		Student u("Quynh20", "Quynh", "20");

		cout << "\n List after add 10 students";
		list.PrintList();
		Sleep(3000);
		system("cls");


	}
	catch (const char* msg)
	{
		cerr << msg;
	}

	Queue<int> integerList;
	integerList.Enqueue(1);
	integerList.Enqueue(2);
	integerList.Enqueue(3);
	cout << "Integer list: " << endl;
	integerList.PrintNumberList();
	Sleep(3000);
	system("cls");

	Queue<double> doubleList;
	doubleList.Enqueue(1.5);
	doubleList.Enqueue(2.55);
	doubleList.Enqueue(6.99);
	cout << "Double list: " << endl;
	doubleList.PrintNumberList();



	return 0;
}


