#include "vm/runtime/vm_thread.h"

using namespace avm;

VmThread::VmThread(const VmClass* entryClass, const VmMethod* entryMethod):
_entryClass(entryClass),
_entryMethod(entryMethod){

}

VmThread::~VmThread() {

}