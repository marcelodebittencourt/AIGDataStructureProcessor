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

	void instanceArraysFanIn();
	unsigned int populateStructureUsingAutoGeneratedConstant0(unsigned int numberPositionArray);

	unsigned int readInputs(unsigned int posArray, bool AagFile);
	unsigned int getNumInputs();
	string listArraysFanIn(unsigned int startPosition, unsigned int endPosition);

	void readOutputs();
	unsigned int getNumOutputs();
	string listArrayOutputs();

	unsigned int readAnds(unsigned int posArray);
	unsigned int getNumAnds();

	bool closeAigFile();
	virtual ~AIGParser();

private:
	string listHeaderString;
	string listArraysFanInString;
	ifstream fileAig;
	unsigned int numInputs;
	unsigned int numLatches;
	unsigned int numOutputs;
	unsigned int numAnds;
	unsigned int numNodes;

	unsigned int *arrayFanIn1;
	unsigned int *arrayFanIn2;

	unsigned int *arrayOutputs;
};
}
}

#endif /* AIGPARSER_H_ */
