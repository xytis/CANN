#include "LineWorld.hpp"

constexpr float max_food = 10.0f;
constexpr float food_multiplicator = 2.0f;

LineWorld::LineWorld(int resolution, float food, cRandomPool * random)
: m_pRandom(random)
{
  m_aLineWorld.resize(resolution);
  m_fLineLength = 10.0f;
  m_fAllFood = 0;
  
  while (food > 0) {
    float amount = m_pRandom->get_random_in(0.0f, food);
    float coord = m_pRandom->get_random_in(0.0f, m_fLineLength);
    food -= amount;
    addFood(coord, amount);
  }
  
}

LineWorld::~LineWorld()
{

}

float LineWorld::getFood(float x)
{
  float coord = fmod(x, m_fLineLength);
  int index = floor(coord);
  return m_aLineWorld.at(index);
}

float LineWorld::eatFood(float x, float amount)
{
  float coord = fmod(x, m_fLineLength);
  int index = floor(coord);
  float & food = m_aLineWorld.at(index);
  if (food > amount)
  {
    food -= amount;
    return amount;
  } else {
    amount = food;
    food -= amount;
    return amount;
  }
}

void LineWorld::addFood(float x, float amount)
{
  float coord = fmod(x, m_fLineLength);
  int index = floor(coord);
  float & food = m_aLineWorld.at(index);
  food += amount;
  if (food > max_food) {
    food = max_food;
  }
}

void LineWorld::growFood()
{
  for (int i = 0; i < m_aLineWorld.size(); i++) {
    float & food = m_aLineWorld.at(i);
    food *= food_multiplicator;
    if (food > max_food) {
      //spread some food around
      addFood(i-1, (food-max_food)/2);
      addFood(i+1, (food-max_food)/2);
    }
  }
}


