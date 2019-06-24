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

		enum InstructionCode
		{
			WRITE_ENABLE = 0x6,			// solicita que a escrita seja habilitada
		};

		// tamanhos em bytes
		static constexpr uint16_t PAGE_SIZE = 256;
		static constexpr uint16_t SECTOR_SIZE = 4096;
		static constexpr uint8_t WRITE_ENABLED_MASK = 0b10;

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
