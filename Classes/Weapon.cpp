#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon()
{
}

Weapon::Weapon(sf::Sprite spr, sf::Vector2f p_position)
{

}

Weapon::~Weapon()
{
}


sf::Sprite Weapon::GetSprite()
{
	return m_sprite;
}

sf::Vector2f Weapon::GetPosition()
{
	return m_position;
}

void Weapon::SetPosition(sf::Vector2f p_position)
{
	m_position = p_position;
}

void Weapon::SetSprite(sf::Sprite p_spr)
{
	m_sprite = p_spr;
}