#include "vm/virtual_machine.h"
#include "vm/exceptions.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace avm;

void help() {
    cout << "avm - A simple JVM written in C++" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "  avm -classpath <path> <mainClass>" << endl;
    cout << endl;
    cout << "Arguments:" << endl;
    cout << "  -classpath   Directory containing .class files" << endl;
    cout << "  mainClass    Fully qualified class name (e.g. com.example.HelloWorld)" << endl;
}

int main(int argc, char *argv[]) {
    if (argc != 4 || string(argv[1]) != "-classpath") {
        help();
        return 1;
    }
    string classpath = argv[2], entry = argv[3];

    try {
        VirtualMachine vm(classpath, entry);
        vm.execute();
    } catch (const RuntimeException& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
