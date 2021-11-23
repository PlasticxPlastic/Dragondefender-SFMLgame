#include "Item.h"

Item::Item(sf::Texture* texture ,float pos_x,float pos_y,int type)
{
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
	this->itemtype = type;
}

Item::~Item()
{
}

const sf::FloatRect Item::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Item::update()
{
}

void Item::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
