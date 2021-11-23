#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = rand() % 5 + 3; 
	this->type = 0;
	this->speed = -(rand()% 4+3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

Enemy::Enemy(sf::Texture* texture,float pos_x, float pos_y)
{
	this->initVariables();
	this->sprite.setTexture(*texture);
	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

//Functions
void Enemy::update()
{
	this->sprite.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}