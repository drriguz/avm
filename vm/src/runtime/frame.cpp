#include "vm/runtime/frame.h"

using namespace avm;

Frame::Frame()
:_operandStack(nullptr){
}

Frame::~Frame(){
	if(_operandStack) {
		delete _operandStack;
		_operandStack = nullptr;
	}
}