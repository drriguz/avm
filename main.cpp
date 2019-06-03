#include "class_parser.h"
#include "format/class_file.h"

#include <iostream>
using namespace std;
using namespace avm;

int main(int argc, char* argv[]) {
	cout << "Running" << endl;
	avm::ClassParser parser;
	ClassFile parsed = parser.parse("test/Const.class");
	parsed.verbose();
	return 1;
}
