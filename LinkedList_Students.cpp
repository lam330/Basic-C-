// LinkedList_Students.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<vector>
#include<Windows.h>
using namespace std;

//Quản lý danh sách sinh viên bằng danh sách liên kết
//1. Tạo 1 file text, trong đó chứa dữ liệu là danh sách sinh viên gồm các thông tin : Ho ten, ngay sinh, lớp
//Mỗi 1 dòng trong file thể hiện thông tin của 1 sinh viên, các thông tin của mỗi sinh viên cách nhau dấu ','
//File này tạo manual bằng tay
//2. Đọc file dữ liệu bên trên, sử dụng danh sách liên kết để quản lý dữ liệu
//3. Đưa ra màn hình các lựa chọn :
//-Xuất thông tin
//- Sắp xếp dữ liệu, in ra thông tin danh sách
//- Thêm / sửa / xóa dữ liệu(có cập nhật vào file)

struct Student
{

    string name;
    int dateOfBirth;
    string _class;

    Student() {}
    Student(string ipName, int ipDate, string ipClass) : name(ipName), dateOfBirth(ipDate), _class(ipClass) {}
    Student(const Student& obj)
    {
        name = obj.name;
        dateOfBirth = obj.dateOfBirth;
        _class = obj._class;
    }

    Student& operator=(const Student& ipPerson)
    {
        if (this == &ipPerson)
        {
            return *this;
        }
        name = ipPerson.name;
        dateOfBirth = ipPerson.dateOfBirth;
        _class = ipPerson._class;
        return *this;
    }

    bool operator>(const Student& obj)
    {
        //convert string to int
        stringstream buff1(_class);
        int lValue = 0;
        buff1 >> lValue;

        stringstream buff2(obj._class);
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
        stringstream buff1(_class);
        int lValue = 0;
        buff1 >> lValue;

        stringstream buff2(obj._class);
        int rValue = 0;
        buff2 >> rValue;

        //compare
        if (lValue < rValue)
        {
            return true;
        }
        return false;
    }



    friend std::ostream& operator << (std::ostream& out, const Student& ipPerson)
    {


        out << setw(15) <<"  "  << left << ipPerson.name << "\t\t" << ipPerson.dateOfBirth << "\t\t" << ipPerson._class << endl;
        return out;
    }



    void DisplayOne(const Student& ipPerson, int& index)
    {
        index++;
        cout << index << setw(20) << ipPerson.name << setw(20) << ipPerson.dateOfBirth
            << setw(20) << ipPerson._class << endl;

    }

    //check input Student data
    bool CheckName(const string& ipName)
    {
        for (unsigned int i = 0; i < ipName.length(); ++i)
        {
            if (!((ipName[i] >= 'a' && ipName[i] <= 'z') || (ipName[i] >= 'A' && ipName[i] <= 'Z') || ipName[i] == ' '))
            {
                return false;
            }
        }
        return true;
    }

    bool CheckDateOfBirth(const int& ipDate)
    {
        if (!(ipDate > 0 && ipDate <= 31))
        {
            return false;
        }
        return true;
    }

    bool CheckClass(const string ipClass) 
    {
        for (unsigned int i = 0; i < ipClass.length(); ++i)//17CDT2
        {
            if (!((ipClass[i] >= 'a' && ipClass[i] <= 'z') || (ipClass[i] >= 'A' && ipClass[i] <= 'Z') || ipClass[i] == ' ') || ( ipClass[i] >= '1' && ipClass[i] <= '9'))
            {
                return false;
            }
        }
        return true;
    }

    void EnterOne()
    {

        cout << "Enter info:" << endl;
    retry:
        cout << "Name: ";
        cin.ignore(32767, '\n');
        getline(cin, name);
        

        if (!CheckName(name))
        {
            cout << "Name is not allowed for SPECIAL CHARACTERS or NUMBER!" << endl;
            cout << "Enter again" << endl;
            goto retry;
        }

    retry1:
        cout << "Date of birth: ";
       
        cin >> dateOfBirth;
        cin.ignore(32767, '\n');
        if (!CheckDateOfBirth(dateOfBirth))
        {
            cout << "Date must be A NUMBER" << endl;
            cout << "Enter again" << endl;
            goto retry1;
        }
        
        
    retry2:
        cout << "Class: ";
        //cin.ignore(32767, '\n');
        getline(cin, _class);
        //getline(cin, _class);
        //fflush(stdin);
       
        if (!CheckClass(_class))
        {
            cout << "Clas is not allowed for SPECIAL CHARACTERS" << endl;
            cout << "Enter again" << endl;
            goto retry2;
        }

    }


};


