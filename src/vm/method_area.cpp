#include "vm/method_area.h"
#include "exceptions.h"

using namespace avm;

MethodArea::MethodArea(){

}

MethodArea::~MethodArea() {

}

const JavaClass& MethodArea::getClass(const std::string& className) const{
	try{
		return _classes.at(className);
	} catch(...) {
		throw ClassNotFoundException(className);
	}
}

void MethodArea::putClass(const std::string& className, const JavaClass& javaClass){
	_classes[className] = javaClass;
}
