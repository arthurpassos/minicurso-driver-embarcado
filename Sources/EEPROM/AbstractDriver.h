/*
 * AbstractDriver.h
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#ifndef SOURCES_EEPROM_ABSTRACTDRIVER_H_
#define SOURCES_EEPROM_ABSTRACTDRIVER_H_

#include "Buffers/AbstractByteBuffer.h"
#include "Utils/IPowerable.h"

namespace EEPROM
{
	class AbstractDriver : public IPowerable
	{
	public:
		constexpr AbstractDriver() = default;
		virtual ~AbstractDriver() = default;

		virtual bool store(uint32_t address, const uint8_t* data, uint16_t size) const = 0;
		virtual bool store(uint32_t address, const AbstractByteBuffer& data) const;

		virtual bool read(uint32_t address, uint8_t* buffer, uint16_t size) const = 0;
		virtual bool read(uint32_t address, const AbstractByteBuffer& buffer, uint16_t size) const;

		virtual bool erase_sector(uint32_t address) const = 0;
	};

} /* namespace EEPROM */

#endif /* SOURCES_EEPROM_ABSTRACTDRIVER_H_ */
