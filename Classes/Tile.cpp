#include "stdafx.h"
#include "Tile.h"


Tile::Tile(sf::Sprite p_spr, sf::Vector2f p_position)
{
	m_sprite = p_spr;
	m_position = p_position;
	m_sprite.setPosition(m_position);
}
Tile::Tile()
{

}

sf::Sprite Tile::GetSprite()
{
	return m_sprite;
}

sf::Vector2f Tile::GetPosition()
{
	return m_position;
}

void Tile::SetPosition(sf::Vector2f p_position)
{
	m_position = p_position;
}

void Tile::SetSprite(sf::Sprite p_spr)
{
	m_sprite = p_spr;
}

void Tile::loadLevelOne()
{

}

Tile::~Tile()
{
}
