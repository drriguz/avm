#include "gtest/gtest.h"

#include "vm/util/numbers.h"

#include "vm/exceptions.h"

using namespace avm;

TEST(Numbers, splitLong) {
	uint32_t h, l;
	std::tie (h, l) = Numbers::splitLong(102421231208098);
	int64_t x = Numbers::asLong(h, l);
	ASSERT_EQ(102421231208098, x);
}

TEST(Numbers, splitDouble) {
	uint32_t h, l;
	std::tie (h, l) = Numbers::splitDouble(102421231208098.12345);
	double x = Numbers::asDouble(h, l);
	ASSERT_EQ(102421231208098.12345, x);
}