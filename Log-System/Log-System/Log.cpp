#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Log.h"

void CreateSaveDir()
{
	system("mkdir c:\\ProjectSaveFiles");
	system("mkdir c:\\ProjectSaveFiles\\Log-System");
	system("cls");
}

std::string AddLeadingZeroes(int num)
{
	std::string st = "";
	if (num < 10 and num >= 0)
		st += L'0';
	st += std::to_string(num);
	return st;
}

std::string TmToDateString(tm tm, char delimiter)
{
	std::string out = "";
	out += AddLeadingZeroes(tm.tm_year + 1900) + delimiter;
	out += AddLeadingZeroes(tm.tm_mon + 1) + delimiter;
	out += AddLeadingZeroes(tm.tm_mday);
	return out;
}

std::string TmToTimeString(tm tm, char delimiter)
{
	std::string out = "";
	out += AddLeadingZeroes(tm.tm_hour) + delimiter;
	out += AddLeadingZeroes(tm.tm_min) + delimiter;
	out += AddLeadingZeroes(tm.tm_sec);
	return out;
}

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

void LOG::Log(SEVERITY inSeverity, std::string inMessage)
{
	severity = inSeverity;
	message = inMessage;
	time_t _t;
	time(&_t);
	localtime_s(&timeStamp, &_t);
}

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
	logFstream.open(fileName, std::ios::out | std::ios::app);
	return logFstream.is_open();
}

void LOG::Close()
{
	logFstream.close();
}

void LOG::SaveLog()
{
	PrintLog();
	logFstream << LogToString() << '\n';
}