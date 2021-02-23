#pragma once

std::string AddLeadingZeroes(int num);

std::string TmToDateString(tm tm, char delimiter = '-');

std::string TmToTimeString(tm tm, char delimiter = ':');

enum class SEVERITY
{
	CRITICAL = 0,
	ERROR = 1,
	WARNING = 2,
	DEBUG = 3,
	INFO = 4
};

std::string SeverityToString(SEVERITY severity);

//Date Time Severity Message
struct LOG
{
	tm timeStamp; //Log's time stamp
	enum SEVERITY severity; //Log's severity
	std::string message; //Log's message

	std::string LogToString(char delimiter = ' ');
	void PrintLog();
	void Log(SEVERITY severity, std::string message);


	std::fstream logFstream;

	void Close();
	bool Open(std::string fileName);
	void SaveLog();
};