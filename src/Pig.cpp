#include "Pig.h"
Pig::Pig()
{

}

Pig::~Pig()
{

}
void Pig::setHealth()
{
  hp -= 1;
  setVisibility(false);
}

bool Pig::getGravity()
{
  return grounded;
}

// Function which determines whether any of the pigs are colliding with
// any of the blocks.
// If they are, then they will remain still, otherwise fall to the ground
void Pig::pigFall(int& no_of_pigs, Pig*& pig_array, Block*& block_array)
{
  for (int i = 0; i < 5; ++i)
  {
    pig_array[i].grounded = false;
    for (int j = 0; j < 10; ++j)
    {
      if (pig_array[i].getVisibility() && block_array[j].getVisibility())
      {
        if (pig_array[i].getSprite()->getGlobalBounds().intersects(
              block_array[j].getSprite()->getGlobalBounds()))
        {
          pig_array[i].grounded = true;
        }
      }
    }
    if (pig_array[i].getSprite()->getPosition().y > 600)
    {
      pig_array[i].grounded = true;
    }
    if (!pig_array[i].getGravity())
    {
      pig_array[i].getSprite()->move(0, 1);
    }
  }
}
