#ifndef CBRAIN_H_INCLUDED
#define CBRAIN_H_INCLUDED

#include <iostream>
#include <map>
#include "../include/exception.h"
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
            *   \param cRandomPool Random generator
            *   \param unsigned size
            *   \param std::string ID
            */
            cBrain(cRandomPool &, unsigned size, std::string ID);
            /**
            *   Constructor, which loads created CANN from stream.
            *   \param std::istream Formated stream with genomes and stuff.
            */
            cBrain(std::istream &);
            /**
            *   getter for cNeuron references
            *   \param unsigned ID
            *   \return refence to cNeuron
            */
            cNeuron * at(unsigned id) { return neurons->find(id)->second;};

            /**
            *   Returns ID of brain.
            *   \return ID
            */
            std::string  ID() { return m_ID; };

            /**
            *   Outputs genome of the whole brain with its cells
            *   to given stream object.
            *   \param std::ostream Stream object with genome.
            */
            void    genome(std::ostream &);

            /**
             * Mutates the brain.
             * \param cRandomPool random pool
             */
            void mutate(cRandomPool &);

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
            *   \param std::ostream output stream
            */
            std::ostream & dump(std::ostream &);

            /**
             * Returns the size of brain
             * \return unsigned size
             */
            unsigned size() { return m_size; };

            ~cBrain() {};
    };
};

#endif // CBRAIN_H_INCLUDED
