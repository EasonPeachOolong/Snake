#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
#include <string>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position, int i, double angle = 0.f);
	SnakeNode(sf::Vector2f position, int i, int k);
	void setPosition(sf::Vector2f position, double angle);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset, double angle);

	void render(sf::RenderWindow& window);
	void render(sf::RenderWindow& window, int i);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	double getangle() const {return angle_;}

	static const float radius_;

private:
	double angle_;
	sf::Vector2f position_;
	sf::CircleShape shape_;
	sf::RectangleShape shape2_;
	sf::Texture texture;
	sf::Color fillcolor[6] = {sf::Color::Red,sf::Color::Blue,
						sf::Color(255,255,0),sf::Color::Green,
						sf::Color::Yellow, sf::Color::Magenta};
};
}

#endif