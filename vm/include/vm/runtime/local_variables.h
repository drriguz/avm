#ifndef _AVM_LOCAL_VARIABLES_H_
#define _AVM_LOCAL_VARIABLES_H_

#include "slot.h"
#include <vector>

namespace avm{

	class LocalVariables {
	public:
		LocalVariables(int size);
		virtual ~LocalVariables();
	public:
		void setByte(int i, int8_t value);
		void setShort(int i, int16_t value);
		void setInt(int i, int32_t value);
		void setLong(int i, int64_t value);
		void setFloat(int i, float value);
		void setDouble(int i, double value);
		void setChar(int i, uint16_t value); 
		int8_t getByte(int i);
		int16_t getShort(int i);
		int32_t getInt(int i);
		int64_t getLong(int i);
		float getFloat(int i);
		double getDouble(int i);
		uint16_t getChar(int i);
	protected:
		void checkRange(int i, int valueSize);
		void setSingleByte(int i, int32_t value);
		void setDoubleByte(int i, int64_t value);
		int32_t getSingleByte(int i);
		int64_t getDoubleByte(int i);
	protected:
		int _size;
		Slot** _variables;
	};
}
#endif