#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
class Direction
{
public:
	double x,y;
	Direction(double x_, double y_) : x(x_), y(y_) {};
	//in order to get the mouse direction, I substitute the previous four buttons with Direction
	//Up, Down, Left and Right can also be changed into Dircection easily
};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	int checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;

	unsigned getSize() const;

private:
	void move();
	void grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	
	bool is_valid(const Direction& a, const Direction& b);	
	Direction b_to_a_direction(const sf::Vector2f& a, const sf::Vector2i& b);

	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;
	sf::Vector2f mouse_direction_;
	
	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif