/*
 * Ports.h
 *
 *  Created on: Mar 8, 2019
 *      Author: PC
 */

#ifndef SOURCES_INTERFACES_PORTS_H_
#define SOURCES_INTERFACES_PORTS_H_

#include <stdint.h>
#include <utility>
#include "gpio1.h"
#include "fsl_gpio_driver.h"

template <typename> struct InputPort;

// NÃO PONHA UM DESTRUTOR VIRTUAL NESSE CARA!!! AÍ ELE VIR NON-LITERAL

struct Port
{
    constexpr Port(uint32_t PIN) : PIN(PIN) {}
//    virtual ~Port() = default;
protected:
    const uint32_t PIN;
};

template <typename T> struct OutputPort : T
{
    static_assert(std::is_base_of<Port, T>::value /*|| std::is_base_of<InputPort<Port>, T>::value*/, "Template argument should be base of Port or InputPort");
    template <typename ... Args>
    constexpr OutputPort(Args... args) : T (std::forward<Args>(args)...){}

	virtual void write(uint32_t level) const
	{
		GPIO_DRV_WritePinOutput(T::PIN, level);
	}

	virtual void set() const
	{
		GPIO_DRV_SetPinOutput(T::PIN);
	}

	virtual void clear() const
	{
		GPIO_DRV_ClearPinOutput(T::PIN);
	}

	virtual void toggle() const
	{
		GPIO_DRV_TogglePinOutput(T::PIN);
	}
};

template <typename T> struct InputPort : T
{
    static_assert(std::is_base_of<Port, T>::value /*|| std::is_base_of<OutputPort<Port>, T>::value*/, "Template argument should be base of Port or OutputPort");
    template <typename ... Args>
    constexpr InputPort(Args... args) : T (std::forward<Args>(args)...){}

	virtual uint32_t read() const
	{
		return GPIO_DRV_ReadPinInput(T::PIN);
	}
};

#endif /* SOURCES_INTERFACES_PORTS_H_ */
