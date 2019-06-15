/*
 * DynamicByteBuffer.h
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#ifndef BUFFERS_DYNAMICBYTEBUFFER_H_
#define BUFFERS_DYNAMICBYTEBUFFER_H_

#include <memory>
#include "Buffers/AbstractByteBuffer.h"

class DynamicByteBuffer: public AbstractByteBuffer {
public:
	using size_type = std::size_t;
	DynamicByteBuffer(size_type size, size_type reset_value = 0);
private:
	std::unique_ptr<uint8_t[]> buffer;
};

#endif /* BUFFERS_DYNAMICBYTEBUFFER_H_ */
