/*
 * Driver.h
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#ifndef SOURCES_EEPROM_S25FL1K_DRIVER_H_
#define SOURCES_EEPROM_S25FL1K_DRIVER_H_

#include "../AbstractDriver.h"
#include "Interfaces/SPICommunicationChannel.h"

namespace EEPROM { namespace S25FL1K {

	class Driver : public AbstractDriver
	{
		using VCCPin = OutputPort<Port>;

		enum Action
		{
			PAGE_PROGRAM = 0x2,			// solicita a escrita
			READ_DATA = 0x3,			// solicita a leitura
			WRITE_DISABLE = 0x4,		// solicita que a escrita seja desabilitada
			QUERY_WRITE_MODE = 0x5,		// pergunta se está em write enable ou write disable
			WRITE_ENABLE = 0x6,			// solicita que a escrita seja habilitada
			SECTOR_ERASE = 0x20			// solicita que um setor seja apagado
		};

		// tamanhos em bytes
		static constexpr uint16_t PAGE_SIZE = 256;
		static constexpr uint16_t SECTOR_SIZE = 4096;

	public:
		Driver(SPICommunicationChannel& communication_channel, VCCPin vcc_pin);

		bool store(uint32_t address, const uint8_t* data, uint16_t size) const override;

		bool read(uint32_t address, uint8_t* buffer, uint16_t size) const override;

		bool erase_sector(uint32_t address) const override;

		void turn_on() override;
		void turn_off() override;
		bool is_on() override;

	private:
		SPICommunicationChannel& communication_channel;
		VCCPin vcc_pin;
		bool on;

		void write(uint32_t address, const uint8_t* data, uint16_t size) const;

		void enable_and_write(uint32_t address, const uint8_t* data, uint16_t size) const;

		void check_page_offset_and_write(uint32_t address, const uint8_t* data, uint16_t size) const;

		void enable_write() const;

		void disable_write() const;

		bool is_write_enabled() const;
	};

}}

#endif /* SOURCES_EEPROM_S25FL1K_DRIVER_H_ */
