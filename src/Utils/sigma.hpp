#ifndef SIGMA_H_INCLUDED
#define SIGMA_H_INCLUDED

class   sigma
{
    private:
        double * m_stiffness;
        double * m_threshold;
    public:
        sigma(double * stiffness, double * threshold):
        m_stiffness(stiffness),
        m_treshold(threshold) {};

        inline double Call(double x)
        {
            return 1/(1+exp(-(x-m_threshold)*m_stiffness));
        };
        
        inline double operator () (double x)
        {
            return 1/(1+exp(-(x-m_threshold)*m_stiffness));
        };
};

#endif // SIGMA_H_INCLUDED
