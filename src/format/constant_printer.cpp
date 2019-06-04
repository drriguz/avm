#include "format/constant_printer.h"
#include "exceptions.h"

#include <iostream>
#include <iomanip>

using namespace avm;

ConstantPrinter::ConstantPrinter(const u2&count, const ConstantInfo* pool) :
		constant_pool_count(count), constant_pool(pool) {

}

ConstantPrinter::~ConstantPrinter() {

}

std::string ConstantPrinter::getConstantTypeName(
		const ConstantTypes& type) const {
	switch (type) {
	case Class:
		return "Class";
	case Fieldref:
		return "Fieldref";
	case Methodref:
		return "Methodref";
	case InterfaceMethodref:
		return "InterfaceMethodref";
	case String:
		return "String";
	case Integer:
		return "Integer";
	case Float:
		return "Float";
	case Long:
		return "Long";
	case Double:
		return "Double";
	case NameAndType:
		return "NameAndType";
	case Utf8:
		return "Utf8";
	case MethodHandle:
		return "MethodHandle";
	case MethodType:
		return "MethodType";
	case InvokeDynamic:
		return "InvokeDynamic";
	default:
		return "";
	}
}

void ConstantPrinter::verbose(const u2& utf8Id) {
	if (utf8Id < 1 || utf8Id >= this->constant_pool_count)
		throw ClassFormatException("Invalid utf8 id");
	const ConstantInfo info = this->constant_pool[utf8Id];
	const ConstantTypes type = static_cast<ConstantTypes>(info.tag);
	if (type != Utf8)
		throw ClassFormatException("Id should be a index of utf8");
	std::cout << ((const ConstantUtf8&) info).bytes;
}

void ConstantPrinter::verbose(const ConstantTypes& type, const u1* info) {
	switch (type) {
	case Class:
		break;
	case Fieldref:
		break;
	case Methodref: {
		ConstantMethodref* methodRef = (ConstantMethodref*) info;
		std::cout << methodRef->toString();
		verbose(methodRef->class_index);
		break;
	}
	case InterfaceMethodref:
		break;
	case String:
		break;
	case Integer:
		break;
	case Float:
		break;
	case Long:
		break;
	case Double:
		break;
	case NameAndType:
		break;
	case Utf8: {
		const ConstantUtf8* utf8Info = (ConstantUtf8*) info;
		std::cout << utf8Info->bytes;
		break;
	}
	case MethodHandle:
		break;
	case MethodType:
		break;
	case InvokeDynamic:
		break;
	default:
		break;
	}
}
void ConstantPrinter::verbose() {
	for (int i = 1; i < constant_pool_count; i++) {
		ConstantInfo info = constant_pool[i];
		const ConstantTypes type = static_cast<ConstantTypes>(info.tag);
		if (type == Long || type == Double)
			i++;
		std::string id = "#" + std::to_string(i) + " = ";
		std::cout << std::right << std::setw(10) << id;
		std::cout << std::left << std::setw(20) << getConstantTypeName(type);
		verbose(type, info.info);
		std::cout << std::endl;
	}
}

