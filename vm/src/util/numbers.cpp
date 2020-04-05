#include "vm/util/numbers.h"

using namespace avm;

std::tuple<uint32_t, uint32_t> Numbers::splitLong(int64_t value) {
	uint64_t* uv = reinterpret_cast<uint64_t*>(&value);
	uint32_t highBytes = *uv >> 32, lowBytes = *uv & 0xFFFFFFFF;
	return std::make_tuple (highBytes, lowBytes);
}

std::tuple<uint32_t, uint32_t> Numbers::splitDouble(double value) {
	int64_t* sv = reinterpret_cast<int64_t*>(&value);
	return splitLong(*sv);
}

int64_t Numbers::asLong(uint32_t highBytes, uint32_t lowBytes){
	uint64_t uv = (((uint64_t)highBytes) << 32) + lowBytes;
	return *reinterpret_cast<int64_t*>(&uv);
}

double Numbers::asDouble(uint32_t highBytes, uint32_t lowBytes){
	uint64_t uv = (((uint64_t)highBytes) << 32) + lowBytes;
	return *reinterpret_cast<double*>(&uv);
}