#include "vm/interpreter.h"
#include <iostream>

using namespace avm;

Interpreter::Interpreter(){

}

Interpreter::~Interpreter(){

}

void Interpreter::execute(VmThread* thread){
    while(true) {
        const Instruction* instruction = thread->nextInstruction();
        if(instruction == nullptr)
            break;
        invoke(thread->currentClass()->getRuntimeConstantPool(), instruction, thread->currentFrame());
        std::cout << "=>" << instruction->getOpcode() << std::endl;
    }
}

void Interpreter::invoke(const ConstantPool* runtimeConstantPool, const Instruction* instruction, Frame* frame) {
    OperandStack* oprandStack = frame->getOperandStack();
    LocalVariables* localVariables = frame->getLocalVariables();
    switch(instruction->getOpcode()) {
        case j_iconst_1:{
            oprandStack->pushInt(1);
            break;
        }
        case j_iconst_2:{
            oprandStack->pushInt(2);
            break;
        }
        case j_istore_1:{
            localVariables->setInt(1, oprandStack->popInt());
            break;
        }
        case j_istore_2:{
            localVariables->setInt(2, oprandStack->popInt());
            break;
        }
        case j_istore_3:{
            localVariables->setInt(3, oprandStack->popInt());
            break;
        }
        case j_iload_1:{
            oprandStack->pushInt(localVariables->getInt(1));
            break;
        }
        case j_iload_2:{
            oprandStack->pushInt(localVariables->getInt(2));
            break;
        }
        case j_iload_3:{
            oprandStack->pushInt(localVariables->getInt(3));
            break;
        }
        case j_iadd:{
            int32_t i1 = oprandStack->popInt();
            int32_t i2 = oprandStack->popInt();
            oprandStack->pushInt(i1 + i2);
            break;
        }
        case j_getstatic:{
            // FIXME:
            u2 index = instruction->getOprandAsU2();
            std::cout << "get_static #" << index << std::endl;
            oprandStack->pushInt(-1);
            break;
        }
        case j_invokevirtual: {
            u2 index = instruction->getOprandAsU2();
            std::cout << "invoke_virtual #" << index << std::endl;
            break;
        }
        case j_return: {
            frame->returnVoid();
            break;
        }
        default:
            break;
    }
}