/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * CANN
 * Copyright (C) Vytis Valentinavičius 2009 <xytis2000@gmail.com>
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

#ifndef _SIGNALPOOL_H_
#define _SIGNALPOOL_H_

#include "main.h"
#include "neuron.h"
#include <vector>

class SignalPool
{
public:
	int										connectNeuron		(Neuron *);					//Adds neuron to the list, then gives back the ID of neuron.
 	void 									putSignal					(CSINAL , NEURONID);	//Takes the ID of neuron, then puts its signal in the array.
	CSIGNALARRAY					 	getSignals				(void );						//Returns the array of signals.
	bool									isLocked					(void );						//Returns true if there can't be any more neurons added.
																													// (The number of neurons is a constant)
	void										update						(void );						//Updates the signal table.
	
protected:

private:
	bool									mlocked;
	CSIGNALARRAY	 					mpool;
	std::vector<Neuron *> 		mneurons;
};

#endif // _SIGNALPOOL_H_
