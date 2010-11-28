#include "../include/cSensor.h"

namespace CANN
{
    /*
    cSensor::
    cSensor(unsigned ID, unsigned width, unsigned *pattern):
    m_ID(ID),
    m_width(width),
    m_number(pattern),
    m_threshold(NULL),
    m_signal(NULL)
    {

    }

    void cSensor::
    bind_to_brain(unsigned number, double * array)
    {
        if (number != m_number[m_width-1])
            throw   exception::NetworksIncompatible("Network connection widths do not match");
        m_signal[m_width-1]=array;
    }

    void cSensor::
    bind_to_input(unsigned number, double * array)
    {
        if (number != m_number[0])
            throw   exception::NetworksIncompatible("Network connection widths do not match");
        m_signal[0]=array;
    }

    void cSensor::
    clear_signal()
    {
    for(unsigned u = 1; u < m_width; u++)
        for(unsigned uu = 0; uu < m_number[u]; uu++)
        {
            m_signal[u][uu] = 0;
        }
    }

    void cSensor::
    react()
    {
        clear_signal;
        for(unsigned u = 0; u < m_width-1; u++)
            for(unsigned uu = 0; uu < m_number[u]; uu++)
            {
                m_signal[u+1][uu] += m_signal[u][uu]*m_threshold[u][uu];
            }
    }
    */
};
