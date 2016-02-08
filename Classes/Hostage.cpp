#include "stdafx.h"
#include "Hostage.h"


Hostage::Hostage()
{
}

Hostage::Hostage(sf::Texture& p_tex, sf::Vector2f p_pos)
{
	m_position = p_pos;
	m_tex = &p_tex;
	m_hostageSprite.setTexture(p_tex);
	m_spriteRect = sf::IntRect(0, 0, 32, 24);
	m_hostageSprite.setTextureRect(m_spriteRect);
	m_hostageSprite.setPosition(p_pos);
	m_hostageSprite.setOrigin(16, 12);
	m_velocity = sf::Vector2f(0, 0);
	isRescued = false;
}


Hostage::~Hostage()
{
}

void Hostage::Update(sf::Vector2f p_targetPos, float p_targetRotation)
{
	if (isRescued == true)
	{
		m_position = p_targetPos;
		m_hostageSprite.setPosition(m_position);
		m_hostageSprite.setRotation(p_targetRotation);
	}

}

sf::Vector2f Hostage::getPosition()
{
	return m_position;
}

sf::Vector2f Hostage::getVelocity()
{
	return m_velocity;
}

sf::Sprite Hostage::getSprite()
{
	return m_hostageSprite;
}

bool Hostage::getRescue()
{
	return isRescued;
}

void Hostage::setRescue(bool p_rescue)
{
	isRescued = p_rescue;
}