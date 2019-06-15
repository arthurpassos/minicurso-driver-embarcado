/*
 * Interface.h
 *
 *  Created on: Feb 27, 2019
 *      Author: PC
 */

#ifndef INTERFACES_INTERFACE_H_
#define INTERFACES_INTERFACE_H_


#include <cstdint>
#include <cstddef>
#include "../Buffers/AbstractByteBuffer.h"
#include "Utils/IPowerable.h"

class Interface
{
public:
	virtual ~Interface() = default;

	using size_type = std::size_t;

    virtual void send(const uint8_t* data, size_type size) = 0;
    virtual void send(const AbstractByteBuffer& data) = 0;

    virtual size_type read(uint8_t* buffer, size_type size) = 0;
    virtual size_type read(AbstractByteBuffer& buffer, size_type size) = 0;
};


#endif /* INTERFACES_INTERFACE_H_ */
