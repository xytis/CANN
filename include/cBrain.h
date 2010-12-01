#ifndef CBRAIN_H_INCLUDED
#define CBRAIN_H_INCLUDED

#include <iostream>
#include <map>
#include "../include/cNeuron.h"

namespace CANN
{
    class cBrain
    {
        private:
            unsigned  m_size;
            std::map<unsigned,cNeuron*> * neurons;
        public:
            /**
            *   Constructor, which creates CANN from absolute zero.
            *   \param Random generator
            *   \param size
            */
            cBrain(cRandomPool &, unsigned m_size);
            /**
            *   Constructor, which loads created CANN from stream.
            *   \param Formated stream with genomes and stuff.
            */
            cBrain(std::istream &);

            //cBrain(std::object big_boobs);

            void    genome(std::ostream &);

            ~cBrain() {};
    };
};

#endif // CBRAIN_H_INCLUDED
