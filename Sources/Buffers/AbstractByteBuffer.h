/*
 * AbstractByteBuffer.h
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#ifndef BUFFERS_ABSTRACTBYTEBUFFER_H_
#define BUFFERS_ABSTRACTBYTEBUFFER_H_

#include <cstdint>
#include <cstddef>
#include <string.h>
//#include "Utils/Utils.h"

class AbstractByteBuffer {
public:
    using size_type = uint16_t;

    constexpr AbstractByteBuffer(size_type p_size, uint8_t reset_value = 0x0)
            : _size(p_size), offset(0), reset_value(reset_value)
    {
    }

    virtual ~AbstractByteBuffer() = default;

	AbstractByteBuffer(const AbstractByteBuffer& other);
    AbstractByteBuffer(AbstractByteBuffer&& other) = delete;

    AbstractByteBuffer& operator=(const AbstractByteBuffer& other);
    AbstractByteBuffer& operator=(AbstractByteBuffer&& other) = delete;

    virtual bool push_back(const uint8_t* data, size_type requested_size, bool use_rtt = true);

    virtual bool push_back(const AbstractByteBuffer& other, bool use_rtt = true);

    virtual bool push_back(uint8_t byte, bool use_rtt = true);

    constexpr size_type length() const
    {
    	return offset;
    }

    bool slow_is_filled_with(uint8_t byte, uint16_t length);

    virtual void clear();

    virtual bool empty() const;

    virtual bool full() const;

    constexpr size_type size() const
    {
    	return _size;
    }

    constexpr bool isInBounds(size_type requested_size) const
    {
    	return requested_size + offset <= _size;
    }

	uint8_t operator[](uint16_t i) const
	{
		return get()[i];
	}

	uint8_t& operator[](uint16_t i)
	{
		return get()[i];
	}

    virtual uint8_t* get() const = 0;

private:
    size_type _size;
    size_type offset;
    size_type reset_value;
};

#endif /* BUFFERS_ABSTRACTBYTEBUFFER_H_ */
