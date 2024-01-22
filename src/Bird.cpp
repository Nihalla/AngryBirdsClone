#include "Bird.h"


Bird::Bird()
{

}

Bird::~Bird()
{

}

Vector2 Bird::getDirection()
{
  return direction;
}
void Bird::setDirection(float x, float y)
{
  direction.x = x;
  direction.y = y;
}