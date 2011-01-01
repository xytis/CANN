#ifndef CNEURON_H_INCLUDED
#define CNEURON_H_INCLUDED

#include <iostream>

#include <string>
#include <sstream>
#include <cassert>
#include <map>
#include <cmath>

#include <iomanip>

#include "../include/exception.h"
#include "../include/cRandomPool.h"

namespace CANN
{
    struct sNeuronCore
    {
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

            /**
            *   Gives neurons a place to be =]
            *   Actualy it registers ID address pair of given neuron
            *   \param map[ID]=address
            */
            void        register_to (std::map<unsigned,cNeuron*> &);

            /**
            *   Getter m_ID()
            *   \return m_ID
            */
            unsigned    ID() {return m_ID;};

            /**
            *   Sets threshold and stiffness
            */
            void        init(double, double);

            /**
            *   Creates an active link with a weight
            */
            void        link (cNeuron &, double);
            /**
            *   Deletes a link
            */
            void        unlink (cNeuron &);

            /**
            *   Returns genome in formated string
            *   \return genome
            */
            std::string get_genome();
            /**
            *   Loads genome from formated string.
            *   \param genome
            */
            void        set_genome (std::string);

            /**
            *   Mutates all links
            *   \param cRandomPool instance
            */
            void        mutate_links (cRandomPool &);

            /**
            *   Mutates core values
            *   \param cRandomPool instance
            */
            void        mutate_core (cRandomPool &);

            /**
            *   Receives signals
            */
            void        get(double);
            /**
            *   Shows current signal
            */
            double      let()   { return m_core->m_signal;};
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
            *   Alows one-way data flow from this to given neuron
            *   \param cNeuron to pair with
            */
            void        pair(cNeuron &);
            /**
            *   Breaking pairing with another neuron
            *   \param cNeuron to unpair from
            */
            void        unpair(cNeuron &);

            std::string core_dump();
            /**
            *   Do not delete single neurons, it causes shitload of problems
            */
                        ~cNeuron();

    };
};

#endif // CNEURON_H_INCLUDED
