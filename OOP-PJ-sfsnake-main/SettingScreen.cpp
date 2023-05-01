#include <SFML/Graphics.hpp>
#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"
#include "GameOverScreen.h"

using namespace sfSnake;

SettingScreen::SettingScreen() {
    font_.loadFromFile("Fonts/game_over.ttf");
    questions_.setFont(font_);
    questions_.setString(
        "1.background color"
        "\n\n\n\n2.need grid lines?"
        "\n\n\n\n3.grid lines's color"
        "\n\n\n\npress [Enter] to save");
    questions_.setFont(font_);
    questions_.setColor(sf::Color::Magenta);
    choices_[0].setString("[A]Black");
    choices_[1].setString("[B]White");
    choices_[2].setString("[C]Brown");
    choices_[3].setString("[Y]Yes");
    choices_[4].setString("[N]No");
    choices_[5].setString("[D]Black");
    choices_[6].setString("[E]White");
    choices_[7].setString("[F]Brown");
    choices_[0].setPosition(sf::Vector2f(0,60));
    choices_[1].setPosition(sf::Vector2f(210,60));
    choices_[2].setPosition(sf::Vector2f(420,60));
    choices_[3].setPosition(sf::Vector2f(0,180));
    choices_[4].setPosition(sf::Vector2f(210,180));
    choices_[5].setPosition(sf::Vector2f(0,300));
    choices_[6].setPosition(sf::Vector2f(210,300));
    choices_[7].setPosition(sf::Vector2f(420,300));
    for (int i=0;i<8;i++){
        choices_[i].setFont(font_);
        choices_[i].setColor(sf::Color::Cyan);
    }     

}

void SettingScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            Game::Screen = std::make_shared<MenuScreen>();
        int i;
        for (i=0;i<3&&choices_[i].getColor()!=sf::Color::Green;i++);    
        switch (i)
        {
            case 0: Game::BG_color=sf::Color::Black;break;
            case 1: Game::BG_color=sf::Color::White;break;
            case 2: Game::BG_color=sf::Color(128,64,0);break;
        }
        for (i=3;i<5&&choices_[i].getColor()!=sf::Color::Green;i++);    
        switch (i)
        {
            case 3: Game::grid_on=true;break;
            case 4: Game::grid_on=false;return;
        }
        for (i=5;i<8&&choices_[i].getColor()!=sf::Color::Green;i++);
        switch (i)
        {
            case 6: Game::grid_color=sf::Color(255,255,255,64);break;
            case 5: Game::grid_color=sf::Color(0,0,0,64);break;
            case 7: Game::grid_color=sf::Color(128,64,0,64);break;
        }
    }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        choices_[0].setColor(sf::Color::Green);
        choices_[1].setColor(sf::Color::Yellow);
        choices_[2].setColor(sf::Color::Yellow);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
        choices_[1].setColor(sf::Color::Green);
        choices_[0].setColor(sf::Color::Yellow);
        choices_[2].setColor(sf::Color::Yellow);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
        choices_[2].setColor(sf::Color::Green);
        choices_[1].setColor(sf::Color::Yellow);
        choices_[0].setColor(sf::Color::Yellow);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
        choices_[3].setColor(sf::Color::Green);
        choices_[4].setColor(sf::Color::Yellow);
        for (int i=5;i<8;i++){
            choices_[i].setColor(sf::Color::Yellow);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        choices_[4].setColor(sf::Color::Green);
        choices_[3].setColor(sf::Color::Yellow);
        for (int i=5;i<8;i++){
            choices_[i].setColor(sf::Color(192,192,192));
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if (choices_[5].getColor()==sf::Color(192,192,192)) return;
        choices_[5].setColor(sf::Color::Green);
        choices_[6].setColor(sf::Color::Yellow);
        choices_[7].setColor(sf::Color::Yellow);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
        if (choices_[5].getColor()==sf::Color(192,192,192)) return;
        choices_[6].setColor(sf::Color::Green);
        choices_[5].setColor(sf::Color::Yellow);
        choices_[7].setColor(sf::Color::Yellow);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        if (choices_[5].getColor()==sf::Color(192,192,192)) return;
        choices_[7].setColor(sf::Color::Green);
        choices_[6].setColor(sf::Color::Yellow);
        choices_[5].setColor(sf::Color::Yellow);
    }
}

void SettingScreen::update(sf::Time delta) {}

void SettingScreen::render(sf::RenderWindow& window)
{
	window.draw(questions_);
	for (int i=0;i<8;i++){
        window.draw(choices_[i]);
    }
}
