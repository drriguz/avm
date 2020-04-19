#include "vm/runtime/method_area.h"
#include "vm/exceptions.h"

using namespace avm;

MethodArea::MethodArea() {

}

MethodArea::~MethodArea() {

}

std::shared_ptr<VmClass> MethodArea::getClass(const std::string &className) const {
    try {
        return _loadedClasses.at(className);
    } catch (...) {
        throw ClassNotFoundException(className);
    }
}

void MethodArea::registerClass(const std::string &className, std::shared_ptr<VmClass> javaClass) {
    if (_loadedClasses.count(className) > 0)
        throw ClassAlreadyLoadedException(className);
    _loadedClasses[className] = javaClass;
}

bool MethodArea::isLoaded(const std::string &className) const {
    return _loadedClasses.count(className) > 0;
}
