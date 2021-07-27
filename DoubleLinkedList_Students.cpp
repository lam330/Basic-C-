// DoubleLinkedList_Students.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<sstream>
using namespace std;

struct Student
{
	string account;
	string name;
	string key;

	Student() {}
	Student(string ipAcc, string ipName, string ipKey) : account(ipAcc), name(ipName), key(ipKey) {}

	//check input data
	bool CheckAcc(const string& ipAcc)
	{
		for (unsigned int i = 0; i < ipAcc.length(); ++i)
		{
			if (!((ipAcc[i] >= 65 && ipAcc[i] <= 90) || (ipAcc[i] >= 97 && ipAcc[i] <= 122) || (ipAcc[i] >= 48 && ipAcc[i] <= 57)))
			{
				return false;
			}
		}
		return true;
	}
	bool CheckName(const string& ipName)
	{
		for (unsigned int i = 0; i < ipName.length(); ++i)
		{
			if (!((ipName[i] >= 65 && ipName[i] <= 90) || (ipName[i] >= 97 && ipName[i] <= 122) || ipName[i] == 32))
			{
				return false;
			}
		}
		return true;
	}
	friend bool CheckKey(const string& ipKey)
	{
		{
			for (unsigned int i = 0; i < ipKey.length(); ++i)
			{
				if (!(ipKey[i] >= 48 && ipKey[i] <= 57))//! 0->9
				{
					return false;
				}
			}
			return true;
		}
	}


	void EnterOne()
	{
		cout << "Enter info:" << endl;
	retry:
		cout << "Account: ";

		getline(cin, account);
		getline(cin, account);
		fflush(stdin);

		if (!CheckAcc(account))
		{
			cout << "Account it no allowed for SPECIAL CHARACTERS" << endl;
			cout << "Enter again" << endl;
			goto retry;
		}
	retry1:
		cout << "Name: ";

		getline(cin, name);
		fflush(stdin);

		if (!CheckName(name))
		{
			cout << "Name is not allowed for SPECIAL CHARACTERS or NUMBER!" << endl;
			cout << "Enter again" << endl;
			goto retry1;
		}
	retry2:
		cout << "ID: ";

		getline(cin, key);
		fflush(stdin);

		if (!CheckKey(key))
		{
			cout << "ID must be A NUMBER" << endl;
			cout << "Enter again" << endl;
			goto retry2;
		}

	}



	void DisplayOne()
	{
		cout << "Information" << endl;

		cout << "Account: " << account << endl;
		cout << "Name: " << name << endl;
		cout << "ID: " << key << endl;
	}

	Student& operator=(const Student& ipPerson)
	{
		if (this == &ipPerson)
		{
			return *this;
		}


		account = ipPerson.account;
		name = ipPerson.name;
		key = ipPerson.key;
		return *this;
	}

	friend std::ostream& operator << (std::ostream& out, const Student& ipPerson)
	{
		out << ipPerson.account << std::endl;
		out << ipPerson.name << std::endl;
		out << ipPerson.key << std::endl;
		return out;
	}

	bool operator>(const Student& obj)
	{
		//convert string to int
		stringstream buff1(key);
		int lValue = 0;
		buff1 >> lValue;

		stringstream buff2(obj.key);
		int rValue = 0;
		buff2 >> rValue;

		//compare
		if (lValue > rValue)
		{
			return true;
		}
		return false;
	}

	bool operator<(const Student& obj)
	{
		//convert string to int
		stringstream buff1(key);
		int lValue = 0;
		buff1 >> lValue;

		stringstream buff2(obj.key);
		int rValue = 0;
		buff2 >> rValue;

		//compare
		if (lValue < rValue)
		{
			return true;
		}
		return false;
	}

};

bool CheckKey(const string& ipKey)
{
	{
		for (unsigned int i = 0; i < ipKey.length(); ++i)
		{
			if (!(ipKey[i] >= 48 && ipKey[i] <= 57))//! 0->9
			{
				return false;
			}

		}
		return true;
	}
}

struct Node //node structure
{
	Student data;
	Node* next;
	Node* prev;

