#include "vm/runtime/operand_stack.h"
#include "vm/exceptions.h"

using namespace avm;

OperandStack::OperandStack(int maxSize)
	:_maxSize(maxSize) {

}

OperandStack::~OperandStack() {

}

void OperandStack::checkStackSize(int valueSize) {
	int newSize = _variables.size() + valueSize;
	if(newSize > _maxSize)
		throw StackOutOfRangeException("Exceed max slot stack size");
}

void OperandStack::pushSingleByte(int32_t value){
	checkStackSize(1);
	uint32_t* uv = reinterpret_cast<uint32_t*>(&value);
	Slot slot = Slot(*uv);
	_variables.push(slot);
}

void OperandStack::pushDoubleByte(int64_t value) {
	checkStackSize(2);
	uint64_t* uv = reinterpret_cast<uint64_t*>(&value);
	Slot highBytes = Slot(*uv >> 32), 
		 lowBytes = Slot(*uv & 0xFFFFFFFF);
	_variables.push(highBytes);
	_variables.push(lowBytes);
}

int32_t OperandStack::popSingleByte() {
	Slot top = _variables.top();
	_variables.pop();
	uint32_t uv = top.getValue();
	int32_t* sv = reinterpret_cast<int32_t*>(&uv);
	return *sv;
}

int64_t OperandStack::popDoubleByte() {
	uint64_t lowBytes = _variables.top().getValue();
	_variables.pop();
	uint64_t highBytes = _variables.top().getValue();
	_variables.pop();
	uint64_t uv = (highBytes << 32) + lowBytes;
	return *reinterpret_cast<int64_t*>(&uv);
}

void OperandStack::pushByte(int8_t value){
	pushSingleByte(value);
}

void OperandStack::pushShort(int16_t value){
	pushSingleByte(value);
}

void OperandStack::pushInt(int32_t value){
	pushSingleByte(value);
}

void OperandStack::pushLong(int64_t value){
	pushDoubleByte(value);
}

void OperandStack::pushFloat(float value){
	int32_t* sv = reinterpret_cast<int32_t*>(&value);;
	pushSingleByte(*sv);
}

void OperandStack::pushDouble(double value){
	int64_t* sv = reinterpret_cast<int64_t*>(&value);
	pushDoubleByte(*sv);
}

void OperandStack::pushChar(uint16_t value){
	pushSingleByte(value);
}

int8_t OperandStack::popByte(){
	return popSingleByte();
}

int16_t OperandStack::popShort(){
	return popSingleByte();
}

int32_t OperandStack::popInt(){
	return popSingleByte();
}

int64_t OperandStack::popLong(){
	return popDoubleByte();
}

float OperandStack::popFloat(){
	int32_t sv = popSingleByte();
	return *reinterpret_cast<float*>(&sv);
}

double OperandStack::popDouble(){
	int64_t sv = popDoubleByte();
	return *reinterpret_cast<double*>(&sv);
}

uint16_t OperandStack::popChar(){
	return popSingleByte();
}