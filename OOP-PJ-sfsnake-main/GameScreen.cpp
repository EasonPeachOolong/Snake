#include <SFML/Graphics.hpp>

#include <random>
#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include "stopwatch.h"

using namespace sfSnake;

extern Stopwatch sw;

static std::default_random_engine engine;

GameScreen::GameScreen() : snake_()
{
	engine.seed(time(NULL));
	//the fixed total number of fruits are 24
	//first generate 6 black or brown fruits randomly
	for (int i=0; i < 6; ++i) {
		std::uniform_int_distribution<int> color_creator(0,1);
		generateFruit(color_creator(engine));
	}

	//then generate 18 fruits, green, blue or red, randomly
	for (int i=0; i < 18; ++i) {
		std::uniform_int_distribution<int> color_creator2(2,4);
		generateFruit(color_creator2(engine));
	}

	//draw the grids
	if(Game::grid_on == false)	return;
	for (int i=0; i < Game::Width; i += SnakeNode::radius_*2) {
		lines.push_back(sf::Vertex(sf::Vector2f(i,0),sf::Color(Game::grid_color)));
		lines.push_back(sf::Vertex(sf::Vector2f(i,Game::Height),sf::Color(Game::grid_color)));
	}
	for (int i=0;i<Game::Height; i += SnakeNode::radius_*2) {
		lines.push_back(sf::Vertex(sf::Vector2f(0,i),sf::Color(Game::grid_color)));
		lines.push_back(sf::Vertex(sf::Vector2f(Game::Width,i),sf::Color(Game::grid_color)));
	}
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	snake_.update(delta);
	//generate the fruit which has been eaten
	int i = snake_.checkFruitCollisions(fruit_);
	
	if(i < 5) {
		generateFruit(i);
	}

	if (snake_.hitSelf()) {
		sw.stop();
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
	}
}

void GameScreen::render(sf::RenderWindow& window)
{
	if (Game::grid_on) {
		window.draw(&lines[0], lines.size(), sf::Lines);
	}
	
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit(int i)
{	
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::radius_*2);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::radius_*2);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine)), i));
}

