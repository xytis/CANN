#ifndef CPERIPHERAL_H_INCLUDED
#define CPERIPHERAL_H_INCLUDED

#include "cNeuralNetwork.hpp"

namespace Creature
{
    class   cPeripheral : public cNeuralNetwork
    {
        public:
            virtual void    bind        (const std::vector<cNeuron *> &)    = 0;
            virtual void    exchange    (std::vector<double> &)             = 0;
    };
};
#endif
