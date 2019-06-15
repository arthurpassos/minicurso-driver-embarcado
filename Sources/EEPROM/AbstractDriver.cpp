/*
 * AbstractDriver.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#include "AbstractDriver.h"

namespace EEPROM
{
	bool AbstractDriver::store(uint32_t address, const AbstractByteBuffer& data) const
	{
		return store(address, data.get(), data.length());
	}

	bool AbstractDriver::read(uint32_t address, const AbstractByteBuffer& buffer, uint16_t size) const
	{
		return buffer.size() >= size ? read(address, buffer.get(), size) : false;
	}
} /* namespace EEPROM */
