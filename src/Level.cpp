#include "Level.h"

Level::Level()
{

}

Level::~Level()
{

}

void Level::loadLevel1(sf::RenderWindow& window, int &no_of_birds, int &no_of_pigs, Pig* &pig_array, GameObject* &background, sf::Texture &texture)
{
  offset = 0.f;
  background->getSprite()->setTexture(texture);
  no_of_birds = 5;
  no_of_pigs  = 3;
  for (int i = 0; i < no_of_pigs; i++)
  {
    pig_array[i].setVisibility(true);
    pig_array[i].getSprite()->setPosition(
      window.getSize().x / 1.5f -
        pig_array[i].getSprite()->getGlobalBounds().width / 2 + offset,
      window.getSize().y / 1.2f -
        pig_array[i].getSprite()->getGlobalBounds().height / 2);
    offset += 100;
  }
}
void Level::loadLevel2(int &no_of_birds, int &no_of_pigs, Pig* &pig_array, GameObject* &background, sf::Texture &texture, Block* &block_array)
{
  background->getSprite()->setTexture(texture);
  no_of_birds = 10;
  no_of_pigs  = 5;
  for (int i = 0; i < no_of_pigs; i++)
  {
    pig_array[i].setVisibility(true);
  }
  for (int i = 0; i < 10; ++i)
  {
    block_array[i].setVisibility(true);
  }

  pig_array[0].getSprite()->setPosition(690, 485);
  pig_array[1].getSprite()->setPosition(870, 485);
  pig_array[2].getSprite()->setPosition(740, 370);
  pig_array[3].getSprite()->setPosition(820, 370);
  pig_array[4].getSprite()->setPosition(780, 200);
  block_array[0].getSprite()->setPosition(650, 450);
  block_array[1].getSprite()->setPosition(950, 450);
  block_array[2].getSprite()->setPosition(700, 350);
  block_array[3].getSprite()->setPosition(900, 350);
  block_array[4].getSprite()->setPosition(800, 250);
  block_array[5].getSprite()->setPosition(680, 550);
  block_array[6].getSprite()->setPosition(850, 550);
  block_array[7].getSprite()->setPosition(690, 430);
  block_array[8].getSprite()->setPosition(840, 430);
  block_array[9].getSprite()->setPosition(690, 320);
}
