#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}

Enemy::Enemy(sf::Sprite p_spr, sf::Vector2f p_position, float p_velocity)
{
	m_sprite = p_spr;
	m_position = p_position;
	m_sprite.setPosition(m_position);
	m_velocity = p_velocity;
	m_alive = true;
	canMoveLeft = true;
	//m_angle = 0;
	//m_sprite.setRotation(m_angle);
}

Enemy::~Enemy()
{
	
}

sf::Sprite Enemy::GetSprite()
{
	return m_sprite;
}

sf::Vector2f Enemy::GetPosition()
{
	return m_position;
}

void Enemy::SetPosition(sf::Vector2f p_position)
{
	m_position = p_position;
	m_sprite.setPosition(m_position);
}

void Enemy::update(sf::Vector2f p_targetPos, sf::Time p_deltaTime)
{
	// fix temp to be p_deltaTime.asMicroSeconds() later.. something buggy with the time 
	//float temp = 0.01f;
	float temp = 0.01f;
	/*if (m_position.x < p_targetPos.x)
	{
		m_position.x += m_velocity * temp;
	}
	if (m_position.x > p_targetPos.x)
	{
		m_position.x -= m_velocity * temp;
	}
	if (m_position.y < p_targetPos.y)
	{
		m_position.y += m_velocity * temp;
	}
	if (m_position.y > p_targetPos.y)
	{
		m_position.y -= m_velocity * temp;
	}*/

	// going from bottom right to left
	if (m_position.x > 150 && canMoveLeft == true )
	{
		m_position.x -= m_velocity * temp;
		canMoveUp = true;
		canMoveDown = false;
		canMoveRight = false;
	}
	// going from bottom left to top left
	if (m_position.x < 150 && m_position.y > 80 && canMoveUp == true)
	{
		m_position.y -= m_velocity * temp;
		canMoveLeft = false;
		canMoveDown = false;
		canMoveRight = true;
	}
	// going from top left to top right
	if (m_position.y < 80 && canMoveRight == true)
	{
		m_position.x += m_velocity * temp;
		canMoveDown = true;
		canMoveLeft = false;
		canMoveUp = false;
	}
	// going from top right to bottom right
	if (m_position.x > 700 && canMoveDown == true)
	{
		m_position.y += m_velocity * temp;
		//canMoveLeft = true;
		canMoveRight = false;
		canMoveUp = false;
	}
	if (m_position.x > 700 && m_position.y > 480)
	{
		canMoveLeft = true;
	}

	m_angle = -atan2(m_position.x - p_targetPos.x, m_position.y - p_targetPos.y);
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_angle * 57.2957795);   // converting from radians to degrees
}

bool Enemy::GetAlive()
{
	return m_alive;
}

void Enemy::SetAlive(bool p_alive)
{
	m_alive = p_alive;
}