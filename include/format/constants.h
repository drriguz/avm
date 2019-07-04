#ifndef _AVM_CONSTANTS_H_
#define _AVM_CONSTANTS_H_

#include "types.h"
#include <iostream>
#include <string>

namespace avm {
	enum ConstantTypes {
		Class = 7,
		Fieldref = 9,
		Methodref = 10,
		InterfaceMethodref = 11,
		String = 8,
		Integer = 3,
		Float = 4,
		Long = 5,
		Double = 6,
		NameAndType = 12,
		Utf8 = 1,
		MethodHandle = 15,
		MethodType = 16,
		InvokeDynamic = 18,
	};

	class ConstantInfo {
		friend class ClassParser;
		friend class ClassFile;
		friend class ConstantVisitor;

	public:
		ConstantInfo() : tag(), info(nullptr) {
		}
		ConstantInfo(const ConstantTypes &t, u1 *i) : tag(t), info(i) {
		}
		~ConstantInfo() {
		}

	private:
		ConstantTypes tag;
		u1 *info;
	};

	struct ConstantClass {
		u2 name_index;
	};

	struct ConstantFieldref {
		u2 class_index;
		u2 name_and_type_index;
	};

	struct ConstantMethodref {
		u2 class_index;
		u2 name_and_type_index;
		std::string toString() const {
			return "#" + std::to_string(class_index) + ".#" + std::to_string(name_and_type_index);
		}
	};

	struct ConstantInterfaceMethodref {
		u2 class_index;
		u2 name_and_type_index;
	};

	struct ConstantString {
		u2 string_index;
	};

	struct ConstantInteger {
		u4 bytes;
	};

	struct ConstantFloat {
		mutable u4 bytes;
		float &getValue() const {
			return *reinterpret_cast<float *>(&bytes);
		}
	};

	struct ConstantLong {
		mutable u4 high_bytes;
		mutable u4 low_bytes;
		long getValue() const {
			return ((long)high_bytes << 32) + low_bytes;
		}
	};

	struct ConstantDouble {
		mutable u4 high_bytes;
		mutable u4 low_bytes;
		double getValue() const {
			long value = ((long)high_bytes << 32) + low_bytes;
			return *reinterpret_cast<double *>(&value);
		}
	};

	struct ConstantNameAndType {
		u2 name_index;
		u2 descriptor_index;
	};

	class ConstantUtf8 {
		friend class ClassParser;
		friend class ConstantVisitor;

	public:
		ConstantUtf8() : length(0), bytes(nullptr) {
		}
		~ConstantUtf8() {
			if (bytes)
				delete[] bytes;
		}

	public:
		void ensureStringBuffer() {
			if (bytes)
				delete[] bytes;
			bytes = new u1[length + 1];
		}

	private:
		u2 length;
		u1 *bytes;
	};

	struct ConstantMethodHandle {
		u1 tag;
		u1 reference_kind;
		u2 reference_index;
	};

	struct ConstantMethodType {
		u1 tag;
		u2 descriptor_index;
	};

	struct ConstantInvokeDynamic {
		u1 tag;
		u2 bootstrap_method_attr_index;
		u2 name_and_type_index;
	};
} // namespace avm

#endif
