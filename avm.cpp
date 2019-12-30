#include "parser/class_file_parser.h"

#include <iostream>
using namespace std;
using namespace avm;

int main(int argc, char **argv) {
	cout << "♩♪♫♬♭♮" << endl;

	ClassFileParser parser("res/com/test/Constants.class");
	const JavaClass javaClass = parser.parse();
	const ConstantClass* info = (ConstantClass*)javaClass.getConstantAt(16)->info;
	cout << info->nameIndex;
	return 0;
}
