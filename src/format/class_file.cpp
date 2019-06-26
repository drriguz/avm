#include "format/class_file.h"
#include "format/access_flags.h"
#include <iostream>
#include "format/constant_visitor.h"

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

void ClassFile::ensureFields() {
	if (fields)
		delete[] fields;
	fields = new FieldInfo[fields_count];
}

void ClassFile::printConstantPool() {
	ConstantVisitor visitor(constant_pool_count, constant_pool);
	visitor.verbose();
}
void ClassFile::printInterfaces() {
	ConstantVisitor visitor(constant_pool_count, constant_pool);
	for (int i = 0; i < interfaces_count; i++) {
		const u2 id = interfaces[i];
		const auto utf8 = Class;
		std::cout << "\t#" << i << ":" << id << "\t" << visitor.visit(id, &utf8)
				<< std::endl;
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
	std::cout << "fields_count:" << fields_count << std::endl;
}
