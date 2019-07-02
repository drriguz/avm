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

void ConstantVisitor::verbose() {
	for (int i = 1; i < constant_pool_count; i++) {
		ConstantInfo info = constant_pool[i];
		const ConstantTypes type = static_cast<ConstantTypes>(info.tag);
		if (type == Long || type == Double)
			i++;
		std::string id = "#" + std::to_string(i) + " = ";
		std::cout << std::right << std::setw(10) << id;
		std::cout << std::left << std::setw(20) << getConstantTypeName(type);

		std::cout << visit(i);
		std::cout << std::endl;
	}
}
std::string ConstantVisitor::visit(const u2& constantId,
		const ConstantTypes* expected) const {
	const auto utf8 = Utf8;
	if (constantId < 1 || constantId >= this->constant_pool_count)
		throw ClassFormatException(
				"ConstantId out of range" + std::to_string(constantId));
	const ConstantInfo info = this->constant_pool[constantId];
	const ConstantTypes type = static_cast<ConstantTypes>(info.tag);
	if (expected && type != *expected)
		throw ClassFormatException(
				"Constant is not expected:" + std::to_string(type)
						+ " Expected is:" + std::to_string(*expected));
	const u1* payload = info.info;
	switch (type) {
	case Class: {
		const ConstantClass* classInfo = (const ConstantClass*) payload;

		return "#" + std::to_string(classInfo->name_index) + "\t//"
				+ visit(classInfo->name_index, &utf8);
	}
	case Fieldref:
		break;
	case Methodref: {
		const ConstantMethodref* methodRef = (const ConstantMethodref*) payload;
		const ConstantTypes c1 = Class;
		const ConstantTypes c2 = NameAndType;
		return methodRef->toString() + "\t// "
				+ visit(methodRef->class_index, &c1) + "."
				+ visit(methodRef->name_and_type_index, &c2);
	}
	case InterfaceMethodref:
		// TODO:
		break;
	case String: {
		const ConstantString* string = (const ConstantString*) payload;
		return "#" + std::to_string(string->string_index) + "\t//"
				+ visit(string->string_index, &utf8);
	}
	case Integer: {
		const ConstantInteger* integer = (const ConstantInteger*) payload;
		return std::to_string(static_cast<int>(integer->bytes));
	}
	case Float: {
		const ConstantFloat* floatNum = (const ConstantFloat*) payload;
		return std::to_string(floatNum->getValue());
	}
	case Long:
		break;
	case Double:
		break;
	case NameAndType: {
		const ConstantNameAndType* nameAndType =
				(const ConstantNameAndType*) payload;
		return visit(nameAndType->name_index, &utf8) + ":"
				+ visit(nameAndType->descriptor_index, &utf8);
	}
	case Utf8: {
		const ConstantUtf8* utf8Info = (const ConstantUtf8*) payload;
		return std::string(reinterpret_cast<const char*>(utf8Info->bytes));
	}
	case MethodHandle:
		break;
	case MethodType:
		break;
	case InvokeDynamic:
		break;
	default:
		return "";
	}
}

