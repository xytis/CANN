#ifndef CBRAIN_H_INCLUDED
#define CBRAIN_H_INCLUDED

#include <iostream>
#include "../include/cNeuron.h"

namespace CANN
{
    class cBrain
    {
        private:
            double  **m_threshold;
            double  **m_signal;
            unsigned  m_size;
        public:
            cBrain(unsigned);

            void debug_print_threshold(std::ostream & out = std::cout);
            void debug_print_signal(std::ostream & out = std::cout);

            ~cBrain() {};
    };
};

#endif // CBRAIN_H_INCLUDED
