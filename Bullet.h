#pragma once

//#include "Bullet.h"
#include"Player.h"

#include<SFML/Graphics.hpp>
#include<iostream>


class Bullet
{
private:
	sf::Sprite shape;
	//sf::Texture* texture;
	sf::Texture texture;
	sf::Sprite sprite;


	sf::Vector2f direction;
	float movementSpeed;
	


public:

	Bullet();
	void initSprite();
	Bullet(sf::Texture *texture, float pos_x, float pos_y,float dirX, float dirY, float movement_speed);
	virtual ~Bullet();

	// Accessor
	const sf::FloatRect getBounds() const;


	void update();
	void render(sf::RenderTarget* target);
};

