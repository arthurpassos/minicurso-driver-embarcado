/*
 * Driver.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#include "Driver.h"
#include "Utils/Utils.h"

namespace EEPROM { namespace S25FL1K {

	Driver::Driver(SPICommunicationChannel& communication_channel, VCCPin vcc_pin)
	: communication_channel(communication_channel), vcc_pin(vcc_pin), on(false)
	{
	}

	bool Driver::store(uint32_t address, const uint8_t* data, uint16_t size) const
	{
		check_page_offset_and_write(address, data, size);
		return true;
	}

	bool Driver::read(uint32_t address, uint8_t* buffer, uint16_t size) const
	{

		// 1) crie um buffer (vetor) contendo
		// o c�digo de instru��o e o endere�o formatado
		// de acordo com a especifica��o no manual

		// 2) ative o chip/ slave (DOWN) pelo canal de comunica��o

		// 3) envie o comando pelo canal de comunica��o

		// 4) leia do canal de comunica��o utilizando seu buffer

		// 5) desative o chip/ slave (UP) pelo canal de comunica��o

		return true;
	}

	bool Driver::erase_sector(uint32_t address) const
	{
		enable_write();

		// 1) crie um buffer (vetor) contendo
		// o c�digo de instru��o e o endere�o formatado
		// de acordo com a especifica��o no manual

		// 2) ative o chip/ slave (DOWN) pelo canal de comunica��o

		// 3) envie o comando pelo canal de comunica��o

		// 4) desative o chip/ slave (UP) pelo canal de comunica��o

		// 5)
		// while(is_write_enabled())
		// {
		// 	Utils::delay(3);
		//}

		return true;
	}

	void Driver::turn_on()
	{
		vcc_pin.clear();
		Utils::delay(100);
		on = true;
	}

	void Driver::turn_off()
	{
		vcc_pin.set();
		Utils::delay(100);
		on = false;
	}

	bool Driver::is_on()
	{
		return on;
	}

	void Driver::check_page_offset_and_write(uint32_t address, const uint8_t* data, uint16_t size) const
	{
		uint32_t offset = 0;
		uint16_t page_size = 0;

		while (offset < size)
		{
			const uint32_t offseted_address = address + offset;
			page_size = PAGE_SIZE - (offseted_address % PAGE_SIZE);

			if (offset + page_size > size)
			{
				page_size = size - offset;
			}

			enable_and_write(offseted_address, &data[offset], page_size);

			offset += page_size;
		}
	}

	void Driver::write(uint32_t address, const uint8_t* data, uint16_t size) const
	{
		// 1) crie um buffer (vetor) contendo
		// o c�digo de instru��o e o endere�o formatado
		// de acordo com a especifica��o no manual

		// 2) ative o chip/ slave (DOWN) pelo canal de comunica��o

		// 3) envie o comando pelo canal de comunica��o

		// 4) envie o dado pelo canal de comunica��o

		// 5) desative o chip/ slave (UP) pelo canal de comunica��o
	}

	void Driver::enable_write() const
	{
		// utilizo apenas um byte porque meu comando � de apenas um byte,
		// mas se meu comando tivesse argumentos (como o de escrita ou leitura),
		// eu poderia utilizar um vetor, por exemplo.
		const uint8_t write_enable_command = InstructionCode::WRITE_ENABLE;

		// aviso o slave (mem�ria) que vou falar com ela
		communication_channel.CS_DOWN();

		// envio o comando
		communication_channel.send(&write_enable_command, sizeof(write_enable_command));

		// aviso o slave (mem�ria) que terminei de falar com ela
		communication_channel.CS_UP();

		// aguardo a escrita ser habilitada
		while(!is_write_enabled())
		{
			Utils::delay(3);
		}
	}

	void Driver::disable_write() const
	{
		const uint8_t write_disable_command = InstructionCode::WRITE_DISABLE;

		communication_channel.CS_DOWN();

		communication_channel.send(&write_disable_command, sizeof(write_disable_command));

		communication_channel.CS_UP();
	}

	void Driver::enable_and_write(uint32_t address, const uint8_t* data, uint16_t size) const
	{
		enable_write();

		write(address, data, size);

		while(is_write_enabled())
		{
			Utils::delay(3);
		}
	}

	bool Driver::is_write_enabled() const
	{
//		uint8_t response = 0xFF;
//		const InstructionCode instruction_code; // = c�digo correspondente no ENUM/ manual.

		// 1) crie um comando contendo
		// 	o c�digo de instru��o de acordo com a especifica��o no manual

		// 2) ative o chip/ slave (DOWN) pelo canal de comunica��o

		// 3) envie o comando pelo canal de comunica��o

		// 4) leia a resposta pelo canal de comunica��o (apenas um byte de resposta)

		// 5) desative o chip/ slave (UP) pelo canal de comunica��o

		// 6) verifique o n�vel (ligado ou desligado) do bit correspondente
		// ao status de escrita retornado na resposta.

		// 7) retorne o resultado
	}


}}
