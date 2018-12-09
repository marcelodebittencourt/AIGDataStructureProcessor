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
	numNodes = 0;

	arrayFanIn1 = nullptr;
	arrayFanIn2 = nullptr;

	arrayOutputs = nullptr;

	listHeaderString = "";
	listArrayInputString = "";
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
	listHeaderString.append("Header:\n");
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

void AIGParser::instanceArraysFanIn() {
	arrayFanIn1 = new unsigned int[1 + numNodes];
	arrayFanIn2 = new unsigned int[1 + numNodes];
}

unsigned int AIGParser::populateStructureUsingAutoGeneratedConstant0(
		unsigned int numberPositionArray) {
	//populate constant 0, FanIn = null is represented by max unsigned int
	arrayFanIn1[0] = UINT_MAX; //UINT_MAX = represents the maximum unsigned in (UNSIGNED INTEGER_MAX) from include climits
	arrayFanIn2[0] = UINT_MAX;
	numberPositionArray++;
	return numberPositionArray;
}

unsigned int AIGParser::readInputs(unsigned int posArray, bool AagFile) {
	string line;

	for (unsigned int i = 0; i < numInputs; i++) {
		getline(fileAig, line);
		//set all fanIns to max unsigned int
		arrayFanIn1[posArray] = UINT_MAX;
		arrayFanIn2[posArray] = UINT_MAX;

		posArray++;
	}
	return posArray;
}

unsigned int AIGParser::getNumInputs() {
	return numInputs;
}

string AIGParser::listArraysFanIn() {

	listArrayInputString.append("List of INPUTS:\n");

	for (unsigned int i = 1; i <= numInputs; i++) {
		listArrayInputString.append("Position->");
		listArrayInputString.append(to_string(i));

		listArrayInputString.append(" FanIn1->");
		listArrayInputString.append(to_string(arrayFanIn1[i]));

		listArrayInputString.append(" FanIn2->");
		listArrayInputString.append(to_string(arrayFanIn2[i]));

		listArrayInputString.append("\n");
	}
	return listArrayInputString;
}

void AIGParser::readOutputs() {
	string line;

	arrayOutputs = new unsigned int[numOutputs];
	unsigned int numNodeOutput;
	for (unsigned int i = 0; i < numOutputs; i++) {
		getline(fileAig, line);
		numNodeOutput = stoi(line);
		arrayOutputs[i] = numNodeOutput;
	}
}

string AIGParser::listArrayOutputs() {
	string listArrayOutputsString = "";
	listArrayOutputsString.append("List of Outputs:\n");
	for (unsigned int i = 0; i < numOutputs; i++)
		listArrayOutputsString.append(
				"Output " + to_string(i) + "->" + to_string(arrayOutputs[i]) + "\n");
	return listArrayOutputsString;
}

bool AIGParser::closeAigFile() {
	fileAig.close();
	return true;
}

AIGParser::~AIGParser() {
	delete[] arrayFanIn1;
	delete[] arrayFanIn2;

	delete[] arrayOutputs;
}

}
}

