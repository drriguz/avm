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
		inline int32_t asLong() const {
			uint32_t copy = _value;
			return *reinterpret_cast<int32_t*>(&copy);
		}

		inline float asFloat() const {
			uint32_t copy = _value;
			return *reinterpret_cast<float*>(&copy);
		}
	protected:
		const uint32_t _value;
	};
}
#endif