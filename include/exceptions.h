#ifndef _AVM_EXCEPTIONS_H_
#define _AVM_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace avm {

	class RuntimeException : public std::exception {
	public:
		RuntimeException(const std::string &msg) : message(msg) {
		}
		const virtual char *what() const throw() {
			return message.c_str();
		}

	private:
		std::string message;
	};
	class NotClassFileException : public RuntimeException {
	public:
		NotClassFileException(const std::string &msg) : RuntimeException(msg) {
		}
	};
	class OpenFileException : public RuntimeException {
	public:
		OpenFileException(const std::string &msg) : RuntimeException(msg) {
		}
	};

	class ReadFileException : public RuntimeException {
	public:
		ReadFileException(const std::string &msg) : RuntimeException(msg) {
		}
	};

	class ClassFormatException : public RuntimeException {
	public:
		ClassFormatException(const std::string &msg) : RuntimeException(msg) {
		}
	};

} // namespace avm
#endif
