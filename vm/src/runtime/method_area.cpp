#include "vm/runtime/method_area.h"
#include "vm/exceptions.h" 

using namespace avm;

MethodArea::MethodArea(){

}

MethodArea::~MethodArea() {

}

const JavaClass* MethodArea::getClass(const std::string& className) const{
	try{
		return _loadedClasses.at(className).get();
	} catch(...) {
		throw ClassNotFoundException(className);
	}
}

void MethodArea::putClass(const std::string& className, JavaClass* javaClass){
	if(_loadedClasses.count(className) > 0)
		throw ClassAlreadyLoadedException(className);
	_loadedClasses[className] = std::unique_ptr<JavaClass>(javaClass);
}

bool MethodArea::loadedClass(const std::string& className) const{
	return _loadedClasses.count(className) > 0;
}