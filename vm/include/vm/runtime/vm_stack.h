#ifndef _AVM_VM_STACK_H_
#define _AVM_VM_STACK_H_

#include <stack>

#include "frame.h"

namespace avm{

	class VmStack {
	public:
		VmStack();
		virtual ~VmStack();
	protected:
		std::stack<Frame> _frames;
	};
}
#endif