#include "stdafx.h"
#include "Bullet.h"
#include "SFML\System\Time.hpp"


Bullet::Bullet(sf::Vector2f positon, sf::Vector2f velocity, sf::Sprite p_sprite)
{
	m_position = positon;
	m_velocity = velocity;

	m_sprite = p_sprite;
}


Bullet::~Bullet()
{
}

void Bullet::Update(sf::Time p_deltaTime)
{
	m_position += (m_velocity *  1000.0f) * p_deltaTime.asSeconds();
	m_sprite.setPosition(m_position);
	bulletRectangle = sf::IntRect(m_position.x, m_position.y, 6, 6);
}
void Bullet::Rotate(float speed)
{
	m_sprite.rotate(speed);
}

sf::Vector2f Bullet::GetScreenCoordinates()
{
	return m_position;

}

sf::Sprite Bullet::GetSprite()
{
	return m_sprite;
}
sf::Vector2f Bullet::GetPosition()
{
	return m_position;
}

sf::IntRect Bullet::GetBulletRectangle()
{
	return bulletRectangle;
}