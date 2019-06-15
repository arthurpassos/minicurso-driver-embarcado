/*
 * IPowerable.h
 *
 *  Created on: Mar 26, 2019
 *      Author: PC
 */

#ifndef SOURCES_UTILS_IPOWERABLE_H_
#define SOURCES_UTILS_IPOWERABLE_H_


struct IPowerable
{
	virtual ~IPowerable() = default;

	virtual void turn_on() = 0;
	virtual void turn_off() = 0;

	virtual bool is_on() = 0;
};


#endif /* SOURCES_UTILS_IPOWERABLE_H_ */
