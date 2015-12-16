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
		// Origin of SpaceShip


		m_velocity = XboxController::Instance().GetLeftStickAxis() * m_speed * p_deltaTime.asSeconds();
		m_position += m_velocity;
		m_playerSprite.setPosition(m_position);

	}
	if (XboxController::Instance().m_rightStickEnabled)
	{
		////  Angle from Analog Stick B
		m_angle = atan2(XboxController::Instance().GetRightStickAxis().y, XboxController::Instance().GetRightStickAxis().x);
		float temp = m_angle;
		temp *= (180 / M_PI_2) /2;

		// Sets your angle
		m_playerSprite.setRotation(temp);

	}


	
	m_playerSprite.setPosition(m_position);
	m_spriteRect = sf::IntRect(m_position.x, m_position.y, m_playerSprite.getTextureRect().width, m_playerSprite.getTextureRect().height);

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
	m_playerSprite.setPosition(m_position);
	m_spriteRect = sf::IntRect(m_position.x, m_position.y, m_playerSprite.getTextureRect().width, m_playerSprite.getTextureRect().height);
}

sf::IntRect Player::GetRectum()
{
	return m_spriteRect;
}
