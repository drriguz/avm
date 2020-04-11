#include "vm/runtime/vm_thread.h"

using namespace avm;

VmThread::VmThread(const VmClass* entryClass, const VmMethod* entryMethod):
_entryClass(entryClass),
_entryMethod(entryMethod){
    Frame *topFrame = new Frame(entryMethod->getMaxLocals(), entryMethod->getMaxStack(), entryClass->getRuntimeConstantPool());
    _vmStack.push(topFrame);
}

VmThread::~VmThread() {

}