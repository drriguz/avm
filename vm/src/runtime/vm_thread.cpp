#include "vm/runtime/vm_thread.h"

using namespace avm;

VmThread::VmThread(const VmClass* entryClass, const VmMethod* entryMethod):
_entryClass(entryClass),
_entryMethod(entryMethod),
_pcRegister(0){
    Frame *topFrame = new Frame(entryMethod->getMaxLocals(), entryMethod->getMaxStack(), entryClass->getRuntimeConstantPool());
    _vmStack.push(topFrame);
}

VmThread::~VmThread() {

}

Frame* VmThread::currentFrame() {
    return _vmStack.currentFrame();
}

const Instruction* VmThread::nextInstruction() {
    if(_pcRegister < _entryMethod->getInstructionsCount())
        return _entryMethod->getInstruction(_pcRegister++);
    else return nullptr;
 }