
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma warning(disable : 4996)
#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<experimental/filesystem>
#include<fstream>
#include<string>
using namespace std;

void Menu()
{
    cout << setw(50) << "****************************** YOUR OPTIONS *************************" << endl;
    cout << setw(65) << "*          1. ls <path to directory>                                *" << endl;
    cout << setw(65) << "*          2. Remove <path to directory/file>                       *" << endl;
    cout << setw(65) << "*          3. download <path to FTP file> <path to save local file> *" << endl;
    cout << setw(65) << "*********************************************************************" << endl;
}

string ModifyPath(string& ipPath)
{
    std::replace(ipPath.begin(), ipPath.end(), '\\', '/');
    //  ipPath = ipPath.Replace(@"\\", @"\");
    return ipPath;
}

int main()
{
    cout << "\t\t------ TCP CLIENT --------" << endl;
    cout << endl;
    //Local Variable
    WSADATA       WinSockData;
    int           iWsaStartup;
    int           iWsaCleanup;

    SOCKET        TCPClientSocket;
    int           iCloseSocket;

    struct   sockaddr_in     TCPServerAdd;

    int           iConnect;

    int           iRecv;
    char          RecvBuffer[512];
    int           iRecvBuffer = strlen(RecvBuffer) + 1;

  /*  int        iSend;
    char       SenderBuffer[512] = "Hello from Client!";
    int        iSenderBuffer = strlen(SenderBuffer) + 1;*/

    //STEP-1 WSASatrtUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp Failed" << endl;
    }
    cout << "WSAStartUp Success" << endl;
    // STEP-2 Socket Creation
    TCPClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//tạo socket 
    if (TCPClientSocket == INVALID_SOCKET)
    {
        cout << "TCP Client Socket Creation Failed" << endl;
        cout << "Error Code - " << WSAGetLastError() << endl;
    }
    cout << "TCP Client Socket Creation Success" << endl;

    // STEP-3 Fill Server Structure => set up socket
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");//same ip with server
    TCPServerAdd.sin_port = htons(8000);//same port

    // STEP-4 Connect Fun
    //connect tới địa chỉ server
    iConnect = connect(TCPClientSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));
    if (iConnect == SOCKET_ERROR)
    {
        cout << "Connection Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Connection Success" << endl;

    Sleep(2000);
    system("cls");


    // STEP-5 RECV Data From Server Side = recv1

    iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
    if (iRecv == SOCKET_ERROR)
    {
        cout << "Receive Data Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "DATA RECEIVED1 -> " << RecvBuffer << endl;

    char repeat = 'y';
    while (repeat != 'n')
    {
        system("cls");
        Menu();


        // STEP-6 Send Data to Server = send 1
        int        iSend = 0;
        //char       SenderBuffer[512] = "Hello from Client!";
        int        iSenderBuffer = 0;

        //handle senderBuffer
        const char* ptr = "";

        cout << endl;
        int selection = 0;
        cout << "Enter your selection: ";
        cin >> selection;
        cin.ignore(256, '\n');
        string ipPath;


        switch (selection)
        {
        case 1:
        {

            fflush(stdin);
            cout << "Enter path: ";
            getline(cin, ipPath);
            //"C:/Users/ADMIN/Desktop/test"

            ipPath = "List all folders and files " + ipPath;
            ptr = ipPath.c_str();
            break;
        }
        case 2:
        {
            fflush(stdin);
            cout << "Enter path: ";
            getline(cin, ipPath);
            //"C:/Users/ADMIN/Desktop/test"

            ipPath = "Remove all folders and files " + ipPath;
            ptr = ipPath.c_str();
            break;

        }
        case 3:
        {

            fflush(stdin);
            cout << "Enter path: ";
            getline(cin, ipPath);
            //"C:/Users/ADMIN/Desktop/test/source.txt"
            string localFilePath;
            fflush(stdin);
            cout << "Enter local file path: ";
            getline(cin, localFilePath);
            //"C:/Users/ADMIN/Desktop/test/copyFile.txt"
            ipPath = "Send file content from " + ipPath + " " + localFilePath;
            ptr = ipPath.c_str();
            break;
        }
       
        default:
        {
            cout << "Enter in range of selection: [1->4]";
            Sleep(2000);
            break;
        }
           
        }
        iSenderBuffer = strlen(ptr) + 1;



        cout << "--------------------------------" << endl;
        //char*
        iSend = send(TCPClientSocket, ptr, iSenderBuffer, 0);
        if (iSend == SOCKET_ERROR)
        {
            cout << "Sending Failed " << endl;
            cout << "Error No-> " << WSAGetLastError() << endl;
        }
        cout << "Data Sending Success " << endl;

        //show result from sever
        iRecv = recv(TCPClientSocket, RecvBuffer, iRecvBuffer, 0);
        if (iRecv == SOCKET_ERROR)
        {
            cout << "Receive Data Failed " << endl;
            cout << "Error No-> " << WSAGetLastError() << endl;
        }
        cout << "Result:\n" << RecvBuffer << endl;

        cout << "Do you want to use orther functions? [y/n]: ";
        fflush(stdin);
        cin >> repeat;
    }

    // STEP-7 Close Socket Fun
    iCloseSocket = closesocket(TCPClientSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success" << endl;

    // STEP-8 WSA CleanUp Fun;
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR)
    {
        cout << "CleanUp Fun Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "CleanUp Fun Success" << endl;
    system("PAUSE");
    Sleep(2000);
    return 0;
    
    
}