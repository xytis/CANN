/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CANN
 * Copyright (C)  2009 <>
 * 
 * CANN is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CANN is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NEURON_H_
#define _NEURON_H_

#include "signalpool.h"
#include <string>

/**
 * Enum for distinguishing the neurons.
 */
enum NeuronType
{
	Normal = 0,							//Obvious
	Input = 1,							//
	Output = 2,							//
	//Cancer = 53,						//What if one neuron is mutating more severelly than others?
	Dead = 255							//Just a neuron which does not update. It can be dead for a while, or forever =]
};
/* $
 *	From above is obvious that a input neuron can not be normal =], or it can not be an output neuron,
 *	thus limiting the minimal size of a network to input + output.
 */

/**
 * Main workhorse class.
 */
class Neuron
{
public:
	Neuron								();																		//Base constructor. Should create an empty Normal Neuron,
																															// yet not attached any other class, thus unusable. FIXME: maybe this is useless?
	Neuron								(NeuronType, SignalPool *, /*Mutator *,*/);			//Constructor, automaticly bonding with the other clases,
																															// yet taking the random for the "genetic code"
	Neuron								(std::string, SignalPool *,/*Mutator *,*/);				//Swiss army knife one =], Used when reloading from a previous simmulation.

	void										assignSignalPool		(SignalPool * );

	void										update						(void );								//recalculates the output based on input.

	std::string							formatState				(void );								//produces the state of neuron in a string format.	
protected:
	void										recoverState			(std::string );						//reproduces the parameters from a given string.
private:
	SignalPool							*pool;
	//Mutator								*mutator;
	NEURONID							id;
	NeuronType							type;
	CSIGNAL 								(*process)				(CSIGNALARRAY );					//changeable process function (different threshold?)
	//The idea behind a changeable process function: If a neutron is an input neutron -- it does not "think", as in, it does not react to local signals,
	//if it can obtain a signal from external source. An external source can be a class which has a method which can be assigned to this function variable.
	//Almost the same goes to output, just it "thinks" as a regular neuron, but sends its result to external place. When a non special neuron -- just "thinks".
	CSIGNALARRAY						influenceValues;													//modifiers which are aplied to each input.
	//void									mutate						(void );									//slightly changes the influenceValues.
};

#endif // _NEURON_H_
