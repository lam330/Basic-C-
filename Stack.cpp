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
		//cout << "--------------" << endl;
		cout << "Account: " << account << endl;
		cout << "Name: " << name << endl;
		cout << "ID: " << id << endl;
		cout << "---------------" << endl;

	}


};

template<class Type>// class

class Stack
{
private:

	int number;
	Type* arr;
public:
	Stack()
	{
		number = 0;
		arr = new Type[number];
	}
	void PrintList()
	{
		cout << "Tale of SinhVien:\n";
		cout << "STT " << setw(17) << "Account" << setw(20) << "Name" << setw(19) << "ID" << endl;
		for (int index = 0; index < number; index++)
		{
			cout << index << setw(20) << arr[index].account << setw(20) << arr[index].name
				<< setw(20) << arr[index].id << endl;
		}
	}

	void PrintNumberList()
	{
		cout << "\n List of numbers: ";
		for (int i = 0; i < number; i++)
		{
			cout << arr[i] << " ";
		}
	}
	

	void Push_data(const Type& obj)
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

	
	void Pop_data()//remove last ele
	{
		if (number>1)
		{
			int newNumber = number - 1;
			Type* tempList = new Type[newNumber];
			for (int i = 0; i < newNumber; i++)
			{
				tempList[i] = arr[i];
			}

			arr = tempList;
			number--;
		}
		else
		{
			throw("List is empty=> can't remove");
		}
	}

	Student Peek_data()// get last ele
	{
		if (number <= 10)
		{
			return arr[number-1];
		}
		throw("Queue is empty => can't get information ");
	}

};

int main()
{
	Stack <Student> list;

	try
	{
		Student a("Lam1", "Lam", "01");
		list.Push_data(a);
		Student b("Phu2", "Phu", "02");
		list.Push_data(b);
		Student c("Trang3", "Trang", "03");
		list.Push_data(c);
		Student d("Trieu4", "Trieu", "04");
		list.Push_data(d);
		Student e("Duyet5", "Duyet", "05");
		list.Push_data(e);
		Student f("Dau6", "Dau", "06");
		list.Push_data(f);
		Student g("Nhat7", "Nhat", "07");
		list.Push_data(g);
		Student h("Sang8", "Sang", "08");
		list.Push_data(h);
		Student j("Vu9", "Vu", "09");
		list.Push_data(j);
		Student k("Nguyen10", "Nguyen", "10");
		list.Push_data(k);
		list.PrintList();

		Sleep(3000);
		system("cls");

		//removed 3 
		cout << "Students are removed" << endl;
		for (int i = 0; i < 3; i++)
		{
			Student person;
			person = list.Peek_data();
			person.DisplayOne();
			list.Pop_data();
		}
		cout << "\nList after removing 3 students";
		list.PrintList();
		Sleep(3000);
		system("cls");

		


	}
	catch (const char* msg)
	{
		cerr << msg;
	}

	Stack<int> integerList;
	integerList.Push_data(1);
	integerList.Push_data(2);
	integerList.Push_data(3);
	cout << "Integer list: " << endl;
	integerList.PrintNumberList();
	Sleep(3000);
	system("cls");

	Stack<double> doubleList;
	doubleList.Push_data(1.5);
	doubleList.Push_data(2.55);
	doubleList.Push_data(6.99);
	cout << "Double list: " << endl;
	doubleList.PrintNumberList();



	return 0;
}


