#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

std::string Add0BeforeIntSmallerThan10(int num)
{
	std::string st = "";
	if (num < 10 and num >= 0)
		st += L'0';
	st += std::to_string(num);
	return st;
}

enum class SEVERITY
{
	CRITICAL = 0,
	ERROR = 1,
	WARNING = 2,
	DEBUG = 3,
	INFO = 4
};

std::string SeverityToString(SEVERITY severity)
{
	switch (severity)
	{
	case SEVERITY::CRITICAL:
		return "CRITICAL";
	case SEVERITY::ERROR:
		return "ERROR";
	case SEVERITY::WARNING:
		return "WARNING";
	case SEVERITY::DEBUG:
		return "DEBUG";
	case SEVERITY::INFO:
		return "INFO";
	default:
		return "UNKNOWN";
	}
}

std::string TmToDateString(tm tm, char delimiter = '-')
{
	std::string out = "";
	out += Add0BeforeIntSmallerThan10(tm.tm_year + 1900) + delimiter;
	out += Add0BeforeIntSmallerThan10(tm.tm_mon + 1) + delimiter;
	out += Add0BeforeIntSmallerThan10(tm.tm_mday);
	return out;
}

std::string TmToTimeString(tm tm, char delimiter = ':')
{
	std::string out = "";
	out += Add0BeforeIntSmallerThan10(tm.tm_hour) + delimiter;
	out += Add0BeforeIntSmallerThan10(tm.tm_min) + delimiter;
	out += Add0BeforeIntSmallerThan10(tm.tm_sec);
	return out;
}

//Date Time Severity Message
struct LOG
{
	tm timeStamp; //Log's time stamp
	enum SEVERITY severity; //Log's severity
	std::string message; //Log's message

	std::string LogToString(char delimiter = ' ');
	void PrintLog();


	std::fstream logFile;

	void Close();
	bool Open(std::string fileName);
	void SaveLog();
};

std::string LOG::LogToString(char delimiter)
{
	return (TmToDateString(timeStamp) + delimiter + TmToTimeString(timeStamp) + delimiter + SeverityToString(severity) + delimiter + message);
}

void LOG::PrintLog()
{
	std::cout << LogToString() << std::endl;
}

bool LOG::Open(std::string fileName)
{
	logFile.open(fileName, std::ios::out | std::ios::app);
	return logFile.is_open();
}

void LOG::Close()
{
	logFile.close();
}

void LOG::SaveLog()
{
	logFile << LogToString() << std::endl;
}

LOG Log(SEVERITY severity, std::string message)
{
	LOG log;
	log.severity = severity;
	log.message = message;
	time_t _t;
	time(&_t);
	localtime_s(&log.timeStamp, &_t);
	return log;
}

int main()
{
	LOG log;

	//Maybe pick a folder outside of the project folder
	log.Open("logs.log");

	log = Log(SEVERITY::INFO, "Hellooo");
	log.PrintLog();
	log.SaveLog();

	log = Log(SEVERITY::CRITICAL, "Hellooo");
	log.PrintLog();
	log.SaveLog();

	log = Log(SEVERITY::DEBUG, "Hellooo");
	log.PrintLog();
	log.SaveLog();

	log = Log(SEVERITY::ERROR, "Hellooo");
	log.PrintLog();
	log.SaveLog();

	log = Log(SEVERITY::WARNING, "Hellooo");
	log.PrintLog();
	log.SaveLog();

	log.Close();
}