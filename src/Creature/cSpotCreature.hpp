#ifndef CSPOTCREATURE_H_INCLUDED
#define CSPOTCREATURE_H_INCLUDED 

#include "Parts/cBrain.hpp"
#include "Parts/cNeuron.hpp"
#include "Utils/cRandomPool.hpp"

#include <string>
#include <sstream>

namespace Creature
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