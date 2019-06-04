#include "exceptions.h"

#include <iostream>
#include <iomanip>

#include "spdlog/spdlog.h"

#include "format/constant_visitor.h"

using namespace avm;

ConstantVisitor::ConstantVisitor(const u2&count, const ConstantInfo* pool) :
		constant_pool_count(count), constant_pool(pool) {

}

ConstantVisitor::~ConstantVisitor() {

}

std::string ConstantVisitor::getConstantTypeName(
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

void ConstantVisitor::verbose(const ConstantTypes& type, const u1* info) {
	switch (type) {
	case Class: {
		ConstantClass* classInfo = (ConstantClass*) info;
		std::cout << "#" << classInfo->name_index;
		break;
	}
	case Fieldref:
		break;
	case Methodref: {
		ConstantMethodref* methodRef = (ConstantMethodref*) info;
		const ConstantTypes c1 = Class;
		const ConstantTypes c2 = NameAndType;
		std::cout << methodRef->toString() << "\t// "
				<< visit(methodRef->class_index, &c1) << "."
				<< visit(methodRef->name_and_type_index, &c2);
		break;
	}
	case InterfaceMethodref:
		break;
	case String: {
		ConstantString* string = (ConstantString*) info;
		std::cout << "#" << string->string_index;
		break;
	}
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
void ConstantVisitor::verbose() {
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
std::string ConstantVisitor::visit(const u2& constantId,
		const ConstantTypes* expected = nullptr) const {
	if (constantId < 1 || constantId >= this->constant_pool_count)
		throw ClassFormatException(
				"ConstantId out of range" + std::to_string(constantId));
	const ConstantInfo info = this->constant_pool[constantId];
	const ConstantTypes type = static_cast<ConstantTypes>(info.tag);
	if (expected && type != *expected)
		throw ClassFormatException(
				"Constant is not expected:" + std::to_string(type)
						+ " Expected is:" + std::to_string(*expected));
	switch (type) {
	case Class: {
		const ConstantClass* classInfo = (const ConstantClass*) info.info;
		const auto expected = Utf8;
		return visit(classInfo->name_index, &expected);
	}
	case NameAndType: {
		const ConstantNameAndType* nameAndType =
				(const ConstantNameAndType*) info.info;
		const auto expected = Utf8;
		return visit(nameAndType->name_index, &expected) + ":"
				+ visit(nameAndType->descriptor_index, &expected);
	}
	case Utf8: {
		const ConstantUtf8* utf8Info = (const ConstantUtf8*) info.info;
		return std::string(reinterpret_cast<const char*>(utf8Info->bytes));
	}
	default:
		return "";
	}
}

