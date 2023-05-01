#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <math.h>
#include <random>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "stopwatch.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

static std::default_random_engine engine1;

Snake::Snake() : hitSelf_(false), direction_(Direction (0,-1))
{
	engine1.seed(time(NULL));
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	int i=0;
	static std::uniform_int_distribution<int> snake_body_color(0,5);
	nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::radius_,
			Game::Height / 2 - SnakeNode::radius_ + (SnakeNode::radius_)*2*i), 0, 0));
	for (int i = 1; i < Snake::InitialSize; ++i)
	{
		nodes_.push_back(SnakeNode(sf::Vector2f(
			Game::Width / 2 - SnakeNode::radius_,
			Game::Height / 2 - SnakeNode::radius_ + SnakeNode::radius_ *2*i), snake_body_color(engine1)));
	}
}

Direction Snake::b_to_a_direction(const sf::Vector2f& a, const sf::Vector2i& b) {
	double x1 = a.x, x2 = b.x, y1 = a.y, y2 = b.y;
	double length = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	//two circumstances that may invalid the direction
	if (x2<0||x2>Game::Width) return Direction(0,0);
	if (y2<0||y2>Game::Height) return Direction(0,0);
	return Direction((x2-x1)/length, (y2-y1)/length);
}

//to judge if the angle between the current direction and the target direction is too big for snake to move
bool Snake::is_valid(const Direction& a, const Direction& b) {
	//to judge if the target direction is invalid
	if (b.x==0&&b.y==0) 	
		return false;
	return a.x*b.x+a.y*b.y>=-sqrt(1/2);
}

void Snake::handleInput(sf::RenderWindow& window)
{
	Direction direction (0,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction.x = 0, direction.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction.x = 0, direction.y = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction.x = -1, direction.y = 0;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction.x = 1, direction.y = 0;
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		direction = b_to_a_direction(nodes_[0].getPosition(), sf::Mouse::getPosition(window));

	if(is_valid(direction_, direction)) 
		direction_ = direction;
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

int Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds())) {
			toRemove = it;
			break;
		} 
	}

	//remember the color of the fruit that has been eaten
	int k = toRemove!=fruits.end() ? toRemove->color_ : 5;

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		//if color is black or brown, don't grow
		int loop_num = toRemove->color_<2 ? 0 : toRemove->color_-1;
		for(int i=0; i<loop_num; ++i) {
			grow();
		}
		fruits.erase(toRemove);
	}
	return k;
}

void Snake::grow()	
{
	static std::uniform_int_distribution<int> fillcolor(0,5);
	nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
		nodes_[nodes_.size() - 1].getPosition().y),fillcolor(engine1),
		nodes_[nodes_.size() - 1].getangle()));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];
	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	//the move of snakebody, which only needs to follow the node in front of it
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition(), nodes_.at(i-1).getangle());
	}

	//the move of snakehead, which involves setting the angle for rotation
	double angle;
	if(direction_.y == 0) {
		if(direction_.x >= 0)	angle = -90;
		else	angle = 90;
	}
	else {
		if(direction_.y > 0)
			angle = 180+atan(-direction_.x/direction_.y)/3.14159265354*180;
		else 
			angle = atan(-direction_.x/direction_.y)/3.14159265354*180;
	}
	nodes_[0].move(SnakeNode::radius_*2*direction_.x, SnakeNode::radius_*2*direction_.y,angle);
}

void Snake::render(sf::RenderWindow& window)
{
	nodes_[0].render(window,0);
	for (int i=0; i<nodes_.size(); ++i)
		nodes_[i].render(window);
}