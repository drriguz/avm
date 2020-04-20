#include "vm/class_loader.h"

#include <iostream>

using namespace avm;

ClassLoader::ClassLoader() {

}

ClassLoader::~ClassLoader() {

}

void ClassLoader::link(VmClass* vmClass) {
    // verify
    // prepare
    vmClass->prepare();
}

std::shared_ptr<JavaClass> ClassLoader::readClass(const std::string& className) {
    if(_classCache.count(className) == 0) {
        auto newClass = std::shared_ptr<JavaClass>(new JavaClass());
        readClass(className, *newClass.get());
        _classCache[className] = newClass;
    }
    return _classCache.at(className);
}
std::shared_ptr<VmClass> ClassLoader::resolve(const std::string& className, MethodArea* methodArea) {
    if(methodArea->isLoaded(className))
        return methodArea->getClass(className);
    std::cout << "Loading class:" << className << std::endl;
    std::shared_ptr<JavaClass> rawClass = readClass(className);
    auto loaded = std::shared_ptr<VmClass>(new VmClass(rawClass));

    // otherwise it's java/lang/Object
    if(rawClass->hasSuperClass()) {
        loaded->_superClass = load(rawClass->getSuperClassName(), methodArea);
    }
    for(int i = 0; i < loaded->getRawClass()->getInterfacesCount(); i++) {
        auto interface = load(loaded->getRawClass()->getInterfaceName(i), methodArea);
        loaded->_interfaces.push_back(interface);
    }
    methodArea->registerClass(className, loaded);
    return loaded;
}

std::shared_ptr<VmClass> ClassLoader::load(const std::string& className, MethodArea* methodArea) {
    auto loaded = resolve(className, methodArea);
    link(loaded.get());
    return loaded;
}