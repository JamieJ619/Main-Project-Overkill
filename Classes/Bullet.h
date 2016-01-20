#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Time.hpp"
class Bullet
{
public:
	Bullet(sf::Vector2f positon, sf::Vector2f velocity, sf::Sprite);
	~Bullet();
	void Update(sf::Time);
	sf::Sprite GetSprite();
	sf::Vector2f GetScreenCoordinates();
	void Rotate(float speed);
	sf::Vector2f GetPosition();
	sf::IntRect GetBulletRectangle();
	sf::IntRect bulletRectangle;
private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_alive;
};

