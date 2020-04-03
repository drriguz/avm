#ifndef _AVM_STRINGS_H_
#define _AVM_STRINGS_H_

#include <string>

namespace avm {

class Strings {
private:
	Strings();
public:
	static std::string replaceAll(const std::string& source,
			const std::string& match,
			const std::string& replacement);
};
}

#endif
