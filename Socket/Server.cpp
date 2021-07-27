#pragma warning(disable : 4996)
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
#include <string>
#include<experimental/filesystem>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
namespace fs = std::experimental::filesystem;


//list folder and file names in path
void ListFilesAndFolders(const std::string& path,const SOCKET& AcceptSocket)
{
    //// STEP-7 Send Data to Client
    int iSend;
    const char* SenderBuffer=nullptr;
    

    if (fs::is_empty(path))//check folder empty or not? 
    {
        std::cout << "  this file is empty\n";
        //=>send to client
       SenderBuffer = "this file is empty (from Server)\n";
       int   iSenderBuffer = strlen(SenderBuffer) + 1;
       iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
       return;
    }

    string total;
    for (const auto& entry : fs::directory_iterator(path))
    {
        
        total += entry.path().string();
        total += "\n";
        
    }
    const char* result = total.c_str();
    int   iSenderBuffer = strlen(result) + 1;

    iSend = send(AcceptSocket, result, iSenderBuffer, 0);
    if (iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;
   
    
}
// delete all files in path
void DeleteDirectoryContents(const std::string& path, const SOCKET& AcceptSocket)
{

    int iSend;
    const char* SenderBuffer = nullptr;

    if (fs::is_empty(path))//check folder empty or not?
    {
        std::cout << "  this file is empty\n";
         //=>send to client
        SenderBuffer = "this file is empty (from Server)\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
        return;
        
    }

    for (const auto& entry : std::experimental::filesystem::directory_iterator(path))
    {
        std::experimental::filesystem::remove_all(entry.path());
        SenderBuffer = "All folders and files are removed\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);

    }
}
//path input =>check input already exit? => check content empty? => open file selected
//path output => check output already exit
//copy file
void CopyFile(const string& inputFilePath, const string& outputFilePath, const SOCKET& AcceptSocket)
{
    int iSend;
    const char* SenderBuffer = nullptr;
    //file already exit?
    if (!(std::experimental::filesystem::exists(inputFilePath)))
    {
        std::cout << "Source file does not exit\n";
        //send to client
        SenderBuffer = "Source file does not exit (from Server)\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
        return;
    }
   

    string line;
    fstream ini_file{inputFilePath};

    if (ini_file.peek() == std::ifstream::traits_type::eof())//check file empty or not?
    {
        //send to client
        cout << "Source file is empty"<<endl;
        SenderBuffer = "Source file is empty (from Server)\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
        return;

    }

    //output file already exit?
    fstream out_file{ outputFilePath };
    if (!(std::experimental::filesystem::exists(outputFilePath)))
    {
        cout << "Copy file does not exit"<<endl;
        SenderBuffer = "Copy file does not exit (from Server)\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
        return;
    }
    //fstream out_file{ outputFilePath };

    if (ini_file && out_file) 
    {

        while (getline(ini_file, line)) //ini_file>>line
        {
            out_file << line << "\n";
        }

        SenderBuffer = "Copy Finished (from Server)\n";
        int   iSenderBuffer = strlen(SenderBuffer) + 1;
        iSend = send(AcceptSocket, SenderBuffer, iSenderBuffer, 0);
        return;

    }
    else 
    {
        //Something went wrong
        printf("Cannot read File");
    }

    //Closing file
    ini_file.close();
    out_file.close();

    
}


int main()
{
    cout << "\t\t------ TCP SERVER ---------" << endl;
    cout << "Setting up......................." << endl;
    Sleep(1000);
    cout << endl;
    //Local Variable
    WSADATA   Winsockdata;
    int       iWsaStartup;
    int       iWsaCleanup;

    SOCKET   TCPServerSocket;
    int      iCloseSocket;

    struct  sockaddr_in  TCPServerAdd;
    struct  sockaddr_in  TCPClientAdd;
    int     iTCPClientAdd = sizeof(TCPClientAdd);

    int iBind;

    int iListen;

    SOCKET sAcceptSocket;

    int   iSend;
    char  SenderBuffer[512] = "Hello from Server!";
    int   iSenderBuffer = strlen(SenderBuffer) + 1;

    int  iRecv;
    char RecvBuffer[512];
    int  iRecvBuffer = strlen(RecvBuffer) + 1;

    // STEP -1 WSAStartUp Fun
    iWsaStartup = WSAStartup(MAKEWORD(2, 2), &Winsockdata);
    if (iWsaStartup != 0)
    {
        cout << "WSAStartUp Failed" << endl;
    }
    cout << "WSAStartUp Success" << endl;

    // STEP-2 Fill the Structure =>set up socket    
    TCPServerAdd.sin_family = AF_INET;
    TCPServerAdd.sin_addr.s_addr = inet_addr("127.0.0.1");//same
    TCPServerAdd.sin_port = htons(8000);//same

    //STEP -3 Socket Creation
    TCPServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//họ giao thức, kiểu socket, kiểu giao thức 
    if (TCPServerSocket == INVALID_SOCKET)// khởi tạo thất bại 
    {
        cout << "TCP Server Socket Creation Failed" << endl;
        cout << "Error Code - " << WSAGetLastError() << endl;
    }
    cout << "TCP Server Socket Creation Success" << endl;

    //STEP-4 bind fun
    iBind = bind(TCPServerSocket, (SOCKADDR*)&TCPServerAdd, sizeof(TCPServerAdd));// gán địa chỉ cho socket 
    if (iBind == SOCKET_ERROR)
    {
        cout << "Binding Failed" << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Binding Success" << endl;

    //STEP-5 Listen fun
    iListen = listen(TCPServerSocket, 2);// chỉ định socket lắng nghe, kết nối || số lượng tối đa kết nối đang chờ 
    if (iListen == SOCKET_ERROR)// chỉ định lắng nghe thất bại
    {
        cout << "Listen Fun Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Listen Fun Success" << endl;
    //done set up
    Sleep(1000);
    system("cls");
    cout << "Set up are completed "<<endl;
    Sleep(1000);
    

    cout << "Waiting for client request:..." << endl;

    // STEP-6 Accept
    sAcceptSocket = accept(TCPServerSocket, (SOCKADDR*)&TCPClientAdd, &iTCPClientAdd);// chờ chấp nhận kết nối 
    if (sAcceptSocket == INVALID_SOCKET)
    {
        cout << "Accept Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Connection Accepted" << endl;

     //STEP-7 Send Data to Client

   
    iSend = send(sAcceptSocket, SenderBuffer, iSenderBuffer, 0);// accept, SenderBuffer[512] = "Hello from Server!", size 
    if (iSend == SOCKET_ERROR)
    {
        cout << "Sending Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Data Sending Success " << endl;

    // STEP-8 Recv Data from Client

    while (true)
    {
        system("cls");

        iRecv = recv(sAcceptSocket, RecvBuffer, iRecvBuffer, 0);
        if (iRecv == SOCKET_ERROR)
        {
            cout << "Receive Data Failed " << endl;
            cout << "Error No-> " << WSAGetLastError() << endl;
        }
        cout << "DATA RECEIVED -> " << RecvBuffer << endl;

        //========HANDLE RECVBUFFER==========
        string recvString = RecvBuffer;
        vector<string> split{};
        stringstream s(recvString);
        string item;
        char delim = ' ';
        //get the path from string
        while (getline(s, item, delim))
        {
            split.push_back(item);
        }


        string path = split.at(split.size() - 1);
        if (strncmp(RecvBuffer, "List", 4) == 0)//compare 4 first chars
        {
            cout << "Path: " << path << endl;
            ListFilesAndFolders(path, sAcceptSocket);
            Sleep(3000);
            system("cls");
        }
        else if (strncmp(RecvBuffer, "Remove", 6) == 0)
        {
            cout << "Path: " << path << endl;
            DeleteDirectoryContents(path, sAcceptSocket);

            Sleep(2000);
            system("cls");
        }
        else if (strncmp(RecvBuffer, "Send", 4) == 0)
        {

            string inputFilePath = split.at(split.size() - 2);
            string outputFilePath = split.at(split.size() - 1);

            cout << "Path: " << inputFilePath << endl;
            cout << "Path 2: " << outputFilePath << endl;

            CopyFile(inputFilePath, outputFilePath, sAcceptSocket);

        }
        else
        {
            break;
        }
        
    }
    
    // STEP-9 Close Socket
    iCloseSocket = closesocket(TCPServerSocket);
    if (iCloseSocket == SOCKET_ERROR)
    {
        cout << "Closing Socket Failed " << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "Closing Socket Success" << endl;
    // STEP-10 CleanUp from DLL
    iWsaCleanup = WSACleanup();
    if (iWsaCleanup == SOCKET_ERROR)
    {
        cout << "CleanUp Fun Failed " << WSAGetLastError() << endl;
        cout << "Error No-> " << WSAGetLastError() << endl;
    }
    cout << "CleanUp Fun Success" << endl;

    //system("PAUSE");
    return 0;


    cout << "-------------------------------" << endl;



    
}