/*
 * SPIInterface.h
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#ifndef SOURCES_INTERFACES_SPIINTERFACE_H_
#define SOURCES_INTERFACES_SPIINTERFACE_H_

#include "Interfaces/Interface.h"
#include "fsl_spi_master_driver.h"

class SPIInterface final : public Interface
{
	using IDX = uint32_t;
	using Config = spi_master_user_config_t;

public:
	SPIInterface(IDX idx, const Config& config);

    void send(const uint8_t* data, size_type size) override;
    void send(const AbstractByteBuffer& data) override;

    size_type read(uint8_t* buffer, size_type size) override;
    size_type read(AbstractByteBuffer& buffer, size_type size) override;

private:
    IDX idx;
    Config config;

    static constexpr uint8_t DEFAULT_TIMEOUT = 100;
};

#endif /* SOURCES_INTERFACES_SPIINTERFACE_H_ */
