#include "class_parser.h"
#include "format/class_file.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "Hello !" << endl;
    avm::ClassParser parser;
    parser.parse("test/Const.class");
    return 1;
}
