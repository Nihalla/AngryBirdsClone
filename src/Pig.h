//
// Created by nida1 on 4/21/2021.
//

#ifndef ANGRYBIRDSSFML_PIG_H
#define ANGRYBIRDSSFML_PIG_H

#include "Block.h"
#include "GameObject.h"

class Pig : public GameObject
{
 public:
  Pig();
  ~Pig();
  void setHealth();
  bool getGravity();
  void pigFall(int &no_of_pigs, Pig* &pig_array, Block* &block_array);

 private:
  int hp = 1;
  bool grounded = true;
};

#endif // ANGRYBIRDSSFML_PIG_H
