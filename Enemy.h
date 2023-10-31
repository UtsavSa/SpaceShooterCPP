#pragma once


#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>




class Enemy
{


private:

	unsigned pointCount;
	sf::CircleShape shape;
	
	int type;
	int hp;
	int hpMax;
	int damage;
	int points;
	float speed;


	void initVariables();
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();


	//Accessor
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	//Functions
	void update();
	void render(sf::RenderTarget * target);

};

