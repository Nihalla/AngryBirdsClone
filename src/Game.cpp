
#include "Game.h"
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  delete slingshot;
  slingshot = nullptr;
  delete bird;
  bird = nullptr;
  delete background;
  background = nullptr;

  delete[] bird_array;
  bird_array = nullptr;
  delete[] pig_array;
  pig_array = nullptr;
  delete[] block_array;
  block_array = nullptr;

}

bool Game::textInit()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  score_text.setString("0");
  score_text.setFont(font);
  score_text.setCharacterSize(25);
  score_text.setFillColor(sf::Color(204, 66, 66, 180));
  score_text.setPosition(
    window.getSize().x / 1.1f - score_text.getGlobalBounds().width / 1.1f,
    window.getSize().y / 20.f - score_text.getGlobalBounds().height / 20);

  objects_remaining.setString("Birds remaining: 5 / Pigs remaining: 3");
  objects_remaining.setFont(font);
  objects_remaining.setCharacterSize(25);
  objects_remaining.setFillColor(sf::Color(204, 66, 66, 180));
  objects_remaining.setPosition(
    window.getSize().x / 20.f -
      objects_remaining.getGlobalBounds().width / 20.f,
    window.getSize().y / 20.f -
      objects_remaining.getGlobalBounds().height / 20);

  play_text.setString("Play\n");
  play_text.setFont(font);
  play_text.setCharacterSize(25);
  play_text.setFillColor(sf::Color(255, 255, 255));
  play_text.setPosition(
    window.getSize().x / 4.f - play_text.getGlobalBounds().width / 2.f,
    window.getSize().y / 2.f - play_text.getGlobalBounds().height / 2);

  options_text.setString("Instructions\n");
  options_text.setFont(font);
  options_text.setCharacterSize(25);
  options_text.setFillColor(sf::Color(255, 255, 255));
  options_text.setPosition(
    window.getSize().x / 4.f - options_text.getGlobalBounds().width / 2.f,
    window.getSize().y / 2.f + options_text.getGlobalBounds().height / 4);

  exit_text.setString("Quit\n");
  exit_text.setFont(font);
  exit_text.setCharacterSize(25);
  exit_text.setFillColor(sf::Color(255, 255, 255));
  exit_text.setPosition(
    window.getSize().x / 4.f - exit_text.getGlobalBounds().width / 2.f,
    window.getSize().y / 2.f + exit_text.getGlobalBounds().height);

  congrats_text.setString("Congratulations!\n"
                          "Press Enter to go back to the main menu.");
  congrats_text.setFont(font);
  congrats_text.setCharacterSize(50);
  congrats_text.setFillColor(sf::Color(0, 0, 0));
  congrats_text.setPosition(
    window.getSize().x / 2.f - congrats_text.getGlobalBounds().width / 2.f,
    window.getSize().y / 3.f - congrats_text.getGlobalBounds().height / 2);
  return true;
}

