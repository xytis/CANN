#ifndef CNEURON_H_INCLUDED
#define CNEURON_H_INCLUDED

#include <iostream>

#include <string>
#include <sstream>
#include <cassert>
#include <map>
#include <cmath>

#include "../include/exception.h"

namespace CANN
{
    struct sNeuronCore
    {
        unsigned    m_owners;

        double      m_threshold;
        double      m_stiffness;
        double      m_signal;
        double      m_incoming;
    };

    class cNeuron
    {
        private:
            unsigned    m_ID;

            sNeuronCore * m_core;

            std::map<cNeuron *,double> * connections;

            std::map<unsigned,cNeuron*> * reference;

        public:
            cNeuron (unsigned);
            void link (std::map<unsigned,cNeuron*> &);


            unsigned    ID() {return m_ID;};

            std::string get_genome();
            void set_genome (std::string);

            /**
            *   Receives signals
            */
            void        get(double);
            /**
            *   Uses the curent activation value to send signals
            */
            void        send();
            /**
            *   Makes the incoming signal sum the activation value
            *   Uses the sigmoid function to smooth out threshold.
            */
            void        flip();

            /**
            *   Pairing of two(or more) neurons.
            *   \param cNeuron to pair with
            */
            void        pair(cNeuron &);
            sNeuronCore * respond_to_pair();
            /**
            *   Do not delete single neurons, it causes shitload of problems
            */
            ~cNeuron();

    };
};

#endif // CNEURON_H_INCLUDED
