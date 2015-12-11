#pragma once
#include <vector>
#include "Bullet.h"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Texture.hpp"
class BulletManager
{
public:
	BulletManager();
	BulletManager(sf::Texture&);
	~BulletManager();

	void Update(sf::Time);
	void Draw(sf::RenderWindow& p_window);
	void AddBullet(sf::Vector2f m_playerPos, sf::Vector2f, sf::Sprite);

	sf::Sprite getSprite();
	sf::IntRect bulletRectangle;
	sf::IntRect GetBulletRectangle();

private:
	std::vector<Bullet> m_bulletList;
	sf::Sprite m_sprite;
};