	Node()
	{

		next = nullptr;
		prev = nullptr;
	}



	/*  friend std::ostream& operator << (std::ostream& out, const Node* ptr)
	  {
		  out << ptr->data.account << std::endl;
		  out << ptr->data.name << std::endl;
		  out << ptr->data.key << std::endl;
		  return out;
	  }*/
	  /*~Node()
	  {
		  if (prev != nullptr)
		  {
			  delete prev;
			  prev = nullptr;
		  }

		  if (next != nullptr)
		  {
			  delete next;
			  next = nullptr;
		  }
	  }*/
};



Node* head, * tail; // head and tail of DLL

//Creates a new Node and returns pointer to it.
struct Node* CreateNewNode(const Student& ipPerson)
{
	//Node* newNode = (Node*)malloc(sizeof(Node));
	Node* newNode = new Node;
	newNode->data = ipPerson;// operator = 
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;

}

//Inserts a Node at head of doubly linked list
void InsertAtHead(const Student& ipPerson)
{
	Node* newNode = CreateNewNode(ipPerson);
	if (head == NULL)//empty list => head point to first student (newNode) 
	{
		head = newNode;
		tail = newNode;
		return;//? => khoi else?
	}
	//make newNode => head 
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(const Student& ipPerson)
{
	struct Node* newNode = CreateNewNode(ipPerson);
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
		return;
	}
	//make newNode => tail
	tail->next = newNode;
	newNode->prev = tail;
	tail = newNode;


}


void DeleteAtHead()
{
	if (head == NULL)
	{
		return;
	}
	head = head->next;// new head = next node
	head->prev = NULL;//disconnect with old head
}

//Inserts a Node at tail of Doubly linked list
void DeleteAtTail()
{
	if (head == NULL)
	{
		return;
	}
	tail = tail->prev;// new tail = pre node
	tail->next = NULL;// disconnect with old tail
}

void Remove(Node*& head, const string& ipKey)// cover 3 cases
{

	if (head != nullptr)
	{
		Node* tempNode = new Node;
		Node* current = head;

		while (current != nullptr)//go to the end DLL
		{
			// 3 cases: first, mid, last
			if (current->data.key == ipKey)
			{
				if (current->prev == nullptr)//first    <=[] [] []=>
				{

					head = current->next;
					head->prev = nullptr;
					delete current;
					current = nullptr;

					return;
				}
				else if (current->next == nullptr)//last
				{
					tail = current->prev;
					tail->next = nullptr;
					delete current;
					current = nullptr;

					return;
				}
				else// mid  
				{
					tempNode->next = current->next;
					current->next->prev = tempNode;
					current->next = nullptr;
					current->prev = nullptr;
					delete current;

					return;
				}

				return;
			}
			tempNode = current;
			current = current->next;
		}
		tempNode = nullptr;
		current = nullptr;
		cout << "Not Found!";

	}
	else
	{
		cout << "Empty list";
	}

}

//Find Student
void FindByKey(Node* head, const string& ipKey)
{
	int position = 0;
	int count = 0;
	if (head != nullptr)
	{

		Node* current = head;
		while (current != nullptr)
		{
			if (current->data.key == ipKey)
			{
				cout << "Student has " << ipKey << " is located in pos: " << position + 1 << endl;
				cout << current->data << endl;
				//delete current;
				current = nullptr;
				count++;

				return;
			}

			current = current->next;
			position++;
		}
		if (count == 0)
		{
			cout << ipKey << ": Not found!" << endl;
		}
	}
	else
	{
		cout << "Empty list!" << endl;
	}
}

