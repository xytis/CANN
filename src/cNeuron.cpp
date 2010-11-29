#include "../include/cNeuron.h"

namespace CANN
{
    cNeuron::
    cNeuron (unsigned ID):
    m_ID(ID),
    m_core(NULL),
    connections(NULL),
    reference(NULL)
    {

    }

    void cNeuron::
    link(std::map<unsigned,cNeuron*> & neuron_map)
    {
        reference = &neuron_map;
        neuron_map[m_ID] = this;
    }

    void cNeuron::
    set_genome(std::string genome)
    {
        std::stringstream sin(genome);
        unsigned id;
        double t;
        m_core = new sNeuronCore;
        m_core->m_owners = 1;
        sin >> id;
        if (id != m_ID)
            throw exception::IDmissmatch("ID while loading genome does not match!");
        sin >> m_core->m_threshold;
        sin >> m_core->m_stiffness;
        connections = new std::map<cNeuron *,double>;
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
        for( iter = (*connections).begin(); iter != (*connections).end(); ++iter ) {
            sout << (iter->first)->ID() << ' ' << iter->second << ' ';
        }
        return sout.str();
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
        for( iter = (*connections).begin(); iter != (*connections).end(); ++iter ) {
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
    pair(cNeuron & brother)
    {
        if (m_core)
            delete m_core;
        m_core = brother.respond_to_pair();
        m_core->m_owners++;
    }

    sNeuronCore * cNeuron::
    respond_to_pair()
    {
        return m_core;
    }

    cNeuron::
    ~cNeuron()
    {
        if (m_core->m_owners == 1)
            delete m_core;
        else
            m_core->m_owners--;
        delete connections;
        reference->erase(m_ID);
    }
};
