#include "format/constant/constant_info.h"

using namespace avm;

ConstantInfo::ConstantInfo()
:_type(Utf8), _size(0), _info(nullptr){

}

ConstantInfo::ConstantInfo(const ConstantType& type, const u1* info, const u2& size)
:_type(type), _size(size){
	_info = new u1[_size];
	std::copy_n(info, size, _info);
}

ConstantInfo::ConstantInfo(const ConstantInfo& p){
	_type = p._type;
	_size = p._size;
	if(p._info != nullptr) {
		_info = new u1[_size];
		std::copy_n(p._info, _size, _info);
	} else {
		_info = nullptr;
	}
}

ConstantInfo::~ConstantInfo(){
	clear();
}

void ConstantInfo::clear() {
	if(_info){
		delete[] _info;
		_info = nullptr;
	}
}

void ConstantInfo::initialize(const u1* info, u2 size){
	clear();
	_info = new u1[_size];
	std::copy_n(info, size, _info);
}
