
#ifndef ANGRYBIRDSSFML_BLOCK_H
#define ANGRYBIRDSSFML_BLOCK_H

#include "GameObject.h"

class Block : public GameObject
{
 public:
  Block();
  ~Block();
  void destroyBlock();
};

#endif // ANGRYBIRDSSFML_BLOCK_H
