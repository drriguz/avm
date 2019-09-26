#include "class_parser.h"
#include "exceptions.h"
#include "format/class_file.h"
#include "spdlog/spdlog.h"

#include <iostream>
using namespace std;
using namespace avm;

int main(int argc, char *argv[]) {
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Java class parser v{}", 0.1f);

	avm::ClassParser parser("test/resources/Complex.class");

	try {
		ClassFile parsed = parser.parse();
		parsed.verbose();
		spdlog::info(parsed.getMajorVersion());
	} catch (RuntimeException &ex) {
		spdlog::error(ex.what());
	}

	return 1;
}