// sv1 -> sv2 -> sv3 -> ... -> svn -> nullptr

struct Node
{
    Student data;
    Node* next;

    Node()
    {
        next = nullptr;
    }
    ~Node()
    {
        if (next != nullptr)
        {
            delete next;
            next = nullptr;
        }
    } 
};
Node* head; // head of LL

struct Node* CreateNewNode(const Student& ipPerson)
{
    
    Node* newNode = new Node;
    newNode->data = ipPerson;// operator = 
    newNode->next = nullptr;

    return newNode;
}

void InsertAtHead(Node*& head,const Student& ipPerson)
{
    Node* newNode = CreateNewNode(ipPerson);
    if (head == NULL)//empty list => head point to first student (newNode) 
    {
        head = newNode;
        return;
    }
    //make newNode => head  [] []
    newNode->next = head;
    head = newNode;
}

void InsertAtTail(Node*& head, const Student& ipPerson)
{
    Node* newNode = CreateNewNode(ipPerson);
    Node* out = head;

    if (head == NULL)//empty list => head point to first student (newNode) 
    {
        head = newNode;
        return;
    }
    
    while (out->next != nullptr)//go to the last ele
    {
        out = out->next;
    }
    out->next = newNode;
    newNode->next = nullptr;
}

void RemoveAtHead(Node*& head) 
{
    if (head == NULL) 
    {
        return;
    }
    Node* out = head;
    head = head->next;
    out->next = nullptr;
    delete out;
    out = nullptr;
    //return;
}

void RemoveAtTail(Node*& head)// [] []
{
    

    if (head->next == nullptr)//empty list => head point to first student (newNode) 
    {
        head = nullptr;
        return;
    }

    Node* out = head;
    while (out->next->next != nullptr)//go to the second last ele
    {
        out = out->next;
    }

    Node* lastNode = out->next;// last ele
    out->next = nullptr;

    delete lastNode;
    lastNode = nullptr;
}

Student HandleLine(const string& line)
{
    Student newStudent;
    int kind = 0;
    stringstream buff(line);
    string part;
    while (getline(buff, part, ',')) // get chars from buff and store them into part until ',' found
    {
        kind++;
        if (part[0] == ' ')//name, date, class
        {
            part = part.substr(1, part.length() - 1);// get (length) chars from char[1]
        }

        if (kind == 1)
        {
            // assign name
            newStudent.name = part;
        }
        if (kind == 2)
        {
            // assign date
            newStudent.dateOfBirth = stoi(part);// convert string to int
        }
        if (kind == 3)
        {
            // assign class
            newStudent._class = part;
        }
    }
    return newStudent;
}

void ReadFromFile(Node*& head, const string& fileName)
{
    Node* runHead = head;

    fstream file;
    file.open(fileName, ios::in);//open file | mode: read only
    if (file.fail())
    {
        cout << "Failed to open!" << endl;
    }

    vector<string> lines;
    string line;

    while (getline(file, line))//file>>line | read line by line
    {
        lines.push_back(line);
    }

    // list of lines => create students => Insert students 
    for (int index = 0; index < lines.size(); index++)
    {
        Student createStudent = HandleLine(lines.at(index));//
        InsertAtTail(head, createStudent);
    }


    file.close();
}

void WriteToFile(Node* head)// go through node and write
{
    fstream file;
    file.open("Output.txt", ios::out | ios::trunc);//open file | mode out: to write | mode trunc: contents are splited before open file
    file << "Student list: " << endl;

    Node* runHead = head;
    if (runHead == nullptr)
    {
        cout << "Empty list!";
        return;
    }

    while (runHead != nullptr)//write datas
    {
        file << runHead->data<<endl;
        runHead = runHead->next;
        
    }
    file.close();

    

}


