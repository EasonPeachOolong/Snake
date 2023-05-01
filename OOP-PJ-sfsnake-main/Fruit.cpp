#include <SFML/Graphics.hpp>
#include <random>
#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 8.f;

//The fruits are initially generated in the gamescreen
Fruit::Fruit(sf::Vector2f position, int color) : color_(color)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	texture.loadFromFile("Fruits/"+ color_pic[color_] +".png");
	shape_.setTexture(&texture);
}

void Fruit::render(sf::RenderWindow& window)
{
	shape_.setTexture(&texture);
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}