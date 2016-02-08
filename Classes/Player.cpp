#include "stdafx.h"
#include "Player.h"




Player::Player()
{
}
Player::Player(sf::Texture& p_tex, sf::Vector2f p_pos)
{
	m_position = p_pos;
	m_tex = &p_tex;
	m_playerSprite.setTexture(p_tex);
	m_spriteRect = sf::IntRect(0, 0, 132, 24);
	m_playerSprite.setTextureRect(m_spriteRect);
	m_playerSprite.setPosition(p_pos);
	m_velocity = sf::Vector2f(0, 0);
	m_speed = 1;
	m_delay = 0;
	m_angle = 0;
	m_playerSprite.setOrigin(11, 12);
	m_playerSprite.setRotation(m_angle);
	m_alive = true;
	m_score = 0;
	m_health = 100;
}

Player::~Player()
{
}

void Player::Update(sf::Time p_deltaTime)
{
	m_delay -= p_deltaTime.asSeconds();

	//Check state of joystick Analog A
	/////////////////////////////////////////////

	if (XboxController::Instance().m_leftStickEnabled)
	{
		m_velocity = XboxController::Instance().GetLeftStickAxis() * m_speed * 0.0006f;
		m_position += m_velocity;
		m_playerSprite.setPosition(m_position);
		if (hostagePositions.size() < 1000)
		{
			hostagePositions.push_back(m_position);
		}
		if (hostagePositions.size() == 1000 && m_position != hostagePositions.at(0))
		{
			hostagePositions.erase(hostagePositions.begin());
			hostagePositions.push_back(m_position);
		}
	}
	if (XboxController::Instance().m_rightStickEnabled)
	{
		////  Angle from Analog Stick B
		m_angle = atan2(XboxController::Instance().GetRightStickAxis().y, XboxController::Instance().GetRightStickAxis().x);
		float temp = m_angle;
		temp *= (180 / M_PI_2) /2;

		// Sets your angle
		m_playerSprite.setRotation(temp);
		if (hostageRotations.size() < 1000)
		{
			hostageRotations.push_back(m_playerSprite.getRotation());
		}
		if (hostageRotations.size() == 1000 && m_playerSprite.getRotation() != hostageRotations.at(0))
		{
			hostageRotations.erase(hostageRotations.begin());
			hostageRotations.push_back(m_playerSprite.getRotation());
		}
	}
}

// Getters
///////////////////////////
sf::Vector2f Player::getPosition()
{
	return m_position;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

sf::Sprite Player::getSprite()
{
	return m_playerSprite;
}


float Player::getAngle()
{
	return m_angle;
}

bool Player::GetAlive()
{
	return m_alive;
}

// Setters

void Player::SetAlive(bool p_alive)
{
	m_alive = p_alive;
}

void Player::SetPosition(sf::Vector2f p_setPos)
{
	m_position = p_setPos;
}

int Player::GetScore()
{
	return m_score;
}

void Player::SetScore(int score)
{
	m_score = score;
}

int Player::GetHealth()
{
	return m_health;
}

void Player::SetHealth(int p_health)
{
	m_health = p_health;
}

float Player::getRotation()
{
	return m_playerSprite.getRotation();
}

sf::Vector2f Player::GetHostagePos()
{
	return hostagePositions.at(0);
}