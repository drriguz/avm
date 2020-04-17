#include "vm/class_loader.h"

using namespace avm;

ClassLoader::ClassLoader(MethodArea* methodArea):
    _methodArea(methodArea) {

}

ClassLoader::~ClassLoader() {

}
