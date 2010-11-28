#ifndef CSENSOR_H_INCLUDED
#define CSENSOR_H_INCLUDED

#include "../include/exception.h"

namespace CANN
{
    class cSensor
    {
        private:
            unsigned  m_ID;
            unsigned *m_number;
            unsigned  m_width;
            double  **m_threshold;
            double  **m_signal;
        public:
            /**
            *   Default constructor
            *   \param ID
            *   \param width
            *   \param *pattern
            */
            cSensor (unsigned ID, unsigned width, unsigned *pattern);
            /**
            *   Returns ID of sensor.
            *   \return ID
            */
            unsigned  ID() {return m_ID;};

            /**
            *   Binds last array of neurons to brain neurons
            *   \throw exception::NetworksIncompatible
            */
            void    bind_to_brain(unsigned, double *);

            /**
            *   Binds first array of neurons to input values
            *   \throw exception::NetworksIncompatible
            */
            void    bind_to_input(unsigned, double *);

            /**
            *   Takes one step of thinking
            */
            void    react();

            /**
            *   Loads the threshold matrix from external input
            *   \param  threshold matrix
            */
            void    load_threshold(double **);

            void    debug_fill_threshold();
    };

};

#endif // CSENSOR_H_INCLUDED
