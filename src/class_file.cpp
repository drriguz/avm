#include "format/class_file.h"
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

		std::cout << "#" << i << ":" << info.tag << std::endl;
	}
}
void ClassFile::verbose() {
	std::cout << "magic:0x" << std::hex << int(this->magic) << std::endl
			<< std::dec << "minor_version:" << this->minor_version << std::endl
			<< "major_version:" << this->major_version << std::endl
			<< "constant_pool_count:" << this->constant_pool_count << std::endl;
	printConstantPool();
}
