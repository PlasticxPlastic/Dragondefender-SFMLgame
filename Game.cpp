#include "Game.h"

//Private functions


void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1440, 720), "Dragon Defender", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet3.png");
	this->enemy1.loadFromFile("Textures/enemy1.png");
	this->enemy2.loadFromFile("Textures/enemy2.png");
	this->enemy3.loadFromFile("Textures/enemy3.png");
	this->enemy4.loadFromFile("Textures/enemy4.png");
	this->Winditem.loadFromFile("Textures/winditem.png");
	this->Fireitem.loadFromFile("Textures/Fireitem.png");
	this->HPitem.loadFromFile("Textures/hpitem.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Font/Scorefont.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(1220.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(30);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over! Press M to back to menu");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initMenu()
{
	this->menu = new Menu(1440.f,720.f);
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/BG3.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);


	if (!this->Menubackgroundtex.loadFromFile("Textures/X7.jpg"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->Menubackground.setTexture(this->Menubackgroundtex);


	if (!this->GameoverBGtex.loadFromFile("Textures/X10.jpg"))
		std::cout << "ERROROROROROROORORORORO" << "\n";
	this->GameoverBG.setTexture(this->GameoverBGtex);

	if (!this->LBBGtex.loadFromFile("Textures/X11.jpg"))
		std::cout << "sdadsdsdadsad" << "\n";
	this->LBBG.setTexture(this->LBBGtex);
	
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{

	this->spawnTimerMax = 30.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initSounds()
{
	fireblow.loadFromFile("Sounds/Fireblow.wav");
	if (!Die.loadFromFile("Sounds/diesound.wav"))
	{
		std::cout << "XXX" << "\n";
	}
	Button.loadFromFile("Sounds/Button.wav");
	Enterbt.loadFromFile("Sounds/Enter.wav");
}

//Con/Des
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initMenu();
	this->initWorld();
	this->initSystems();
	this->initPlayer();
	this->initEnemies();
	this->initSounds();
	
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}

	//Delete items
	for (auto* i : this->items)
	{
		delete i;
	}
}

int Game::getPoint()
{
	return this->points;
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
			this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	ScoreList scorelist("score/score.txt");
	scorelist.loadFile();
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (gameover == true)
		{
			switch (e.type)
			{
			case sf::Event::TextEntered:
				std::cout << e.text.unicode << std::endl;

				if (e.text.unicode == 8)
				{
					if (name.size() > 0) name.erase(name.end() - 1);
				}
				if (e.text.unicode == 13)
				{
					scorelist.addEntry(name, this->points);
					this->points = 0;
					menustate = true;
					gamestate = false;
					gameover = false;
					name = "";
					this->spawnTimer = .3f;
					this->speedplayer = 1;
					this->player->resetHp();
				}
				if ((e.text.unicode >= 'A' && e.text.unicode <= 'Z') || (e.text.unicode >= 'a' && e.text.unicode <= 'z'))
				{
					if (name.size() < 10)name.push_back(e.text.unicode);
				}
				std::cout << name << std::endl;
				break;
			default:
				break;
			}
		}
		if (menustate == true && gameover == false)
		{
			switch (e.type)
			{
			case sf::Event::KeyReleased:
				switch (e.key.code)
				{
				case sf::Keyboard::Up:
					menu->Moveup();
					this->Buttonsound.setBuffer(Button);
					this->Buttonsound.setVolume(20.f);
					this->Buttonsound.play();
					break;
				case sf::Keyboard::Down:
					menu->Movedown();
					this->Buttonsound.setBuffer(Button);
					this->Buttonsound.setVolume(20.f);
					this->Buttonsound.play();
					break;
				case sf::Keyboard::Space:
					switch (menu->GetPressedItem())
					{
					case 0:
						this->Enterbuttonsound.setBuffer(Enterbt);
						this->Enterbuttonsound.setVolume(10.f);
						this->Enterbuttonsound.play();
						gamestate = true;
						menustate = false;
						break;
					case 1:
						gamestate = false;
						menustate = false;
						leaderboardstate = true;
						this->Enterbuttonsound.setBuffer(Enterbt);
						this->Enterbuttonsound.setVolume(10.f);
						this->Enterbuttonsound.play();
						break;
					case 2:
						this->Enterbuttonsound.setBuffer(Enterbt);
						this->Enterbuttonsound.setVolume(10.f);
						this->Enterbuttonsound.play();
						this->window->close();
						break;
					}
				}
				break;
			}
		}
		if (leaderboardstate == true)
		{
			switch (e.type)
			{
			case sf::Event::KeyReleased:
				switch (e.key.code)
				{
				case sf::Keyboard::Escape:
					leaderboardstate = false;
					menustate = true;
					break;
				}
				break;
			}
		}
	}
	scorelist.saveFile();
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-(speedplayer), 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(speedplayer, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -(speedplayer));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, speedplayer);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + 120,
				this->player->getPos().y + 40,
				1.f,
				0.f,
				7.f
			)
		);
		this->fireblowsound.setBuffer(fireblow);
		this->fireblowsound.setVolume(5.f);
		this->fireblowsound.play();
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Points: " << this->points;

	this->pointText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter; 
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += .3f;
	int randtexture;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		randtexture = rand() % 4;
		if(randtexture == 1)
			this->enemies.push_back(new Enemy(&enemy1,1400.f, rand()%(670 - 40+1)+40));
		else if(randtexture == 2)
			this->enemies.push_back(new Enemy(&enemy2,1400.f, rand()%(670 - 40 + 1) + 40));
		else if(randtexture == 3)
			this->enemies.push_back(new Enemy(&enemy3,1400.f, rand()%(670 - 40 + 1) + 40));
		else if(randtexture == 0)
			this->enemies.push_back(new Enemy(&enemy4,1400.f, rand()%(670 - 40 + 1) + 40));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//Bullet culling (top of screen)
		if (enemy->getBounds().left < 0)
		{
			//Delete enemy
			this->player->loseHp(3);
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				randitemdrop = rand() % 100;
				if (randitemdrop > 80)
				{
					itemdrop = true;
				}
				if (itemdrop == true)
				{
					randitem = rand() % 3;
					if (randitem == 0)
					{
						this->items.push_back(new Item(&Winditem, enemies[i]->getBounds().left, enemies[i]->getBounds().top,1));
					}
					else if (randitem == 1)
					{
						this->items.push_back(new Item(&Fireitem, enemies[i]->getBounds().left, enemies[i]->getBounds().top,2));
					}
					else if (randitem == 2)
					{
						this->items.push_back(new Item(&HPitem, enemies[i]->getBounds().left, enemies[i]->getBounds().top,3));
					}
				}

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				this->Diesound.setBuffer(Die);
				this->Diesound.setVolume(5.f);
				this->Diesound.play();

				enemy_deleted = true;
				this->spawnTimer += 0.05f;
				std::cout << randitemdrop << "\n";
				itemdrop = false;
				randitemdrop = 0;
			}
		}
	}
	for (int i = 0; i < this->items.size(); i++)
	{
		item_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && item_deleted == false; k++)
		{
			if (this->items[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				if (this->items[i]->getType() == 1)
				{
					speedplayer = speedplayer + 0.05;
					delete this->items[i];
					this->items.erase(this->items.begin() + i);
					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);

					item_deleted = true;
				}
				else if (this->items[i]->getType() == 2)
				{
					delete this->items[i];
					this->items.erase(this->items.begin() + i);
					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);
					for (int j = 0; j < enemies.size(); j++)
					{
						delete this->enemies[j];
						this->enemies.erase(this->enemies.begin() + j);
					}
					item_deleted = true;
				}
				else if (this->items[i]->getType() == 3)
				{
					this->player->increaseHp();
					delete this->items[i];
					this->items.erase(this->items.begin() + i);
					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);
					item_deleted = true;
				}
			}
		}
	}
}

