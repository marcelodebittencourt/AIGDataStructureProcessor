#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bitset>
#include <math.h>

#include "AIGParser.h"

using namespace std;
using namespace AIGP;

string getDateTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%F %T", timeinfo);

	return buffer;
}

ofstream fileLog;
int openLogFile(string fileLogName) {
	fileLog.open(fileLogName, std::ofstream::app);
	if (!fileLog) {
		cout << "Unable to open log file: " << fileLogName << endl;
		return 1;
	}
	return 0;
}

void writeLog(string stringToWrite) {
	fileLog << "[" << getDateTime() << "]" << stringToWrite << endl;
}

AIGParser *aig;
int main() {
	cout << "AIG Data Structure Processor" << endl;

	//unsigned int levels;
	//string nodeTagOrder;
	//bool forward;
	//bool bestCase;
	bool flagAag;

	//levels = 8;
	//nodeTagOrder = 'b';
	//forward  = 1;
	//bestCase = 0;
	flagAag = 1;

	string logFileFullPath = "AIGProcessor.log";
	openLogFile(logFileFullPath);
	writeLog("Test file writing");

	string fileExtension;
	fileExtension = (flagAag) ? "aag" : "aig";

	string dataFileDirectory;
	dataFileDirectory = fileExtension + "s";

	string completePath;
	completePath.append("resources/");
	completePath.append(dataFileDirectory);
	completePath.append("/");
	completePath.append("C17");
	completePath.append(".");
	completePath.append(fileExtension);

	cout << "Reading file: " << completePath << "\n";

	aig = new AIGParser();
	if (!aig->openAigFile(completePath))
		return 1;

	string textToLog = "";
	writeLog("*** Reading file: " + completePath);
	textToLog = "";

	//cout << aig->getLineAigFile();

	aig->readHeader(fileExtension);

	cout << aig->listHeader();

	aig->closeAigFile();

	cout << "\n";

	fileLog.close();
	return 0;
}
