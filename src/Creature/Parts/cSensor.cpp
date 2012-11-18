#include "cSensor.hpp"

namespace Creature
{
    cSensor::
    cSensor(cRandomPool & R, const std::vector<unsigned> & layout, std::string ID):
    m_layout(layout),
    m_size(0),
    m_ID(ID),
    neurons(NULL)
    {
        for (unsigned u = 0; u < m_layout.size(); u++)
            m_size += m_layout.at(u);
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
        //Link the layers
        for (unsigned u = 0, n = 0; u < m_layout.size()-1; u++)
        {
            for (unsigned uu = 0; uu < m_layout.at(u); uu++)
            {
                for (unsigned uuu = 0; uuu < m_layout.at(u+1); uuu++)
                    //Links the neurons with random weights.
                    (neurons->find(n+uu)->second)->link(*(neurons->find(n+m_layout.at(u)+uuu)->second), R.fresh_link());
            }
            n += m_layout.at(u);
        }
        //Save references of input layer
        for (unsigned u = 0; u < m_layout.at(0); u++)
        {
            m_input.push_back(neurons->find(u)->second);
        }
        //Save references of the output layer
        for (unsigned u = m_size-m_layout.at(m_layout.size()-1); u < m_size; u++)
        {
            m_output.push_back(neurons->find(u)->second);
        }
    }

    cSensor::
    cSensor(std::istream & in):
    m_layout(),
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
                if (label != "cSensor")
                    throw exception::custom("Wrong type of stream data!");
            }
            if (label == "ID")
            {
                in >> m_ID;
            }
            if (label == "LAYOUT")
            {
                unsigned size, t;
                in >> size;
                for (unsigned u = 0; u < size; u++)
                {
                    in >> t;
                    m_layout.push_back(t);
                }

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
                    (neurons->find(u)->second)->set_genome(line);
                }
                //Save references of input layer
                for (unsigned u = 0; u < m_layout.at(0); u++)
                {
                    m_input.push_back(neurons->find(u)->second);
                }
                //Save references of the output layer
                for (unsigned u = m_size-m_layout.at(m_layout.size()-1)-1; u < m_size; u++)
                {
                    m_output.push_back(neurons->find(u)->second);
                }
            }

        }
    }


    void cSensor::
    genome(std::ostream & out)
    {
        out << "TYPE\t\tcSensor" << std::endl;
        out << "ID\t\t" << m_ID << std::endl;
        out << "LAYOUT\t\t" << m_layout.size() << '\t';
        for (unsigned u = 0; u < m_layout.size(); u++)
            out << m_layout.at(u) << ' ';
        out << std::endl;
        out << "SIZE\t\t" << m_size << std::endl;
        out << "NEURONS" << std::endl;
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            out << iter->second->get_genome() << std::endl;
        }
    }

    void cSensor::
    bind_output(const std::vector<cNeuron *> & array)
    {
        if (array.size() != m_output.size())
            throw exception::NetworksIncompatible("Neuron plug size missmatch");
        for (unsigned u = 0; u < array.size(); u++)
        {
            m_output.at(u)->pair(*array.at(u));
        }
    }

    void cSensor::
    input(const std::vector<double> & in)
    {
        if (in.size() != m_input.size())
            throw exception::custom("Wrong input array size");
        for (unsigned u = 0; u < in.size(); u++)
        {
            m_input.at(u)->get(in.at(u));
        }
    }

    void cSensor::
    send()
    {
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            iter->second->send();
        }
    }

    void cSensor::
    flip()
    {
        std::map<unsigned,cNeuron *>::iterator iter;
        for( iter = (*neurons).begin(); iter != (*neurons).end(); ++iter )
        {
            iter->second->flip();
        }
    }

    std::ostream & cSensor::
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
