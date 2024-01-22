#ifndef ANGRYBIRDSSFML_GAMEOBJECT_H
#define ANGRYBIRDSSFML_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  GameObject(sf::Texture &texture, std::string filename);
  ~GameObject();

  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();

  bool getMovement();
  void setMovement(bool value);

  int getTimer();
  void timerUpdate();
  void resetTimer();

  float getSpeed();

  bool getVisibility();
  void setVisibility(bool value);


 private:
  sf::Clock clock;
  sf::Sprite sprite;

  int active_time = 0;
  bool visibility = true;
  bool movement = false;

  float player_speed = 800;

};
#endif // ANGRYBIRDSSFML_GAMEOBJECT_H
