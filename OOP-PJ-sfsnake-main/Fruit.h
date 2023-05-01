#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <string>

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position, int color);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

private:
	sf::CircleShape shape_;
	sf::Texture texture;
	std::string color_pic[5] = {"black","brown","green","blue","red"};	//store pictures of different colors

public:
	static const float Radius;
	int color_;
};
}

#endif