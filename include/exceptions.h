
#ifndef _AVM_EXCEPTIONS_H_
#define _AVM_EXCEPTIONS_H_

#include <exception>

namespace avm {
class OpenFileException: public std::exception{};
class ClassFormatException: public std::exception{};
}
#endif