bool Game::init()
{
  background = new GameObject(level_1_texture, "Data/Images/lvl1.png");
  background->initialiseSprite(level_2_texture, "Data/Images/lvl2.png");
  background->initialiseSprite(winner_screen_texture, "Data/Images/lvl3.png");
  background->initialiseSprite(
    options_screen_texture, "Data/Images/options.png");
  background->initialiseSprite(menu_screen_texture, "Data/Images/menu.jpg");
  background->getSprite()->setTexture(menu_screen_texture);

  background->getSprite()->setScale(
    window.getSize().x / background->getSprite()->getGlobalBounds().width,
    window.getSize().y / background->getSprite()->getGlobalBounds().height);

  bird = new Bird;
  bird->initialiseSprite(
    bird_texture, "Data/Images/kenney_animalpackredux/PNG/Round/duck.png");
  bird->getSprite()->setScale(0.5, 0.5);

  origin_x = window.getSize().x / 4.3;
  origin_y = window.getSize().y / 1.4;

  bird->getSprite()->setPosition(
    origin_x - bird->getSprite()->getGlobalBounds().width / 2,
    origin_y - bird->getSprite()->getGlobalBounds().height / 2);

  slingshot = new GameObject(
    slingshot_texture, "Data/Images/kenney_physicspack/PNG/Other/cactus.png");
  slingshot->getSprite()->setScale(1, 1.1);
  slingshot->getSprite()->setPosition(216, 535);

  pig_array = new Pig[5];
  for (int i = 0; i < 5; i++)
  {
    pig_array[i].initialiseSprite(
      pig_texture, "Data/Images/kenney_animalpackredux/PNG/Round/pig.png");
    pig_array[i].getSprite()->setScale(0.5, 0.5);
  }

  bird_array = new GameObject[10];
  for (int i = 0; i < 10 - 1; i++)
  {
    bird_array[i].getSprite()->setTexture(bird_texture);
    bird_array[i].getSprite()->setScale(0.25, 0.25);

    bird_array[i].getSprite()->setPosition(
      window.getSize().x - 880.f -
        bird_array[i].getSprite()->getGlobalBounds().width / 2 + bird_offset,
      window.getSize().y / 1.2f -
        bird_array[i].getSprite()->getGlobalBounds().height / 2);
    bird_offset -= 30;
  }

  block_array = new Block[10];
  for (int i = 0; i < 5; i++)
  {
    block_array[i].initialiseSprite(
      block_texture_1,
      "Data/Images/kenney_physicspack/PNG/Wood elements/elementWood019.png");
    block_array[i].getSprite()->setScale(0.5, 0.5);
  }
  for (int j = 5; j < 10; j++)
  {
    block_array[j].initialiseSprite(
      block_texture_2,
      "Data/Images/kenney_physicspack/PNG/Wood elements/elementWood012.png");
    block_array[j].getSprite()->setScale(0.5, 0.5);
  }

  textInit();

  return true;
}

void Game::respawn()
{
  no_of_birds--;
  gravity = 0;
  bird->setDirection(0, 0);
  bird->getSprite()->setPosition(
    origin_x - bird->getSprite()->getGlobalBounds().width / 2,
    origin_y - bird->getSprite()->getGlobalBounds().height / 2);
}


void Game::pigCollision()
{
  for (int i = 0; i < no_of_pigs; i++)
  {
    if (bird->getSprite()->getGlobalBounds().intersects(
          pig_array[i].getSprite()->getGlobalBounds()))
    {
      if (pig_array[i].getVisibility())
      {
        pig_array[i].setHealth();
        bird_vector.x *= -1;
        player_score += 100;
        score_text.setString(std::to_string(player_score));
        pigs_remaining--;
      }
    }
    if (pigs_remaining == 0)
    {
      if (player_score > 300)
      {
        background->getSprite()->setTexture(winner_screen_texture);
        game_won = true;
      }
      else
      {
        gravity = 0;
        bird->setDirection(0, 0);
        bird->getSprite()->setPosition(
          origin_x - bird->getSprite()->getGlobalBounds().width / 2,
          origin_y - bird->getSprite()->getGlobalBounds().height / 2);
        level.loadLevel2(
          no_of_birds,
          no_of_pigs,
          pig_array,
          background,
          level_2_texture,
          block_array);
        pigs_remaining = no_of_pigs;
      }
    }
  }
}

void Game::blockCollision()
{
  for (int i = 0; i < 10; i++)
  {
    if (bird->getSprite()->getGlobalBounds().intersects(
          block_array[i].getSprite()->getGlobalBounds()))
    {
      if (block_array[i].getVisibility())
      {
        block_array[i].destroyBlock();
        bird_vector.x *= -1;
        player_score += 50;
        score_text.setString(std::to_string(player_score));
      }
    }
  }
}

void Game::gameover()
{
  background->getSprite()->setTexture(menu_screen_texture);
  in_menu     = true;
  no_of_birds = 5;
  no_of_pigs  = 3;
  for (int i = 0; i < no_of_pigs; i++)
  {
    pig_array[i].setVisibility(true);
  }
}


// Function to make sure the bird respawns if it hits the ground.
// It doesn't respawn instantly in case a pig might fall on top of the bird

