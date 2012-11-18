#ifndef CMOVER_H_INCLUDED
#define CMOVER_H_INCLUDED

#include <vector>
#include <iostream>
#include <string>
#include <map>

#include "Utils/exception.hpp"
#include "cNeuron.hpp"
#include "cPeripheral.hpp"

namespace Creature
{
    class cMover : public cPeripheral
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
            *   Constructor, which creates cMover from absolute zero.
            *   \param Random generator
            *   \param array of size
            *   \param string ID
            */
            cMover(cRandomPool &, const std::vector<unsigned> & layout, std::string ID);

            /**
            *   Constructor, which loads created cSensor from stream.
            *   \param Formated stream with genomes and stuff.
            */
            cMover(std::istream &);

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
            *   Binds first array of neurons to brain neurons
            *   \param array of neurons, to whom it should bind.
            *   \throw exception::NetworksIncompatible
            */
            void    bind_input(const std::vector<cNeuron *> &);

            /**
            *   Dummy function for better compability
            */
            void    bind(const std::vector<cNeuron *> & V) {bind_input(V);};

            /**
            *   Sends output outside.
            *   \throw exception::custom
            */
            void output(std::vector<double> &);

            /**
            *   Function for exchanging information with outer world
            */
            void exchange(std::vector<double> & out)
            {
                if (!out.empty())
                    output(out);
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


#endif // CMOVER_H_INCLUDED
