/*
 * DynamicByteBuffer.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#include "Buffers/DynamicByteBuffer.h"

DynamicByteBuffer::DynamicByteBuffer(size_type size, size_type reset_value)
: AbstractByteBuffer(size, reset_value), buffer(std::make_unique<uint8_t[]>(size))
{
}