void FindByName(Node* head, const string& ipName)
{
	int position = 0;
	int count = 0;
	if (head != nullptr)
	{

		Node* current = head;
		while (current != nullptr)
		{
			if (current->data.name == ipName)
			{
				cout << "Student has " << ipName << " is located in pos: " << position + 1 << endl;
				cout << current->data << endl;
				//delete current;
				current = nullptr;
				count++;

				return;
			}

			current = current->next;
			position++;
		}
		if (count == 0)
		{
			cout << ipName << ": Not found!" << endl;
		}
	}
	else
	{
		cout << "Empty list!" << endl;
	}
}
//Prints all the elements in linked list in forward traversal order
void Print()
{
	struct Node* temp = head;
	if (temp == NULL)
	{
		return; // empty list, exit
	}
	cout << "Tale of Students:\n";
	cout << "STT " << setw(20) << "Account" << setw(20) << "Name " << setw(20) << "Key " << endl;
	int index = 0;
	while (temp != NULL)
	{
		index++;
		cout << index << setw(22) << temp->data.account << setw(20) << temp->data.name
			<< setw(20) << temp->data.key << endl;
		temp = temp->next;
	}
	printf("\n");
}

//Prints all elements in linked list in reverse traversal order.
void ReversePrint()
{
	struct Node* temp = tail;
	if (temp == NULL) return; // empty list, exit
	// Traversing backward using prev pointer
	printf("\nReverse: ");
	while (temp != NULL)
	{
		cout << temp->data;//
		temp = temp->prev;
	}
	printf("\n");
}

//Bubble Sort
void BubbleSort(Node* head)
{
	int swapped, i;
	Node* ptr1;
	Node* lptr = nullptr;

	/* Checking for empty list */
	if (head == nullptr)
	{
		return;
	}
	do
	{
		swapped = 0;
		ptr1 = head;

		while (ptr1->next != lptr)
		{
			if (ptr1->data > ptr1->next->data)//accesding
			{
				swap(ptr1->data, ptr1->next->data);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}


//Binary Search Tree
void Search(Node* root, const string& ipKey)
{
	int depth = 0;
	Node* temp = new Node;
	temp = root;
	// Run the loop untill temp points to a NULL pointer.
	while (temp != NULL)
	{
		depth++;
		if (temp->data.key == ipKey)
		{
			cout << "\nData found at depth: " << depth;
			return;
		}
		// Shift pointer to left child.
		else if (temp->data.key > ipKey)
		{
			temp = temp->prev;
		}
		// Shift pointer to right child.
		else
		{
			temp = temp->next;
		}

	}

	cout << "\n Data not found";
	return;
}

int main() {

	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL.

	//add 10 students
	Student person1("LamLT11", "Lam", "111111");
	InsertAtTail(person1);
	Student person2("PhuHL01", "Phu", "222222");
	InsertAtTail(person2);
	Student person3("TrieuPN02", "Trieu", "333333");
	InsertAtTail(person3);
	Student person4("TrangTP03", "Trang", "444444");
	InsertAtHead(person4);
	Student person5("DuyetLT04", "Duyet", "555555");
	InsertAtHead(person5);
	Student person6("SangLV05", "Sang", "666666");
	InsertAtTail(person6);
	Student person7("DauLV06", "Dau", "777777");
	InsertAtHead(person7);
	Student person8("HungLV07", "Hung", "888888");
	InsertAtTail(person8);
	Student person9("TienLT08", "Tien", "999999");
	InsertAtTail(person9);
	Student person10("NhatNV09", "Nhat", "101010");
	InsertAtTail(person10);
	Print();

	//remove
	string ipKey;
	cout << "Enter key u want to remove:";
retry:
	fflush(stdin);
	getline(cin, ipKey);

	if (!CheckKey(ipKey))
	{
		cout << "ID must be A NUMBER" << endl;
		cout << "Enter again" << endl;
		goto retry;
	}
	Remove(head, ipKey);// loi thang dau tien 
	cout << "\n\nAfter removing a student";
	Print();

	//find
	string ipName;
	cout << "Enter name u want to find: ";
	fflush(stdin);
	getline(cin, ipName);
	//cout << ipName;
	FindByName(head, ipName);

	cout << "Enter key u want to find: ";
	fflush(stdin);
	getline(cin, ipKey);
	FindByKey(head, ipKey);



	//Sort
	BubbleSort(head);
	cout << "After Sorting" << endl;
	Print();


	cout << "Now we find student's key by search (binary search tree)" << endl;
	cout << "Enter key: ";
	fflush(stdin);
	getline(cin, ipKey);
	Search(head, ipKey);
}




