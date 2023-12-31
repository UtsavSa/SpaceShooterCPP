#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 7.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

}

void Player::initTexture()
{
	// Load a texture from file

	if (!this->texture.loadFromFile("Texture/ship.png"))

	{
		std::cout << "Error:Player:InitTexture:Counld not load file" << "\n";


	}
}

void Player::initSprite()
{
	//set the texture to the sprite

	this->sprite.setTexture(this->texture);

	// Resize the sprite
	this->sprite.scale(0.1f, 0.1f);


}

Player::Player()
{

	this->initVariables();
	this->initTexture();
	this->initSprite();

}

Player::~Player()
{



}

const sf::Vector2f& Player::getPos() const
{
	// TODO: insert return statement here
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const sf::Vector2f pos)
{

	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::move(const float dirX, const float dirY)
{

	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);

}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.5f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{

	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
	
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);


}
