#include "vm/class_loader.h"

using namespace avm;

ClassLoader::ClassLoader(MethodArea* methodArea):
    _methodArea(methodArea) {

}

ClassLoader::~ClassLoader() {

}

void ClassLoader::defineClass(const JavaClass& theClass) {

}

void ClassLoader::link(const JavaClass& theClass) {

}

void ClassLoader::load(const std::string& className) {
    auto newClass = std::shared_ptr<JavaClass>(new JavaClass());
    readClass(className, *newClass.get());
    _loadedClasses[className] = newClass;
    auto vmClass = std::unique_ptr<VmClass>(new VmClass(std::shared_ptr<JavaClass>(newClass)));
    _methodArea->putClass(className, std::move(vmClass));
}