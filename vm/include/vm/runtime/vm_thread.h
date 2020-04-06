#ifndef _AVM_VM_THREAD_H_
#define _AVM_VM_THREAD_H_

#include "program_counter_register.h"
#include "vm_stack.h"

namespace avm{

	class VmThread {
	public:
		VmThread();
		virtual ~VmThread();
	protected:
		ProgramCounterRegister _pcRegister;
		VmStack _vmStack;
	};
}
#endif