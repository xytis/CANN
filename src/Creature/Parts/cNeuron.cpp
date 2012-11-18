#include "cNeuron.hpp"

namespace Creature
{
    cNeuron::
    cNeuron (unsigned ID):
    m_ID(ID),
    m_core(NULL),
    connections(NULL),
    reference(NULL)
    {
        connections = new std::map<cNeuron *,double>;
#ifdef DEBUG
        std::cout << "Neuron ID: " << ID << " address: " << this << std::endl;
#endif //DEBUG
    }

    void cNeuron::
    register_to(std::map<unsigned,cNeuron*> & neuron_map)
    {
        reference = &neuron_map;
        neuron_map[m_ID] = this;
    }

    void cNeuron::
    init(double threshold, double stiffness)
    {
        if (m_core)
            throw exception::custom("Please do not use init to alter m_core values.");
        m_core = new sNeuronCore;
        m_core->m_stiffness = stiffness;
        m_core->m_threshold = threshold;
    }

    void cNeuron::
    set_genome(std::string genome)
    {
        std::stringstream sin(genome);
        unsigned id;
        double t;
        if (m_core)
            delete m_core;
        m_core = new sNeuronCore;
        sin >> id;
        if (id != m_ID)
            throw exception::IDmissmatch("ID while loading genome does not match!");
        sin >> m_core->m_threshold;
        sin >> m_core->m_stiffness;
        while (sin >> id)
        {
            sin >> t;
            (*connections)[(*reference)[id]] = t;
        }
    }

    std::string cNeuron::
    get_genome()
    {
        std::stringstream sout;
        sout << m_ID << ' ';
        assert(m_core);
        sout << m_core->m_threshold << ' ';
        sout << m_core->m_stiffness << ' ';

        std::map<cNeuron *,double>::iterator iter;
        for( iter = (*connections).begin(); iter != (*connections).end(); ++iter )
        {
            //Only if neuron is registered at same parenting object.
            //Fail. This method creates the neurons at the reference with bad ID
            //if ((*reference)[(iter->first)->ID()] == iter->first)
            if (reference->find(iter->first->ID())->second == iter->first)
                sout << (iter->first)->ID() << ' ' << iter->second << ' ';
        }
        return sout.str();
    }

    void cNeuron::
    mutate_links(cRandomPool & R)
    {
        std::map<cNeuron *,double>::iterator iter;
        for( iter = (*connections).begin(); iter != (*connections).end(); ++iter )
        {
            iter->second += R.mutate_link();
        }
    }

    void cNeuron::
    mutate_core(cRandomPool & R)
    {
        m_core->m_threshold += R.mutate_threshold();
        m_core->m_stiffness += R.mutate_stiffness();
    }

    void cNeuron::
    get (double signal)
    {
        m_core->m_incoming+=signal;
    }

    void cNeuron::
    send()
    {
        std::map<cNeuron *,double>::iterator iter;
        for( iter = (*connections).begin(); iter != (*connections).end(); ++iter )
        {
            (iter->first)->get(iter->second * m_core->m_signal);
        }
    }

    void cNeuron::
    flip()
    {
        m_core->m_signal = 1/(1+exp(-(m_core->m_incoming-m_core->m_threshold)*m_core->m_stiffness));
        m_core->m_incoming = 0;
    }

    void cNeuron::
    link(cNeuron & to, double weight)
    {
        assert(reference);
        if (reference->find(to.ID())->second == &to)
            (*connections)[&to] = weight;
        else
            throw exception::custom("Neuron is not in reference array, perhaps its from other network?");
    }

    void cNeuron::
    unlink(cNeuron & from)
    {
        (*connections).erase(&from);
    }

    void cNeuron::
    pair(cNeuron & brother)
    {
        (*connections)[&brother] = 1;
    }

    void cNeuron::
    unpair(cNeuron & brother)
    {
        (*connections).erase(&brother);
    }

    std::string cNeuron::
    core_dump()
    {
        std::stringstream out;
        out << "ID: " << std::setw(4) << m_ID << " in: " << std::setw(6) << m_core->m_incoming << " act: " << std::setw(6) << m_core->m_signal << " | ";
        return out.str();
    }

    cNeuron::
    ~cNeuron()
    {
        delete m_core;
        delete connections;
        reference->erase(m_ID);
    }
};
