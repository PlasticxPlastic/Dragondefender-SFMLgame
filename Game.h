#pragma once

#include<map>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include "Item.h"
#include "Menu.h"
#include "score.h"
#include "Scorelist.h"
#include <algorithm>
#include <fstream>
#include <vector>
#include<SFML/Audio.hpp>

class Game
{
private:
	bool gamestate = false;
	bool menustate = true;
	bool leaderboardstate = false;
	bool gameover = false;
	//Window
	sf::RenderWindow* window;

	//ITEM
	int randitemdrop;
	int randitem;
	bool itemdrop;
	bool item_deleted = false;

	sf::Vector2f ScreenSize = { 1440.f,720.f };

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Item*> items;
	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	sf::Texture Menubackgroundtex;
	sf::Sprite Menubackground;

	sf::Texture GameoverBGtex;
	sf::Sprite GameoverBG;
	std::string name = "";

	sf::Texture LBBGtex;
	sf::Sprite LBBG;


	//score
	sf::Text text;
	//sounds
	sf::Sound fireblowsound;
	sf::SoundBuffer fireblow;

	sf::Sound Diesound;
	sf::SoundBuffer Die;

	sf::Sound Buttonsound;
	sf::SoundBuffer Button;
	
	sf::Sound Enterbuttonsound;
	sf::SoundBuffer Enterbt;

	//Systems
	unsigned points;
	Menu* menu;

	//Player
	Player* player;
	float speedplayer = 1;
	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	sf::Texture enemy1;
	sf::Texture enemy2;
	sf::Texture enemy3;
	sf::Texture enemy4;
	sf::Texture HPitem;
	sf::Texture Fireitem;
	sf::Texture Winditem;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initMenu();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initSounds();

public:
	Game();
	virtual ~Game();

	//Score
	
	int getPoint();
	//Functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();

	void renderGUI();
	void renderWorld();
	void render();
};