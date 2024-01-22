#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{

}

GameObject::GameObject(sf::Texture &texture, std::string filename)
{
  initialiseSprite(texture, filename);
}

GameObject::~GameObject()
{

}


bool GameObject::initialiseSprite(sf::Texture &texture, std::string filename)
{
  if (!texture.loadFromFile(filename))
  {
    std::cout << "texture did not load\n";
  }
  sprite.setTexture(texture);

  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return &sprite;
}


bool GameObject::getMovement()
{
  return movement;
}

void GameObject::setMovement(bool value)
{
  movement = value;

}


int GameObject::getTimer()
{
  return active_time;
}

void GameObject::timerUpdate()
{
  active_time = clock.getElapsedTime().asMilliseconds() / 1000;
}

void GameObject::resetTimer()
{
  active_time = 0;
  sf::Time time = clock.restart();
}

float GameObject::getSpeed()
{
  return player_speed;
}


bool GameObject::getVisibility()
{
  return visibility;
}

void GameObject::setVisibility(bool value)
{
  visibility = value;
}