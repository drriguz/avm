#include "class_file/parser/class_file_parser.h"

#include <iostream>
#include <string>

using namespace std;
using namespace avm;

void help() {
    cout << "Usage:\n" << "guava -classpath <classpath> mainClass" << endl;
}
int main(int argc, char *argv[]) {
    if (argc != 4 || string(argv[1]) != "-classpath") {
        help();
        return 1;
    }
    string classpath = argv[2], entry = argv[3];

    return 0;
}
