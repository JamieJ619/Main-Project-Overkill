#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Joystick.hpp"
#include "XboxController.h"
#define _USE_MATH_DEFINES
#include <math.h>
#pragma once
class Hostage
{
public:
	Hostage();
	Hostage(sf::Texture&, sf::Vector2f p_pos);
	~Hostage();

	void Update(sf::Vector2f p_targetPos, float p_targetRotation);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	bool getRescue();
	void setRescue(bool);

private:
	sf::Texture * m_tex;
	sf::Sprite m_hostageSprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::IntRect m_spriteRect;
	float m_speed;
	sf::Vector2f m_origin;
	bool isRescued;
};

