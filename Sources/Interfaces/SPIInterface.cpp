/*
 * SPIInterface.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#include "SPIInterface.h"

SPIInterface::SPIInterface(IDX idx, const Config& config)
: idx(idx), config(config)
{
}

void SPIInterface::send(const uint8_t* data, size_type size)
{
	SPI_DRV_MasterTransferBlocking(idx, &config, data, NULL, size, DEFAULT_TIMEOUT);
}

void SPIInterface::send(const AbstractByteBuffer& data)
{
	send(data.get(), data.length());
}

SPIInterface::size_type SPIInterface::read(uint8_t* buffer, size_type size)
{
	const auto ret = SPI_DRV_MasterTransferBlocking(idx, &config, NULL, buffer, size, DEFAULT_TIMEOUT);
	return (kStatus_SPI_Success == ret ? size : 0);
}

SPIInterface::size_type SPIInterface::read(AbstractByteBuffer& buffer, size_type size)
{
	return read(buffer.get(), size);
}
