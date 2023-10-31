#include "Bullet.h"
#include"Player.h"

//Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dirX, float dirY, float movement_speed)
//{
//}

void Bullet::initSprite()
{
	sf::Texture bulletTexture;
	if (!bulletTexture.loadFromFile("bullet.png")) {

		std::cout << "couldn't load file, bullet.cpp bullet.initSprite!";
	}
	sf::Sprite bulletSprite(bulletTexture);
	bulletSprite.setScale(0.25f, 0.25f);

	
}

Bullet::Bullet()
{
	this->sprite.setTexture(this->texture);

	// Resize the sprite
	this->sprite.setScale(0.25f, 0.25f);
	this->movementSpeed = 0;
	
}

Bullet::Bullet(sf::Texture *texture, float pos_x, float pos_y, float dirX, float dirY, float movement_speed)
{
	this->shape.setTexture(*texture);
	this->shape.setPosition(pos_x, pos_y);



	this->direction.x = dirX;
	this->direction.y = dirY;
	this->movementSpeed = movement_speed;

}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Bullet::update()
{

	// movement update

	this->shape.move(this->movementSpeed * this->direction);


}

void Bullet::render(sf::RenderTarget* target)
{

	target->draw(this->shape);
}
