#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include<map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include<string>

#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"







class Game
{

private:

	sf::RenderWindow* window;
	//sf::VideoMode videomode;
	//sf::Event ev;


	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	

	//Player
	Player* player;


	//background
	sf::Texture texture;
	sf::Sprite sprite;
	
	//systems
	unsigned points;
	int health;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	//Enemy* enemy;

	void initWindow();

	//Gui 
	sf::Font font;
	sf::Text pointText;
	

	void initTextures();
	void initBackground();
	void initGUI();
	void initSystems();
	void initPlayer();
	void initEnemies();


public:
	Game();
	virtual ~Game();


	void updatePollEvents();
	void updateInput();


	void updateWorld();
	void updateCollision();
	void updateGUI();
	void updateBullets();
	void updateEnemies();
	
	void updateCombat();


	void run();
	void update();
	void renderBackground(sf::RenderTarget&target);
	void renderGUI();
	void render();



};



