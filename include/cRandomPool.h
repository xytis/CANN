#ifndef CRANDOMPOOL_H_INCLUDED
#define CRANDOMPOOL_H_INCLUDED

namespace CANN
{
    class cRandomPool
    {
        private:
            unsigned long long m_seed;
            //Mutation boundaries.
        public:
            cRandomPool() {};
            cRandomPool(unsigned long long seed) {};

            double  mutation() {return 0.99;};
            double  get_random() {return 1;};
            double  get_random_in(double a,  double b) {return 1;};

            double  fresh_link() {return 0.25;};
            double  fresh_stiffness() {return 1;};
            double  fresh_threshold() {return 0.5;};

            unsigned long long get_seed() {return m_seed;};
    };
};

#endif // CRANDOMPOOL_H_INCLUDED
