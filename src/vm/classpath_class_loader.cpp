#include "vm/classpath_class_loader.h"
#include "parser/class_file_parser.h"

using namespace avm;

ClasspathClassLoader::ClasspathClassLoader(const std::string& classpath)
:_classpath(classpath){

}

ClasspathClassLoader::~ClasspathClassLoader(){

}

std::string ClasspathClassLoader::getClassFilePath(const std::string& className) const {
	std::string path = _classpath + "/" + className;
	std::string::size_type i = path.find(".");
	while(i != std::string::npos) {
		path.replace(i, 1, "/");
		i = path.find(".");
	}
	return path + ".class";
}

JavaClass ClasspathClassLoader::loadClass(const std::string& className) {
	const std::string file = getClassFilePath(className);
	ClassFileParser parser(file.c_str());
	return parser.parse();
}
