#include "Menu.h"

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Font/Scorefont.ttf"))
	{

	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(72);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));


	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

}

Menu::~Menu()
{
}

void Menu::render(sf::RenderTarget* target)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		target->draw(this->menu[i]);
	}
}

void Menu::Moveup()
{
	if (selecteditem - 1 >= 0)
	{
		menu[selecteditem].setFillColor(sf::Color::White);
		selecteditem--;
		menu[selecteditem].setFillColor(sf::Color::Cyan);
	}
}

void Menu::Movedown()
{
	if (selecteditem + 1 < MAX_ITEMS)
	{
		menu[selecteditem].setFillColor(sf::Color::White);
		selecteditem++;
		menu[selecteditem].setFillColor(sf::Color::Cyan);
	}
}