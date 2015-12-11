#include "stdafx.h"
#include "XboxController.h"
#include "SFML\Window\Joystick.hpp"


XboxController::XboxController()
:m_DEADZONEA(50), m_DEADZONEB(80)
{

}

sf::Vector2f XboxController::GetLeftStickAxis()
{
	return m_leftAnalogStick;
}

sf::Vector2f XboxController::GetRightStickAxis()
{
	return m_rightAnalogStick;
}

XboxController& XboxController::Instance()
{
	static XboxController instance;
	return instance;
}

void XboxController::Update(sf::Time p_deltaTime)
{
	m_leftAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
	m_rightAnalogStick = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));


	// Updates Left Stick
	if (m_leftAnalogStick.x > m_DEADZONEA || m_leftAnalogStick.x < -m_DEADZONEA || m_leftAnalogStick.y > m_DEADZONEA || m_leftAnalogStick.y < -m_DEADZONEA)
	{
		m_leftStickEnabled = true;
	}
		
	else
		m_leftStickEnabled = false;

	// Updates Right Stick
	if (m_rightAnalogStick.x > m_DEADZONEB || m_rightAnalogStick.x < -m_DEADZONEB || m_rightAnalogStick.y > m_DEADZONEB || m_rightAnalogStick.y < -m_DEADZONEB)
	{
		m_rightStickEnabled = true;
	}
		
	else
		m_rightStickEnabled = false;

	// Updates Right Bumper
	if (sf::Joystick::isButtonPressed(0, 5))
	{
		m_rightBumperEnabled = true;
	}

	else
		m_rightBumperEnabled = false;

}