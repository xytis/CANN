#include "../include/cSpotCreature.h"

namespace CANN
{
    cSpotCreature::cSpotCreature(cRandomPool & pool, int size, unsigned ID)
    {
        //ID consists of "FatherID Generation# UniqueID"
        //Every time new creature is created it inherits its parent ID, and the generation number is increased.
        //ID that is passed to this constructor is current UniqueID
        std::stringstream s;
        s << "0 0 " << ID;
        m_ID = s.str();
        m_brain = new cBrain(pool, size, m_ID + static_cast<std::string>(" B"));
        m_input = m_brain->at(0);
        m_output = m_brain->at(m_brain->size()-1);
    }
    
    cSpotCreature::cSpotCreature(cSpotCreature & father, cRandomPool & pool)
    {
        //Get genome
        std::stringstream genome;
        father.genome(genome);
        //Parse genome, build new creature. (exact copy)
        std::string label;
        while (genome >> label)
        {
            unsigned input, output;
            if (label == "TYPE")
            {
                genome >> label;
                if (label != "cSpotCreature")
                    throw exception::Fatal("Stream filled with wrong type of data!");
            }
            if (label == "ID")
            {
                std::getline(genome, m_ID);
            }
            if (label == "INPUT")
            {
                genome >> input;
            }
            if (label == "OUTPUT")
            {
                genome >> output;
            }
            if (label == "BRAIN")
            {
                m_brain = new cBrain(genome);
                m_input = m_brain->at(input);
                m_output = m_brain->at(output);
            }
        }
        //Mutate the new creature, by altering its brains,
        m_brain->mutate(pool);
        //Update the ID.
        std::stringstream old_ID(m_ID);
        unsigned fatherID, GenerationNO, uniqueID;
        old_ID >> fatherID >> GenerationNO >> uniqueID;
        std::stringstream new_ID;
        new_ID << uniqueID << ' ' << ++GenerationNO << ' ' << pool.generate_ID(GenerationNO);
        m_ID = new_ID.str();
        //Done.
    }

    void cSpotCreature::genome(std::ostream & out)
    {
        out << "TYPE\t\tcSpotCreature" << std::endl;
        out << "ID\t\t" << m_ID << std::endl;
        out << "INPUT\t\t" << 0 << std::endl;
        out << "OUTPUT\t\t" << m_brain->size()-1 << std::endl;
        out << "BRAIN" << std::endl;
        m_brain->genome(out);
    }

    void cSpotCreature::input(double value)
    {
        m_input->get(value);
    }
    
    double cSpotCreature::output()
    {
        return m_output->let();
    }

    void cSpotCreature::think()
    {
        m_brain->send();
        m_brain->flip();
    }
}
