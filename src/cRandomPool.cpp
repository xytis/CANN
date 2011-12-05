#include "../include/cRandomPool.h"

namespace CANN
{
    cRandomPool::cRandomPool()
    {
        srand( time(NULL) );
    }
    
    cRandomPool::cRandomPool(unsigned long long seed)
    {
        m_seed = seed;
        srand(seed);
    }
   
    double cRandomPool::get_random()
    {
        return static_cast<double>( rand() ) / static_cast<double>( RAND_MAX );
    }
    
    double cRandomPool::get_random_in(double low,  double high)
    {
        return static_cast<double>( rand() ) * ( high - low ) / static_cast<double>( RAND_MAX ) + low ;
    }

    double cRandomPool::fresh_link()
    {
        return get_random_in(0.0, sqrt(0.5));
    }
    
    double cRandomPool::fresh_stiffness()
    {
        return get_random_in(10.0, 20.0);
    }
    
    double cRandomPool::fresh_threshold()
    {
        return 1-(get_random_in(0.0, 1.0)*get_random_in(0.0, 1.0));
    }

    double cRandomPool::mutate_link()
    {
        return 1+get_random_in(-0.01, 0.01);
    }
    
    double cRandomPool::mutate_stiffness()
    {
        return 1+get_random_in(-0.1, 0.1);
    }
    
    double cRandomPool::mutate_threshold()
    {
        return 1+get_random_in(-0.01, 0.01);
    }

    unsigned cRandomPool::generate_ID(unsigned generation)
    {
        static unsigned last_generation = 0;
        static unsigned last_ID = 0;
        if (generation == last_generation)
        {
            return ++last_ID;
        }
        else
        {
            last_generation = generation;
            last_ID = 0;
            return last_ID;
        }
    }
}
