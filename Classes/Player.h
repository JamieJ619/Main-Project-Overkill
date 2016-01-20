#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Joystick.hpp"
#include "XboxController.h"
#define _USE_MATH_DEFINES
#include <math.h>


class Player
{
public:
	// Default Constructor
	Player();
	// Destructor
	~Player();
	// Overloaded Constructor
	Player(sf::Texture&, sf::Vector2f p_pos);


	void Update(sf::Time p_deltaTime);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getAngle();
	sf::Sprite getSprite();
	void Shoot(int);
	bool GetAlive();
	void SetAlive(bool);
	void SetPosition(sf::Vector2f);


private:
	float m_delay;
	sf::Vector2f m_origin;
	sf::Vector2f m_analogA;
	sf::Vector2f m_analogB;
	sf::Vector2f m_bulletVel;
	int m_width;
	int m_height;
	float m_angle;
	bool m_alive;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_speed;
	sf::Texture * m_tex;
	sf::IntRect m_spriteRect;
	sf::Sprite m_playerSprite;
};
