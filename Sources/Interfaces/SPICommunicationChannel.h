/*
 * SPICommunicationChannel.h
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#ifndef SOURCES_INTERFACES_SPICOMMUNICATIONCHANNEL_H_
#define SOURCES_INTERFACES_SPICOMMUNICATIONCHANNEL_H_

#include "SPIInterface.h"
#include "Ports.h"

// Decorator pattern para SPIInterface.

class SPICommunicationChannel : Interface
{
	using ChipSelectPin = OutputPort<Port>;
public:
	SPICommunicationChannel(SPIInterface& interface, ChipSelectPin cs_pin);

    void send(const uint8_t* data, size_type size) override;
    void send(const AbstractByteBuffer& data) override;

    size_type read(uint8_t* buffer, size_type size) override;
    size_type read(AbstractByteBuffer& buffer, size_type size) override;

	void CS_UP() const;
	void CS_DOWN() const;

private:
	SPIInterface& interface;
	ChipSelectPin cs_pin;
};

#endif /* SOURCES_INTERFACES_SPICOMMUNICATIONCHANNEL_H_ */
