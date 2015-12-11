#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Time.hpp"
class XboxController
{
public:

	const int m_DEADZONEA, m_DEADZONEB;
	bool m_leftStickEnabled;
	bool m_rightStickEnabled;
	bool m_rightBumperEnabled;
	sf::Vector2f m_leftAnalogStick;
	sf::Vector2f m_rightAnalogStick;
	float m_rightBumper;
	void Update(sf::Time p_deltaTime);
	sf::Vector2f GetLeftStickAxis();
	sf::Vector2f GetRightStickAxis();
	static XboxController& Instance();
private:
	XboxController();
};


