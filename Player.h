#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>



class Player
{

private:
	sf::Sprite sprite;
	sf::Texture texture;


	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();


public:

	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	// Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);


	//Functions

	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget &target);

};