void Print(Node* head)
{
    Node* runHead = head;
    if (runHead == nullptr)
    {
        cout << "Empty list" << endl;
        return; //empty list => exit
    }

    cout << "Tale of Students:\n";
    cout << "STT " << setw(20) << "Name" << "\t  " << "Date of birth " << "\t" << "Class" << endl;
    int index = 0;

    while (runHead != nullptr)
    {
        index++;
        cout << index<<setw(20);
        cout << runHead->data<<endl;//over load << data
        runHead = runHead->next;
    }
    cout << endl;
}

void SortByClass(Node* head)
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

void Menu()
{
    cout << setw(65) << "************************ YOUR OPTIONS ***********************" << endl;
    cout << setw(65) << "*                1. Add students                            *" << endl;
    cout << setw(65) << "*                2. Remove a student                        *" << endl;
    cout << setw(65) << "*                3. Print list                              *" << endl;
    cout << setw(65) << "*                4. Sort by class                           *" << endl;
    cout << setw(65) << "*                5. Exit                                    *" << endl;
    cout << setw(65) << "*************************************************************" << endl;
}

void MenuAdd()
{
    cout << setw(50) << "************************ YOUR OPTIONS ***********************" << endl;
    cout << setw(65) << "*                1. Add a student at head                   *" << endl;
    cout << setw(65) << "*                2. Add a student at last                   *" << endl;
}

void MenuDel()
{
    cout << setw(50) << "************************ YOUR OPTIONS ***********************" << endl;
    cout << setw(65) << "*                1. Remove a student at head                *" << endl;
    cout << setw(65) << "*                2. Remove a student at last                *" << endl;
}

int main()
{
    
    string fileName = "Input.txt";
    ReadFromFile(head, fileName);
    int selection = 0;
    while (true)
    {
        Menu();
    Enter:
        cout << "\nEnter your selection:";
        cin >> selection;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cerr << "Enter IN RANGE OF MENU and no LETTER!";
            cerr << "Retry!";
            goto Enter;
        }

        switch (selection)
        {
        case 1:
        {
            system("cls");
            char repeat = 'y';
            while (repeat == 'y')
            {
                cout << "Enter information: " << endl;
                Student person;
                person.EnterOne();

                MenuAdd();

                int kind = 0;
                cout << "Where do you want to add a student ?";
            Kind:
                cin >> kind;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();

                    cerr << "Enter IN RANGE OF MENU and no LETTER!";
                    if (kind != 1 || kind != 2)
                    {
                        cout << "1 or 2";
                    }
                    cerr << "Retry!";
                    goto Kind;
                }

                if (kind == 1)
                {
                    InsertAtHead(head, person);
                    WriteToFile(head);
                }
                else
                {
                    InsertAtTail(head, person);
                    WriteToFile(head);
                }
                cout << "Do you want to contineu to add student? (y/n) " << endl;
                cin >> repeat;
                system("cls");

            }
            break;


        }
        case 2:
        {
            system("cls");
            char repeat = 'y';
            while (repeat == 'y')
            {
           

                MenuDel();

                int kind = 0;
                cout << "Which student do you want to delete  ?";
            Kind1:
                cin >> kind;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();

                    cerr << "Enter IN RANGE OF MENU and no LETTER!";
                    if (kind != 1 || kind != 2)
                    {
                        cout << "1 or 2";
                    }
                    cerr << "Retry!";
                    goto Kind1;
                }

                if (kind == 1)
                {
                    RemoveAtHead(head);
                    WriteToFile(head);
                }
                else
                {
                    RemoveAtTail(head);
                    WriteToFile(head);
                }
                cout << "Do you want to contineu to delete student? (y/n) " << endl;
                cin >> repeat;
                system("cls");

            }
            break;
        }
        case 3:
        {
            //ReadFromFile(head, fileName);
            Print(head);
            Sleep(3000);
            system("cls");
            break;

        }
        case 4:
        {
            //ReadFromFile(head, fileName);
            SortByClass(head);
            Print(head);
            WriteToFile(head);
            Sleep(3000);
            system("cls");
            break;
        }
        case 5:
        {
            cout << "Leaving.............";
            Sleep(2000);
            system("cls");
            return 0;
        }

        default:
        {
            cout << "Retry! (1->5)";
            goto Enter;
            break;
        }

        }
    }
    
  //  ReadFromFile(head,fileName);
  //  Print();
  //  SortByClass(head);
  //  Print();
  //  
  //  WriteToFile(head);
    


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
