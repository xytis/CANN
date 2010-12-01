#include "../include/cBrain.h"

namespace CANN
{
    cBrain::
    cBrain(cRandomPool & R, unsigned size):
    m_size(size),
    neurons(NULL)
    {
        neurons = new std::map<unsigned,cNeuron*>;
        cNeuron * fresh_neuron;
        for (unsigned u = 0; u < m_size; u++)
        {
            //Creates new neuron with ID of current loop number.
            fresh_neuron = new cNeuron(u);
            //Registers it to array.
            fresh_neuron->register_to(*neurons);
            fresh_neuron->init(R.fresh_threshold(), R.fresh_stiffness());
        }
        for (unsigned u = 0; u < m_size; u++)
            for (unsigned uu = 0; uu < m_size; uu++)
            {
                //Links the neurons with random weights.
                (neurons->at(u))->link(*(neurons->at(uu)), R.fresh_link());
            }
    }

    void cBrain::
    genome(std::ostream & out)
    {
        out << "CBRAIN GENOME" << std::endl;
        out << "SIZE:   " << m_size << std::endl;
        for (unsigned u = 0; u < m_size; u++)
        {
            out << (neurons->at(u))->get_genome() << std::endl;
        }
    }

};
