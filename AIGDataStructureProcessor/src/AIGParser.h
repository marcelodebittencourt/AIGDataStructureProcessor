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
	bool closeAigFile();
	virtual ~AIGParser();
private:
	ifstream fileAig;
};
}
}

#endif /* AIGPARSER_H_ */
