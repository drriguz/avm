#ifndef _AVM_SLOT_H_
#define _AVM_SLOT_H_

#include <cstdint>

namespace avm{

	class Slot {
	public:
		Slot(uint32_t value);
		Slot(const Slot& p);
		virtual ~Slot();
	public:
		inline uint32_t getValue() const {
			return _value;
		}
	protected:
		const uint32_t _value;
	};
}
#endif