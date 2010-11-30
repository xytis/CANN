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
            cBrain(std::istream &);


            ~cBrain() {};
    };
};

#endif // CBRAIN_H_INCLUDED
