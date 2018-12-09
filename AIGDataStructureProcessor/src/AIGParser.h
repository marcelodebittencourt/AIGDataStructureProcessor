#ifndef AIGPARSER_H_
#define AIGPARSER_H_

#include <fstream>

namespace std {
namespace AIGP {

class AIGParser {
public:
	AIGParser();

	bool openAigFile(string completePath/*, bool binaryFile, bool reverse*/);
	string getLineAigFile();
	unsigned int readHeader(string fileExtension);
	string listHeader();
	bool closeAigFile();
	virtual ~AIGParser();
private:
	string listHeaderString;
	ifstream fileAig;
	unsigned int numInputs;
	unsigned int numLatches;
	unsigned int numOutputs;
	unsigned int numAnds;
	unsigned int numNodes;
};
}
}

#endif /* AIGPARSER_H_ */
