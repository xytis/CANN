#ifndef CBRAIN_H_INCLUDED
#define CBRAIN_H_INCLUDED

#include <iostream>
#include <map>
#include "../include/cNeuron.h"
#include "../include/cNeuralNetwork.h"


namespace CANN
{
    class cBrain : public cNeuralNetwork
    {
        private:
            unsigned  m_size;
            std::string m_ID;
            std::map<unsigned,cNeuron*> * neurons;
        public:
            /**
            *   Constructor, which creates CANN from absolute zero.
            *   \param Random generator
            *   \param size
            *   \param string ID
            */
            cBrain(cRandomPool &, unsigned size, std::string ID);
            /**
            *   Constructor, which loads created CANN from stream.
            *   \param Formated stream with genomes and stuff.
            */
            cBrain(std::istream &);
            /**
            *   getter for cNeuron references
            *   \param unsigned ID
            *   \return refence to cNeuron
            */
            cNeuron * at(unsigned id) { return neurons->at(id);};

            /**
            *   Returns ID of brain.
            *   \return ID
            */
            std::string  ID() {return m_ID;};

            /**
            *   Outputs genome of the whole brain with its cells
            *   to given stream object.
            *   \param Stream object with genome.
            */
            void    genome(std::ostream &);

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
            std::ostream & dump(std::ostream &);

            ~cBrain() {};
    };
};

#endif // CBRAIN_H_INCLUDED
