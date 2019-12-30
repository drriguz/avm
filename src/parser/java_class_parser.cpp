#include "parser/java_class_parser.h"
#include "exceptions.h"

#include <iostream>

using namespace avm;

JavaClassParser::JavaClassParser(){

}

JavaClassParser::~JavaClassParser(){
}

void JavaClassParser::readHeader(JavaClass& out) {
	try {
		readU4(&out._magic);
		if (out._magic != 0xCAFEBABE){
			std::cerr << "Unknown file type:" << out._magic << std::endl;
			throw NotClassFileException("Not a class file format: magic not valid");
		}
	} catch (const ReadFileException &ex) {
		throw NotClassFileException("Not a class file format:failed to read magic");
	}
}

void JavaClassParser::readConstantPool(JavaClass& out) {
	readU2(&out._constantPoolCount);
	out.ensureConstantPool();

}

ConstantInfo* JavaClassParser::readConstant(const ConstantType & type) {
	switch(type) {
	case Class:
		u2 tmp;
		readU2(&tmp);
		//ConstantClass * info = new ConstantClass(tmp);
		//return new ConstantInfo{type, (u1*)info};
	default:
		break;
	}
}

JavaClass JavaClassParser::parse() {
	reset();
	JavaClass out;
	readHeader(out);
	readU2(&out._minorVersion);
	readU2(&out._majorVersion);
	readConstantPool(out);
	return out;
}
