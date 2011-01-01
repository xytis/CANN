#include "../include/cBrain.h"

namespace CANN
{
    cBrain::
    cBrain(cRandomPool & R, unsigned size, std::string ID):
    m_size(size),
    m_ID(ID),
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

    cBrain::
    cBrain(std::istream & in):
    m_size(0),
    m_ID(""),
    neurons(NULL)
    {
        neurons = new std::map<unsigned,cNeuron*>;
        std::string label;
        while (in >> label)
        {

            if (label == "TYPE")
            {
                in >> label;
                if (label != "cBrain")
                    throw exception::custom("Wrong type of stream data!");
            }
            if (label == "ID")
            {
                in >> m_ID;
            }
            if (label == "SIZE")
            {
                in >> m_size;
            }
            if (label == "NEURONS")
            {
                std::string line;
                cNeuron * readed_neuron;
                for (unsigned u = 0; u < m_size; u++)
                {
                    readed_neuron = new cNeuron(u);
                    readed_neuron->register_to(*neurons);
                }
                for (unsigned u = 0; u < m_size; u++)
                {
                    std::getline(in, line);
                    if (line == "")
                        std::getline(in, line);
                    (neurons->at(u))->set_genome(line);
                }

            }

        }
    }

    void cBrain::
    genome(std::ostream & out)
    {
        out << "TYPE\t\tcBrain" << std::endl;
        out << "ID\t\t" << m_ID << std::endl;
        out << "SIZE\t\t" << m_size << std::endl;
        out << "NEURONS" << std::endl;
        for (unsigned u = 0; u < m_size; u++)
        {
            out << (neurons->at(u))->get_genome() << std::endl;
        }
    }

    void cBrain::
    send()
    {
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            iter->second->send();
        }
    }

    void cBrain::
    flip()
    {
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            iter->second->flip();
        }
    }

    std::ostream & cBrain::
    dump(std::ostream & out)
    {
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            out << iter->second->let() << ' ';
        }
        out << std::endl;
        return out;
    }
};
