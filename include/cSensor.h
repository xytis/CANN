#ifndef CSENSOR_H_INCLUDED
#define CSENSOR_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "../include/exception.h"
#include "../include/cNeuron.h"
#include "../include/cPeripheral.h"

namespace CANN
{
    class cSensor : public cPeripheral
    {
        private:
            std::vector<unsigned> m_layout;
            unsigned    m_size;
            std::vector<cNeuron *> m_input;
            std::vector<cNeuron *> m_output;
            std::string m_ID;
            std::map<unsigned,cNeuron*> * neurons;
        public:
            /**
            *   Constructor, which creates cSensor from absolute zero.
            *   \param Random generator
            *   \param array of size
            *   \param string ID
            */
            cSensor(cRandomPool &, const std::vector<unsigned> & layout, std::string ID);

            /**
            *   Constructor, which loads created cSensor from stream.
            *   \param Formated stream with genomes and stuff.
            */
            cSensor(std::istream &);

            /**
            *   getter for cNeuron references
            *   \param unsigned ID
            *   \return refence to cNeuron
            */
            cNeuron * at(unsigned id) { return neurons->find(id)->second;};

            /**
            *   Outputs genome of the sensor with its cells
            *   to given stream object.
            *   \param Stream object with genome.
            */
            void    genome(std::ostream &);

            /**
            *   Returns ID of sensor.
            *   \return ID
            */
            std::string  ID() {return m_ID;};

            /**
            *   Binds last array of neurons to brain neurons
            *   \param array of neurons, to whom it should bind.
            *   \throw exception::NetworksIncompatible
            */
            void    bind_output(const std::vector<cNeuron *> &);

            /**
            *   Dummy function for better compability
            */
            void    bind(const std::vector<cNeuron *> & V) {bind_output(V);};

            /**
            *   Gets input from outside, and feeds it to neurons.
            *   \throw exception::custom
            */
            void    input(const std::vector<double> &);

            /**
            *   Function for exchanging information with outer world
            */
            void exchange(std::vector<double> & in)
            {
                if (!in.empty())
                    input (in);
            };

            /**
            *   Takes one step of thinking
            */
            void    send();
            /**
            *   Finishes the thinking
            */
            void    flip();

            /**
            *   Dumps current states
            */
            std::ostream &    dump(std::ostream &);

    };

};

#endif // CSENSOR_H_INCLUDED
