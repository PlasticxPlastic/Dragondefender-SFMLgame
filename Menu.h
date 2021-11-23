#pragma once
#include<SFML/Graphics.hpp>
#define MAX_ITEMS 3
class Menu
{
public:
	Menu(float width, float height);
	~Menu();
	void render(sf::RenderTarget* target);
	void Moveup();
	void Movedown();
	int GetPressedItem() { return selecteditem; }

private:
	int selecteditem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

};