void Game::update()
{
	if (gamestate == true)
	{
		///////////////////////////////////////////
		this->updateInput();

		this->player->update();

		this->updateCollision();

		this->updateBullets();

		this->updateEnemies();

		this->updateCombat();

		this->updateGUI();

		this->updateWorld();
		//////////////////////////////////////////

	}
	
	
}

void Game::renderGUI()
{
	if (gamestate == true)
	{
		///////////////////////////////////////////////////
		this->window->draw(this->pointText);
		this->window->draw(this->playerHpBarBack);
		this->window->draw(this->playerHpBar);
		///////////////////////////////////////////////////
	}
}

void Game::renderWorld()
{
	if (gamestate == true)
	{
		////////////////////////////////////////////////
		this->window->draw(this->worldBackground);
		///////////////////////////////////////////////
	}
}

void Game::render()
{
	this->window->clear();
	if (leaderboardstate == true)
	{
		ScoreList scorelist("score/score.txt");
		scorelist.loadFile();
		this->window->draw(this->LBBG);
		sf::Text text;
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(40);
		int show_max_entry = 8;
		for (int i = 0; scorelist.get().size(); i++)
		{
			if (i >= show_max_entry)break;
			text.setPosition(350.f, 200 + (i * 40));
			text.setString(scorelist.get().at(i).getName());
			window->draw(text);
		}
		for (int i = 0; scorelist.get().size(); i++)
		{
			if (i >= show_max_entry)break;
			text.setPosition(900, 200 + (i * 40));
			text.setString(std::to_string(scorelist.get().at(i).getScore()));
			window->draw(text);
		}
	}

	if (gamestate == true)
	{
		//Draw world
		this->renderWorld();
		//////////////////////////////////////////////////////////////
		//Draw all the stuffs
		this->player->render(*this->window);

		for (auto* bullet : this->bullets)
		{
			bullet->render(this->window);
		}

		for (auto* enemy : this->enemies)
		{
			enemy->render(this->window);
		}

		for (auto* items : this->items)
		{
			items->render(this->window);
		}

		this->renderGUI();

		//Game over screen
		if (this->player->getHp() <= 0)
		{
			std::stringstream ss;
			gameover = true;
			this->window->draw(this->GameoverBG);
			text.setFont(font);
			text.setFillColor(sf::Color::White);
			text.setPosition(400.f, 340.f);
			text.setString("Enter your name : " + name + "_");
			this->window->draw(this->text);
			
		}
			
		/////////////////////////////////////////////////////////////
	}
	if (menustate == true)
	{
		this->window->draw(this->Menubackground);
		menu->render(this->window);

	}
	
	this->window->display();
}