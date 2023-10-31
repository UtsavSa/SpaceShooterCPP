#include "Game.h"
#include"Bullet.h"
#include"player.h"
#include"Enemy.h"



void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(900, 600),"SwagShooter of Space", sf::Style::Close |sf::Style::Fullscreen);
	this->window->setFramerateLimit(120);

	this->window->setVerticalSyncEnabled(false);

}

void Game::initTextures()
{


	this->textures["BULLET"] = new sf::Texture();


	this->textures["BULLET"]-> loadFromFile("Texture/bullett.png");
	//this->textures["BULLET"] =textures.size(1);

	//sf::Sprite bulletSprite();
	//::bulletSprite.setScale(0.12f, 0.12f);
}

void Game::initBackground()
{
	if (this->texture.loadFromFile("Texture/spacebackground2.jpg")) {

		std::cout << "Failed to load background img!";

	}
	sf::Sprite sprite;
	this->sprite.setTexture(texture);
	this->sprite.setColor(sf::Color(250, 200, 200, 240));
	this->sprite.setScale(2.5f, 2.5f);


}

void Game::initGUI()
{
	//load fonts
	if (!this->font.loadFromFile("Fonts/Lora-Italic-VariableFont_wght.ttf"))
	
		std::cout << "Error to load font!";
	
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
	//init point text


}

void Game::initSystems()
{
	this->points = 0;
	this->health = 10;

}

void Game::initPlayer()
{

	this->player = new Player();


	
}

void Game::initEnemies()
{

	this->spawnTimerMax = 40.f;
	this->spawnTimer = this->spawnTimerMax;

}

Game::Game()
{


	this->initWindow();

	this->initTextures();
	this->initGUI();
	this->initSystems();
	this->initBackground();
	this->initPlayer();
	this->initEnemies();
}
 
Game::~Game()
{
	delete this->window;
	delete this->player;
	//Delete textures
	for (auto &i: this->textures)
	{
		delete i.second;

	}
	// delete bullets
	for (auto* i : this->bullets)
	{

		delete i;
	}
	//delete enemies
	for (auto* i : this->enemies)
	{

		delete i;
	}

}

void Game::updatePollEvents()
{

	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();

		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	// move a player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(this->textures["BULLET"],
				this->player->getPos().x+this->player->getBounds().width/2.f, 
			this->player->getPos().y,
			0.f,
			-1.f, 
			5.f));
		std::cout << "mouse pressed" << "\n";
	}



}

void Game::updateWorld()
{
}

void Game::updateCollision()
{

	//left world collision
	if (this->player->getBounds().left < 0.f) 
	{

		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	// right
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{

		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//top side
	if (this->player->getBounds().top < 0.f)
	{

		//this->player->setPosition(0.f, this->player->getBounds().left);
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}

	//bottom
	else if (this->player->getBounds().top +this->player->getBounds().height>=this->window->getSize().y)
	{

		//this->player->setPosition(0.f, this->player->getBounds().left);
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y-this->player->getBounds().height);
	}
}

void Game::updateGUI()
{


	std::stringstream ss;
	ss << "Points: "<< this->points;
	this->pointText.setString(ss.str());
	ss << "Health: " << this->points;
}

void Game::updateBullets()
{

	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top off screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			
			//delete bullet
			delete this->bullets.at(counter);
			
			this->bullets.erase(this->bullets.begin() + counter);
			

			
			--counter;
			std::cout << this->bullets.size() << "\n";
		}
		++counter;
	}

}

void Game::updateEnemies()
{

	//spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{

		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}


	//this->enemy = new Enemy(20.f, 20.f);
	unsigned counter = 0;

	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top off screen)
		if (enemy->getBounds().top + enemy->getBounds().height > this->window->getSize().y)
		{

			//delete enemy
			delete this->enemies.at(counter);

			this->enemies.erase(this->enemies.begin() + counter);
			--counter;
			
		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			delete this->enemies.at(counter);

			this->enemies.erase(this->enemies.begin() + counter);
			--counter;

		}
		++counter;
	}

}


void Game::updateCombat()
{

	//if (this->spawnTimer)
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;

		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{

			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{

				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
				


				enemy_deleted = true;

			}


		}
	}





}





void Game::run()
{

	while (this->window->isOpen())
	{
		this->update();
		this->render();

	}
}

void Game::update()
{

	this->updatePollEvents();
	

	this->updateInput();


	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
	this->updateWorld();
}

void Game::renderBackground(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}

void Game::renderGUI()
{

	this->window->draw(this->pointText);
}

void Game::render()
{
	this->window->clear();

	this->renderBackground(*this->window);

	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{

		bullet->render(this->window);

	}
	for (auto* enemy : this->enemies)
	{

		enemy->render(this->window);

	}
	for (auto* bullet : this->bullets)
	{

		bullet->render(this->window);

	}
	this->renderGUI();

	//this->enemy->render(this->window);
	this->window->display();


}
