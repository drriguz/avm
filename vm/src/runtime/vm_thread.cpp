#include "vm/runtime/vm_thread.h"
#include "vm/interpreter.h"
#include "vm/thread_context.h"

#include <iostream>

using namespace avm;

VmThread::VmThread(const VmClass* entryClass, const VmMethod* entryMethod, VirtualMachine* jvm):
    _entryClass(entryClass),
    _entryMethod(entryMethod),
    _jvm(jvm),
    _pcRegister(0) {
    Frame *topFrame = new Frame(entryMethod->getMaxLocals(), entryMethod->getMaxStack(), entryClass->getRuntimeConstantPool());
    _vmStack.push(topFrame);
}

VmThread::~VmThread() {

}

void VmThread::execute() {
    Context context(_vmStack.currentFrame(), _jvm);
    Interpreter interpreter;
    while(true) {
        const Instruction* instruction = nextInstruction();
        if(instruction == nullptr)
            break;
        interpreter.invoke(&context, instruction);
        std::cout << "=>" << instruction->getOpcode() << std::endl;
    }
}

Frame* VmThread::currentFrame() {
    return _vmStack.currentFrame();
}
const VmClass* VmThread::currentClass() {
    return _entryClass;
}
const VmMethod* VmThread::currentMethod() {
    return _entryMethod;
}

const Instruction* VmThread::nextInstruction() {
    if(_pcRegister < _entryMethod->getInstructionsCount())
        return _entryMethod->getInstruction(_pcRegister++);
    else return nullptr;
}