#include "parser/class_file_parser.h"

#include <iostream>
using namespace std;
using namespace avm;

int main(int argc, char **argv) {
	cout << "♩♪♫♬♭♮" << endl;

	ClassFileParser parser("res/com/test/Simple.class");
	const JavaClass javaClass = parser.parse();
	return 0;
}
