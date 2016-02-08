#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#pragma once
class Weapon
{
public:
	Weapon();
	Weapon(sf::Sprite p_spr, sf::Vector2f p_position);
	~Weapon();

	enum m_texture {PISTOL, MACHINEGUN, SHOTGUN};
	m_texture tex;

	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f);
	void SetSprite(sf::Sprite);

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};

