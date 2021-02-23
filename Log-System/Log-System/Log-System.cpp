#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "Log.h"

int main()
{
	CreateSaveDir();
	LOG log;
	//Maybe pick a folder outside of the project folder
	if (log.Open("c:\\ProjectSaveFiles\\Log-System\\logs.log"))
	{
		log.Log(SEVERITY::INFO, "Program has started successfully");
		log.SaveLog();

		log.Close();
	}
}