void Game::birdConstraints()
{
  if (
    bird->getSprite()->getPosition().x > 216 &&
    bird->getSprite()->getPosition().y > 600)
  {
    game.timerUpdate();

    bird->setMovement(false);
    bird->setDirection(0, 0);
    if (game.getTimer() >= 3)
    {
      if (no_of_birds - 1 != 0)
      {
        respawn();
        game.resetTimer();
      }
      else
      {
        respawn();
        game.resetTimer();
        gameover();
      }
    }
  }
  if (bird->getSprite()->getPosition().y > window.getSize().y)
  {
    respawn();
  }
}

void Game::update(float dt)
{
  if (in_menu)
  {
    resolveText();
  }
  if (!in_menu && !in_options && !game_won)
  {

    // Move the bird within the bounds of a square bounding box
    // This is to display where the bird is when the player is dragging it
    // Away from the slingshot, ready to be shot out.
    cursor_pos = sf::Mouse::getPosition(window);
    if (bird->getMovement())
    {
      if (
        (origin_x - cursor_pos.x <
         200 + bird->getSprite()->getGlobalBounds().width / 2) &&
        (origin_x - cursor_pos.x >
         0 - bird->getSprite()->getGlobalBounds().width / 2) &&
        (origin_y - cursor_pos.y <
         0 + bird->getSprite()->getGlobalBounds().height) &&
        (origin_y - cursor_pos.y >
         -200 + bird->getSprite()->getGlobalBounds().height / 2))
      {
        bird->getSprite()->setPosition(
          cursor_pos.x - bird->getSprite()->getGlobalBounds().width / 2,
          cursor_pos.y - bird->getSprite()->getGlobalBounds().height / 2);
      }
    }
    //---------------------------------------

    // The x direction doesn't need to alter while the bird is moving
    // Only the y direction needs to progressively arch down
    // It uses the magnitude as a constant force that pushes the bird up
    // Meanwhile the gravity keeps growing until it overpowers the force of magnitude

    if (bird->getDirection().x == 1 && !bird->getMovement())
    {
      bird->getSprite()->move(
        bird_vector.x * game.getSpeed() * dt,
        bird_vector.y * game.getSpeed() * dt + gravity - (magnitude / 25));
      gravity += 0.32f;
    }
    //---------------------------------------

    birdConstraints();
    blockCollision();
    pigCollision();
    pig_array->pigFall(no_of_pigs, pig_array, block_array);

    // Display of how much birds and pigs are left for the player
    objects_remaining.setString(
      "Birds remaining: " + std::to_string(no_of_birds) +
      " / Pigs remaining: " + std::to_string(pigs_remaining));
  }
}



void Game::render()
{
  window.draw(*background->getSprite());
  if (in_menu)
  {
    window.draw(play_text);
    window.draw(options_text);
    window.draw(exit_text);
  }
  if (!in_menu && !in_options && !game_won)
  {
    window.draw(score_text);
    window.draw(objects_remaining);
    window.draw(*slingshot->getSprite());
    for (int i = 0; i < 10; ++i)
    {
      if (block_array[i].getVisibility())
      {
        window.draw(*block_array[i].getSprite());
      }
    }
    window.draw(*bird->getSprite());
    for (int j = 0; j < no_of_birds - 1; j++)
    {
      if (bird_array[j].getVisibility())
      {
        window.draw(*bird_array[j].getSprite());
      }
    }
    for (int i = 0; i < no_of_pigs; i++)
    {
      if (pig_array[i].getVisibility())
      {
        window.draw(*pig_array[i].getSprite());
      }
    }
  }
  if (game_won)
  {
    window.draw(congrats_text);
  }
}

