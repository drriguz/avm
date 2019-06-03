#include "format/class_file.h"
#include <iostream>

using namespace avm;

void ClassFile::verbose() {
	std::cout << "magic:0x" << std::hex << int(this->magic) << std::endl
			<< std::dec << "minor_version:" << this->minor_version << std::endl
			<< "major_version:" << this->major_version << std::endl
			<< "constant_pool_count:" << this->constant_pool_count << std::endl;
}
