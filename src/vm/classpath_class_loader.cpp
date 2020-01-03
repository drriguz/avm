#include "vm/classpath_class_loader.h"
#include "parser/class_file_parser.h"
#include "helper/strings.h"

using namespace avm;

ClasspathClassLoader::ClasspathClassLoader(const std::string& classpath)
:_classpath(classpath){

}

ClasspathClassLoader::~ClasspathClassLoader(){

}

std::string ClasspathClassLoader::getClassFilePath(const std::string& className) const {
	return _classpath + "/" + Strings::replaceAll(className, ".", "/") + ".class";
}

JavaClass ClasspathClassLoader::loadClass(const std::string& className) {
	const std::string file = getClassFilePath(className);
	ClassFileParser parser(file.c_str());
	return parser.parse();
}
