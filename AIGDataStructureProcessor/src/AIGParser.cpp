#include <iostream>
#include <sstream>
#include <climits>

#include "AIGParser.h"

namespace std {
namespace AIGP {

AIGParser::AIGParser() {
	numInputs = 0; //I - inputs
	numLatches = 0; //L - latches
	numOutputs = 0; //O - outputs
	numAnds = 0; //A - ands
	//instance array of Node objects
	numNodes = 0;

	listHeaderString = "";
}

bool AIGParser::openAigFile(string completePath) {

	fileAig.open(completePath, std::ifstream::in | std::ifstream::binary);

	if (!fileAig) {
		cout << "Unable to read the file " << completePath << endl;
		return false;
	}
	return true;
}

string AIGParser::getLineAigFile() {
	string line;
	getline(fileAig, line); //read the first line to bypass header
	return line;
}

unsigned int AIGParser::readHeader(string fileExtension) {

	string line;

	unsigned int counterArrayWords { 0 };
	string wordRead;
	string *arrayWords;
	arrayWords = new string[100];

	getline(fileAig, line);
	string strHeader = line;
	istringstream iss(line); //copy the line to a string stream to be able to extract the word (separated by blanks)
	counterArrayWords = -1;

	do { //loop to read word by word
		iss >> wordRead;
		//check if the text is different from empty
		if (wordRead != "") { //if the read word has at least one character
			counterArrayWords++;
			arrayWords[counterArrayWords] = wordRead; //insert each string separated by blanks in a position of array
		} //end of if word has at least one character
	} while (iss); //end of the loop that reads a line word by word
	if (counterArrayWords != 6) { //if the first line has 6 word aag M I L O A
		cout << "Header check 1: ERROR - It has NOT 6 words." << endl;
		return 1;
	}
	if (arrayWords[0] != fileExtension) { //check if the first word is different from "aag"
		cout << "Header check 2: ERROR - Invalid type of file! Found: "
				<< arrayWords[0] << " Expected: " << fileExtension << endl;
		return 2;
	}
	//numMaxVar_h  = stoi(arrayWords[1]); //M - Max variables
	numInputs = stoi(arrayWords[2]); //I - inputs
	numLatches = stoi(arrayWords[3]); //L - latches
	numOutputs = stoi(arrayWords[4]); //O - outputs
	numAnds = stoi(arrayWords[5]); //A - ands
	//instance array of Node objects
	numNodes = numInputs + numAnds;

	delete[] arrayWords;

	return 0;
}

string AIGParser::listHeader() {
	listHeaderString.append("Inputs->");
	listHeaderString.append(to_string(numInputs));
	listHeaderString.append(" Latches->");
	listHeaderString.append(to_string(numLatches));
	listHeaderString.append(" Outputs->");
	listHeaderString.append(to_string(numOutputs));
	listHeaderString.append(" Ands->");
	listHeaderString.append(to_string(numAnds));
	listHeaderString.append(" Nodes->");
	listHeaderString.append(to_string(numNodes));

	return listHeaderString;
}

bool AIGParser::closeAigFile() {
	fileAig.close();
	return true;
}

AIGParser::~AIGParser() {
}

}
}

