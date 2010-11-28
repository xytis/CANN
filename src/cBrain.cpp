#include "../include/cBrain.h"

namespace CANN
{
    cBrain::cBrain(unsigned size):
    m_size(size)
    {
        m_threshold = new double * [size];
        m_signal = new double * [size];
        for (unsigned u = 0; u < size; u++)
        {
            m_threshold[u] = new double[size];
            m_signal[u] = new double[size];
            for (unsigned uu = 0; uu < size; uu++)
            {
                m_threshold[u][uu] = 0;
                m_signal[u][uu] = 0;
            }
        }
    }

    void cBrain::
    debug_print_threshold(std::ostream & out)
    {
        out << "THRESHOLD receiver\\sender" << std::endl;
        for (unsigned l = 0; l < m_size; l++)
        {
            for (unsigned c = 0; c < m_size; c++)
            {
                out << m_threshold[c][l] << ' ';
            }
            out << std::endl;
        }
    }

    void cBrain::
    debug_print_signal(std::ostream & out)
    {
        out << "SIGNAL receiver\\sender" << std::endl;
        for (unsigned l = 0; l < m_size; l++)
        {
            for (unsigned c = 0; c < m_size; c++)
            {
                out << m_signal[c][l] << ' ';
            }
            out << std::endl;
        }
    }

};
