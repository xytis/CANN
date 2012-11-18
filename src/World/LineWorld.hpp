#ifndef LINEWORLD_HPP_
#define LINEWORLD_HPP_

//Simple array, looped to it's ends.
//Has two methods -- getFood(float x) and eatFood(float x).
//When constructing specify resolution.
#include <Utils/cRandomPool.hpp>
#include <vector>

class LineWorld {
public:
  LineWorld(int resolution, float food, cRandomPool * random);
  ~LineWorld();
  
  float getFood(float x);
  float eatFood(float x, float amount);
  
  void addFood(float x, float amount);
  
  void growFood();
  
private:
  cRandomPool * 	m_pRandom;
  std::vector<float> 	m_aLineWorld;
  float 		m_fLineLength;
  float			m_fAllFood;
};

#endif //LINEWORLD_HPP_