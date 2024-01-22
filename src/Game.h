
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include "Bird.h"
#include "Block.h"
#include "GameObject.h"
#include "Level.h"
#include "Pig.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  bool textInit();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event);
  void pigCollision();
  void blockCollision();
  void birdConstraints();
  void respawn();
  void gameover();
  void resolveText();

 private:
  float origin_x = 0;
  float origin_y = 0;

  bool in_menu = true;
  bool in_options = false;
  bool selected_play = true;
  bool selected_option = false;
  bool selected_exit = false;

  int no_of_pigs = 3;
  int pigs_remaining = no_of_pigs;
  int no_of_birds = 5;

  float magnitude = 0 ;
  float gravity = 0;
  int player_score = 0;
  float bird_offset = 0.f;
  bool game_won = false;

  sf::Vector2i cursor_pos;
  Vector2 bird_vector = {0, 0};

  sf::RenderWindow& window;

  sf::Texture bird_texture;
  sf::Texture pig_texture;
  sf::Texture block_texture_1;
  sf::Texture block_texture_2;
  sf::Texture level_1_texture;
  sf::Texture level_2_texture;
  sf::Texture winner_screen_texture;
  sf::Texture menu_screen_texture;
  sf::Texture options_screen_texture;
  sf::Texture slingshot_texture;

  sf::Text play_text;
  sf::Text exit_text;
  sf::Text score_text;
  sf::Text options_text;
  sf::Text congrats_text;
  sf::Text objects_remaining;
  sf::Font font;

  GameObject* slingshot;
  GameObject* background;
  Bird* bird;
  Pig* pig_array;
  Block* block_array;

  GameObject game;
  GameObject* bird_array;
  Level level;
};

#endif // ANGRYBIRDS_GAME_H
