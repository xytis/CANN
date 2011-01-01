#ifndef CNEURALNETWORK_H_INCLUDED
#define CNEURALNETWORK_H_INCLUDED

#include "../include/cNeuron.h"

namespace CANN
{
    class cNeuralNetwork
    {
        public:
            virtual std::string     ID()                    = 0;
            virtual cNeuron *       at(unsigned id)         = 0;
            virtual void            send()                  = 0;
            virtual void            flip()                  = 0;
            virtual void            genome(std::ostream &)  = 0;
            virtual std::ostream &  dump(std::ostream &)    = 0;

            friend std::ostream & operator << (std::ostream & out, cNeuralNetwork & N)
            {
                return N.dump(out);
            };
    };
};

#endif
