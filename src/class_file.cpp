#include "format/class_file.h"
#include "format/access_flags.h"
#include <iostream>

using namespace avm;

ClassFile::ClassFile() {

}

ClassFile::~ClassFile() {
	if (this->constant_pool)
		delete[] this->constant_pool;
}

void ClassFile::ensureConstantPool() {
	if (constant_pool)
		delete[] constant_pool;
	constant_pool = new ConstantInfo[constant_pool_count];
}
void ClassFile::printConstantPool() {
	for (int i = 1; i < constant_pool_count; i++) {
		ConstantInfo info = constant_pool[i];

		std::cout << "\t#" << i << ":" << info.tag << std::endl;
	}
}
void ClassFile::printInterfaces() {
	for (int i = 1; i < interfaces_count; i++) {
		std::cout << "\t#" << i << std::endl;
	}
}

void ClassFile::verbose() {
	std::cout << "magic:0x" << std::hex << int(this->magic) << std::endl
			<< std::dec << "minor_version:" << this->minor_version << std::endl
			<< "major_version:" << this->major_version << std::endl
			<< "constant_pool_count:" << this->constant_pool_count << std::endl;
	printConstantPool();
	std::string accessFlags;
	AccessFlags::getAccessFlags(this->access_flags, accessFlags);
	std::cout << "access_flags:" << accessFlags << std::endl << "this_class:"
			<< this->this_class << std::endl << "super_class:"
			<< this->super_class << std::endl;
	std::cout << "interfaces_count:" << interfaces_count << std::endl;
	printInterfaces();
}