void Game::mouseClicked(sf::Event event)
{
  // Check if the mouse is clicking on the bird

  if (bird->getDirection().x == 0 && bird->getDirection().y == 0)
  {
    sf::Vector2i click = sf::Mouse::getPosition(window);
    if (
      (click.x > bird->getSprite()->getPosition().x) &&
      (click.x < bird->getSprite()->getPosition().x +
                   bird->getSprite()->getGlobalBounds().width) &&
      (click.y > bird->getSprite()->getPosition().y) &&
      (click.y < bird->getSprite()->getPosition().y +
                   bird->getSprite()->getGlobalBounds().height))
    {
      bird->setDirection(1, 0);
      bird->setMovement(true);
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  // Calculate the power of how far the bird will be able to fly
  // Magnitude is used as power

  bird->setMovement(false);
  game.resetTimer();
  bird_vector = { origin_x - bird->getSprite()->getPosition().x,
                  origin_y - bird->getSprite()->getPosition().y };
  magnitude   = sqrtf(pow(bird_vector.x, 2) + pow(bird_vector.y, 2));
  bird_vector.normalise();
}
void Game::resolveText()
{
  // Function to handle the text withing the menu
  if (selected_play)
  {
    play_text.setFillColor(sf::Color(255, 255, 255));
    options_text.setFillColor(sf::Color(0, 0, 0));
    exit_text.setFillColor(sf::Color(0, 0, 0));
    play_text.setCharacterSize(35);
    options_text.setCharacterSize(25);
    exit_text.setCharacterSize(25);
  }
  else if (selected_option)
  {
    play_text.setFillColor(sf::Color(0, 0, 0));
    options_text.setFillColor(sf::Color(255, 255, 255));
    exit_text.setFillColor(sf::Color(0, 0, 0));
    play_text.setCharacterSize(25);
    options_text.setCharacterSize(35);
    exit_text.setCharacterSize(25);

  }
  else
  {
    exit_text.setFillColor(sf::Color(255, 255, 255));
    options_text.setFillColor(sf::Color(0, 0, 0));
    play_text.setFillColor(sf::Color(0, 0, 0));
    exit_text.setCharacterSize(35);
    play_text.setCharacterSize(25);
    options_text.setCharacterSize(25);
  }
}

void Game::keyPressed(sf::Event event)
{
  // Input for navigating the menu
  if (event.key.code == sf::Keyboard::Up)
  {
    if (in_menu)
    {
      if (selected_play)
      {
        return;
      }
      else if (selected_option)
      {
        selected_option = !selected_option;
        selected_play   = !selected_play;
      }
      else
      {
        selected_exit   = !selected_exit;
        selected_option = !selected_option;
      }
    }
  }
  if (event.key.code == sf::Keyboard::Down)
  {
    if (in_menu)
    {
      if (selected_exit)
      {
        return;
      }
      else if (selected_play)
      {
        selected_option = !selected_option;
        selected_play   = !selected_play;
      }
      else
      {
        selected_exit   = !selected_exit;
        selected_option = !selected_option;
      }
    }
  }
  //---------------------------------------
  if (event.key.code == sf::Keyboard::Enter)
  {
    if (in_menu && selected_play)
    {
      in_menu        = false;
      gravity = 0;
      bird->setDirection(0, 0);
      bird->getSprite()->setPosition(
        origin_x - bird->getSprite()->getGlobalBounds().width / 2,
        origin_y - bird->getSprite()->getGlobalBounds().height / 2);
      no_of_pigs     = 3;
      pigs_remaining = no_of_pigs;
      level.loadLevel1(
        window, no_of_birds, no_of_pigs, pig_array, background, level_1_texture);
      score_text.setString("0");
      for (int i = 0; i < 5; ++i)
      {
        pig_array[i].setVisibility(true);
      }
    }
    else if (in_menu && selected_option)
    {
      background->getSprite()->setTexture(options_screen_texture);
      in_menu    = false;
      in_options = true;
    }
    else if (in_options)
    {
      background->getSprite()->setTexture(menu_screen_texture);
      in_options = false;
      in_menu    = true;
    }
    else if (in_menu && selected_exit)
    {
      window.close();
    }

    else if (game_won)
    {
      background->getSprite()->setTexture(menu_screen_texture);
      for (int i = 0; i < 10; ++i)
      {
        block_array[i].setVisibility(false);
      }
      for (int i = 0; i < no_of_pigs; i++)
      {
        pig_array[i].setVisibility(true);
      }
      in_menu      = true;
      game_won     = false;
      player_score = 0;
    }
    else
    {
      // Debug purposes for quickly increasing score and removing pigs
      player_score += 100;
      pigs_remaining--;
    }
  }
}

