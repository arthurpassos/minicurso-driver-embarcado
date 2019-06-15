/*
 * StaticByteBuffer.h
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#ifndef BUFFERS_STATICBYTEBUFFER_H_
#define BUFFERS_STATICBYTEBUFFER_H_

#include <stddef.h>
#include "AbstractByteBuffer.h"
#include "Utils/Utils.h"

template <const std::size_t SIZE>
class StaticByteBuffer : public AbstractByteBuffer {
public:
    constexpr StaticByteBuffer(uint8_t reset_value = 0) : AbstractByteBuffer(SIZE, reset_value)
	{
    	Utils::memset(buffer, reset_value, SIZE);
	}

    StaticByteBuffer(const StaticByteBuffer& other)
    : AbstractByteBuffer(other)
    {
    	memcpy(buffer, other.buffer, SIZE);
    }

    StaticByteBuffer(StaticByteBuffer&& other) = delete;

    StaticByteBuffer& operator=(const StaticByteBuffer& other)
    {
    	memcpy(buffer, other.buffer, SIZE);
    	AbstractByteBuffer::operator =(other);

    	return *this;
    }

    StaticByteBuffer& operator=(StaticByteBuffer&& other) = delete;

    uint8_t *get() const override {
        return (uint8_t*) buffer;
    }

private:
    uint8_t buffer[SIZE];
};



#endif /* BUFFERS_STATICBYTEBUFFER_H_ */
