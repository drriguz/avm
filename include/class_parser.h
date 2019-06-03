#ifndef _AVM_CLASS_PARSER_H_
#define _AVM_CLASS_PARSER_H_

namespace avm {
class ClassFile;
class ClassParser {
public:
	ClassFile parse(const char* file) const;
};
}

#endif
