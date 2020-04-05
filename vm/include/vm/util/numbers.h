#ifndef _AVM_NUMBER_UTIL_H_
#define _AVM_NUMBER_UTIL_H_

#include <cstdint>
#include <tuple>

namespace avm {
	class Numbers {
	public:
		static std::tuple<uint32_t, uint32_t> splitLong(int64_t value);
		static std::tuple<uint32_t, uint32_t> splitDouble(double value);
		static int64_t asLong(uint32_t highBytes, uint32_t lowBytes);
		static double asDouble(uint32_t highBytes, uint32_t lowBytes);
	};
}
#endif