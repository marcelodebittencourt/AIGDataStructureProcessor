//============================================================================
// Name        : AIGDataStructureProcessor.cpp
// Author      : Marcelo de Bittencourt
// Version     :
// Copyright   : Copyright 2018
// Description : AIG Data Structure Processor in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bitset>
#include <math.h>

using namespace std;

string getDateTime() {
#ifdef DEBUG
	cout << "string AIGProcessor::getDateTime()" << endl;
#endif
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%F %T",timeinfo);

	return buffer;
}

ofstream fileLog;
int openLogFile(string fileLogName) {
	fileLog.open( fileLogName, std::ofstream::app ); //open the log file //std::ofstream::trunc
	if ( !fileLog ) {
		cout << "Unable to open log file: " << fileLogName << endl;
		return 1;
	}
	return 0;
}

void writeLog(string stringToWrite) {
	fileLog << "[" << getDateTime() << "]" << stringToWrite << endl;
}

int main() {
	cout << "AIG Data Structure Processor" << endl; // prints Read .aig file
	string logFileFullPath = "AIGProcessor.log";
	openLogFile( logFileFullPath );
	writeLog("Test file writing");
	fileLog.close();
	return 0;
}
