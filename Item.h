#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Item
{
public:
	Item(sf::Texture* texture,float pos_x,float pos_y,int type);
	virtual ~Item();
	
	const sf::FloatRect getBounds() const;

	int getType()
	{
		return itemtype;
	}

	void update();
	void render(sf::RenderTarget* target);

private:
	sf::Sprite sprite;
	int itemtype;
};

