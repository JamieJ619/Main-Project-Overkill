#include "stdafx.h"
#include "BulletManager.h"
#include "SFML\Graphics\RenderWindow.hpp"


BulletManager::BulletManager()
{
	m_bulletList = std::vector<Bullet>();
}



BulletManager::BulletManager(sf::Texture& p_tex)
{
	m_sprite.setTexture(p_tex);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 6, 6));
}


BulletManager::~BulletManager()
{
}

void BulletManager::AddBullet(sf::Vector2f m_playerPos, sf::Vector2f p_vel, sf::Sprite p_sprite)
{
	m_bulletList.push_back(Bullet(m_playerPos, p_vel, p_sprite ));
}

void BulletManager::Update(sf::Time p_deltaTime)
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		m_bulletList.at(i).Update(p_deltaTime);
		bulletRectangle = sf::IntRect(m_bulletList.at(i).GetPosition().x, m_bulletList.at(i).GetPosition().y, 6, 6);
		if (m_bulletList.at(i).GetScreenCoordinates().x > 800)
		{
			m_bulletList.erase(m_bulletList.begin() + i);
		}
		else if (m_bulletList.at(i).GetScreenCoordinates().y > 600)
		{
			m_bulletList.erase(m_bulletList.begin() + i);
		}
	}
}

void BulletManager::Draw(sf::RenderWindow& p_window)
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		p_window.draw(m_bulletList.at(i).GetSprite());

	}
}

sf::Sprite BulletManager::getSprite()
{
	return m_sprite;
}
sf::IntRect BulletManager::GetBulletRectangle()
{
	return bulletRectangle;
}
