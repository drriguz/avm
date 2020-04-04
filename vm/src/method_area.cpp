#include "vm/method_area.h"
#include "class_file/exceptions.h"

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
	_loadedClasses[className] = std::unique_ptr<JavaClass>(javaClass);
}
