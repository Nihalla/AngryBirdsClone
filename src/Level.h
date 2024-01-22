#ifndef ANGRYBIRDSSFML_LEVEL_H
#define ANGRYBIRDSSFML_LEVEL_H
#include "Bird.h"
#include "Block.h"
#include "Pig.h"
#include <SFML/Graphics.hpp>

class Level
{
 public:
  Level();
  ~Level();
  void loadLevel1(sf::RenderWindow& window, int &no_of_birds, int &no_of_pigs, Pig* &pig_array, GameObject* &background, sf::Texture &texture);
  void loadLevel2(int &no_of_birds, int &no_of_pigs, Pig* &pig_array, GameObject* &background, sf::Texture &texture, Block* &block_array);

 private:
  float offset    = 0.f;
};

#endif // ANGRYBIRDSSFML_LEVEL_H
