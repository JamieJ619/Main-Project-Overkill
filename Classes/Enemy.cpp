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
	float temp = 0.01f;
	if (m_position.x < p_targetPos.x)
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
	}
	m_angle = atan2(p_targetPos.x, p_targetPos.y);
	float tempAngle = m_angle;
	tempAngle *= 360;  // its close to being exact think may be my size of the enemy sprite too big 
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(tempAngle);
}