
#ifndef ANGRYBIRDSSFML_BIRD_H
#define ANGRYBIRDSSFML_BIRD_H

#include "GameObject.h"
#include "Vector2.h"

class Bird : public GameObject
{
 public:
  Bird();
  ~Bird();
  Vector2 getDirection();
  void setDirection(float x, float y);

 private:
  Vector2 direction = {0 ,0};
  bool bird_move = false;
};

#endif // ANGRYBIRDSSFML_BIRD_H
