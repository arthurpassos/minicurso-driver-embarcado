/*
 * SPICommunicationChannel.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: PC
 */

#include "SPICommunicationChannel.h"

SPICommunicationChannel::SPICommunicationChannel(SPIInterface& interface, ChipSelectPin cs_pin)
: interface(interface), cs_pin(cs_pin)
{
}

void SPICommunicationChannel::send(const uint8_t* data, size_type size)
{
	return interface.send(data, size);
}

void SPICommunicationChannel::send(const AbstractByteBuffer& data)
{
	return interface.send(data);
}

Interface::size_type SPICommunicationChannel::read(uint8_t* buffer, size_type size)
{
	return interface.read(buffer, size);
}

Interface::size_type SPICommunicationChannel::read(AbstractByteBuffer& buffer, size_type size)
{
	return interface.read(buffer.get(), size);
}

void SPICommunicationChannel::CS_UP() const
{
	cs_pin.set();
}

void SPICommunicationChannel::CS_DOWN() const
{
	cs_pin.clear();
}
