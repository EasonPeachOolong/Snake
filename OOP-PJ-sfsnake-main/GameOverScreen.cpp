#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SettingScreen.h"
#include "stopwatch.h"

using namespace sfSnake;

extern Stopwatch sw;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	float time = sw.getMicroseconds() / 1e6;
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nUsing Time: " + std::to_string(time) + " s!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit"
		"\n\nPress [TAB] to setup");
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		sw.start();
		Game::Screen = std::make_shared<GameScreen>();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		Game::Screen = std::make_shared<SettingScreen>();
	}
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
}