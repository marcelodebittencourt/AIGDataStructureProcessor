#include <iostream>
#include <climits>

#include "AIGParser.h"

namespace std {
namespace AIGP {

AIGParser::AIGParser() {
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

bool AIGParser::closeAigFile() {
	fileAig.close();
	return true;
}

AIGParser::~AIGParser() {
}


}
}

