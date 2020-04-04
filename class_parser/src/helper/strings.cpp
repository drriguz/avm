#include "class_file/helper/strings.h"
using namespace avm;

Strings::Strings(){

}


std::string Strings::replaceAll(const std::string& source,
		const std::string& match,
		const std::string& replacement){
	std::string str = source;
	std::string::size_type i = str.find(match);
	std::string::size_type matchLength = match.length();
	while(i != std::string::npos) {
		str.replace(i, matchLength, replacement);
		i = str.find(match);
	}
	return str;
}
