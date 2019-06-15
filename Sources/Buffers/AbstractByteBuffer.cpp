/*
 * AbstractByteBuffer.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#include <string>
#include "Buffers/AbstractByteBuffer.h"
#include "fsl_debug_console.h"

using size_type = std::size_t;

AbstractByteBuffer::AbstractByteBuffer(const AbstractByteBuffer& other)
: _size(other._size), offset(other.offset), reset_value(other.reset_value)
{

}

AbstractByteBuffer& AbstractByteBuffer::operator=(const AbstractByteBuffer& other)
{
	_size = other._size;
	offset = other.offset;
	reset_value = other.reset_value;

	return *this;
}

bool AbstractByteBuffer::push_back(const uint8_t* data, size_type requested_size, bool use_rtt)
{
	if(isInBounds(requested_size))
	{
		memcpy(&get()[offset], data, requested_size);
		offset += requested_size;
		return true;
	}
	else
	{
		if(use_rtt)
		{

		}
		return false;
	}

}

bool AbstractByteBuffer::push_back(const AbstractByteBuffer& other, bool use_rtt)
{
	return push_back(other.get(), other.length(), use_rtt);
}

//size_type AbstractByteBuffer::length() const

bool AbstractByteBuffer::empty() const
{
	//	for(size_type i = 0; i < offset; i++)
	//	{
	//		if(get()[i] != reset_value)
	//		{
	//			return false;
	//		}
	//	}

	return offset == 0;
}

bool AbstractByteBuffer::full() const
{
	return offset == _size;
}

void AbstractByteBuffer::clear()
{
	offset = 0;
}

bool AbstractByteBuffer::push_back(uint8_t byte, bool use_rtt)
{
	return push_back(&byte, sizeof(byte), use_rtt);
}

bool AbstractByteBuffer::slow_is_filled_with(uint8_t byte, uint16_t length)
{
	if(length > size())
	{
		return false;
	}

	for(uint16_t i = 0; i < length; i++)
	{
		if(this->operator [](i) != byte)
		{
			return false;
		}
	}

	return true;
}
//constexpr size_type AbstractByteBuffer::size() const

//constexpr bool AbstractByteBuffer::isInBounds(size_type requested_size) const
