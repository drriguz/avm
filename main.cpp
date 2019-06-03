#include "class_parser.h"
#include "format/class_file.h"
#include "exceptions.h"

#include <iostream>
using namespace std;
using namespace avm;

int main(int argc, char* argv[]) {
	cout << "Running" << endl;
	avm::ClassParser parser("test/Const.class");
	try {
		ClassFile parsed = parser.parse();
		parsed.verbose();
	} catch (const RuntimeException& ex) {
		cerr << ex.what() << endl;
	}

	return 1;
}
