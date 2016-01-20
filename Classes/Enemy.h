#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
class Enemy
{
public:
	Enemy();
	Enemy(sf::Sprite, sf::Vector2f, float);
	~Enemy();

	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f);
	void update(sf::Vector2f p_targetPos, sf::Time);
	bool GetAlive();
	void SetAlive(bool p_alive);

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float  m_velocity;
	float m_angle;
	bool m_alive;
};

