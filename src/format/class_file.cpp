#include "format/class_file.h"
#include "format/access_flags.h"
#include "format/constant_printer.h"
#include <iostream>

using namespace avm;

ClassFile::ClassFile() :
		constant_pool(nullptr), interfaces(nullptr) {

}

ClassFile::~ClassFile() {
	if (this->constant_pool)
		delete[] this->constant_pool;
	if (this->interfaces)
		delete[] this->interfaces;
}

void ClassFile::ensureConstantPool() {
	if (constant_pool)
		delete[] constant_pool;
	constant_pool = new ConstantInfo[constant_pool_count];
}

void ClassFile::ensureInterfaces() {
	if (interfaces)
		delete[] interfaces;
	interfaces = new u2[interfaces_count];
}

void ClassFile::printConstantPool() {
	ConstantPrinter printer(constant_pool_count, constant_pool);
	printer.verbose();
}
void ClassFile::printInterfaces() {
	for (int i = 0; i < interfaces_count; i++) {
		std::cout << "\t#" << i << ":" << interfaces[i] << std::endl;
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
