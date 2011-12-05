#ifndef CSPOTCREATURE_H_INCLUDED
#define CSPOTCREATURE_H_INCLUDED 

#include "../include/cBrain.h"
#include "../include/cNeuron.h"
#include "../include/cRandomPool.h"

#include <string>
#include <sstream>

namespace CANN
{
    class cSpotCreature
    {
    public:
        cSpotCreature(cRandomPool & pool, int size, unsigned ID);
        cSpotCreature(cSpotCreature & father, cRandomPool & pool);

        void input(double );
        double output();

        void genome(std::ostream &);

        void think();
    private:
        std::string m_ID;
        cBrain * m_brain;
        cNeuron * m_input;
        cNeuron * m_output;
    };
}

#endif