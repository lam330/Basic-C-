#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

#define ERR_LEVEL 0
#define WARN_LEVEL 1
#define INFO_LEVEL 2
#define DEBUG_LEVEL 3

class Logger {
public:
	static Logger* GetInstance(int stdchannel);
	static Logger* GetInstance(const string& filepath);
	int GetSeverity() { return mSeverityLevel; }
	int SetSeverity(int level) { return mSeverityLevel = level; }
	virtual void log(int serverityLevelOfMessage, const char* format) = 0;
protected:
	int mSeverityLevel;
	Logger() {} ;
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
};

class LoggerFile : public Logger {
	friend Logger* Logger::GetInstance(int stdchannel);
	friend Logger* Logger::GetInstance(const string& filepath);
public:
	~LoggerFile() {
		if (mOutputHandle) fclose(mOutputHandle);
	}
	void log(int serverityLevelOfMessage, const char* format) {
		time_t now = time(NULL);
		tm* t = localtime(&now);
		string temp = "";
		temp.append("[");
		temp.append(to_string(t->tm_year+1900));
		temp.append("-");
		temp.append(to_string(t->tm_mon + 1));
		temp.append("-");
		temp.append(to_string(t->tm_mday));
		temp.append(" ");
		temp.append(to_string(t->tm_hour));
		temp.append(":");
		temp.append(to_string(t->tm_min));
		temp.append(":");
		temp.append(to_string(t->tm_sec));
		//temp.append(".");
		//temp.append()		//havent find milisec yet.
		switch (serverityLevelOfMessage) {
		case ERR_LEVEL: {temp.append("] [ERROR] "); break; }
		case WARN_LEVEL: {temp.append("] [WARNING] "); break; }
		case INFO_LEVEL: {temp.append("] [INFO] "); break; }
		case DEBUG_LEVEL: {temp.append("] [DEBUG] "); break; }
		}
		temp.append(format);
		//can also use this
		//char* str = new char[temp.size()+1];
		//strcpy(str, temp.c_str());
		//str[temp.size()] = '\0';
		//if (serverityLevelOfMessage <= mSeverityLevel) {
		//fwrite(str, strlen(str), 1, mOutputHandle);
		//fwrite("\n", 1, 1, mOutputHandle);
		//}
		//delete[] str;
		//str = NULL;
		if (serverityLevelOfMessage <= mSeverityLevel) {
			fwrite(temp.c_str()	, strlen(temp.c_str()), 1, mOutputHandle);
			fwrite("\n",1,1,mOutputHandle);
			fflush(mOutputHandle);
		}

	}
protected:
	FILE* mOutputHandle;
	LoggerFile(const string& filePath) {
		mOutputHandle = fopen("OUTPUT.txt", "w"); // "w" Creates an empty file for writing. If a file with the same name has been survived at, content of it was purging and the file was view as a new file is blank
	}
	LoggerFile(FILE* alreadyHandle) {
		mOutputHandle = alreadyHandle;
	}
	LoggerFile() {};
	LoggerFile(const LoggerFile&) = delete;
	LoggerFile& operator=(const LoggerFile&) = delete;
};

Logger* Logger::GetInstance(int stdchannel) {
	if (stdchannel == 0) { //logger for stdout
		return new LoggerFile(stdout);
	}
	else { // logger for stderr
		return new LoggerFile(stderr);
	}
}
Logger* Logger::GetInstance(const string& filepath)
{
	return new LoggerFile(filepath);
}

int main() {

	int Select;

	do 
	{
		cout << "\nSelect = ";
		cin >> Select;

		switch (Select)
		{
		case 0:
		{
			break;
		}
		case 1:
		{	// logger to stdout
			Logger* logger = Logger::GetInstance(0);
			logger->SetSeverity(INFO_LEVEL);
			logger->log(ERR_LEVEL, "ERROR!!!!");
			logger->log(WARN_LEVEL, "WARNING!!!");
			logger->log(INFO_LEVEL, "INFO!!");
			logger->log(DEBUG_LEVEL, "DEBUG!");
			break;
		}
		case 2:
		{	// logger to stderr
			Logger* logger = Logger::GetInstance(1);
			logger->SetSeverity(WARN_LEVEL);
			logger->log(ERR_LEVEL, "ERROR!!!!");
			logger->log(WARN_LEVEL, "WARNING!!!");
			logger->log(INFO_LEVEL, "INFO!!");
			logger->log(DEBUG_LEVEL, "DEBUG!");
			break;
		}
		case 3:
		{	// logger to File
			Logger* logger = Logger::GetInstance("OUTPUT.txt");
			logger->SetSeverity(WARN_LEVEL);
			logger->log(WARN_LEVEL, "WARNING!!!");
			logger->log(INFO_LEVEL, "INFO!!");
			logger->log(DEBUG_LEVEL, "DEBUG!");
			break;
		}

		default:
		{
			cout << "Wrong Select!" << endl;
			break;
		}
		}

	} 	while (Select!=0);

	return 0;
}