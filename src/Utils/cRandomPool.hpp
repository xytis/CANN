#ifndef CRANDOMPOOL_H_INCLUDED
#define CRANDOMPOOL_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <cmath>


class cRandomPool
{
private:
  unsigned long long m_seed;
  //Mutation boundaries.
public:
  cRandomPool();
  cRandomPool(unsigned long long seed);
  
  /**
   * Returns random in range [0,1]
   * @return random number
   */
  double  get_random();
  /**
   * Returns random in range [a,b]
   * @params a,b -- range
   * @return random number
   */
  double  get_random_in(double a,  double b);
  
  double  fresh_link();
  double  fresh_stiffness();
  double  fresh_threshold();
  
  double  mutate_link();
  double  mutate_stiffness();
  double  mutate_threshold();
  
  unsigned long long get_seed() { return m_seed; };
  
  unsigned generate_ID(unsigned generation);
};

#endif // CRANDOMPOOL_H_INCLUDED
