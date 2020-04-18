#include "vm/class_loader.h"

using namespace avm;

ClassLoader::ClassLoader() {

}

ClassLoader::~ClassLoader() {

}

void ClassLoader::defineClass(const JavaClass& theClass) {

}

void ClassLoader::link(const JavaClass& theClass) {

}

std::shared_ptr<JavaClass> ClassLoader::readClass(const std::string& className) {
    if(_classCache.count(className) == 0) {
        auto newClass = std::shared_ptr<JavaClass>(new JavaClass());
        readClass(className, *newClass.get());
        _classCache[className] = newClass;
    }
    return _classCache.at(className);
}

std::unique_ptr<VmClass> ClassLoader::load(const std::string& className) {
    std::shared_ptr<JavaClass> rawClass = readClass(className);
    return std::unique_ptr<VmClass>(new VmClass(std::shared_ptr<JavaClass>(rawClass)));
}