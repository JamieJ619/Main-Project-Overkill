#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Graphics\Sprite.hpp"
class Tile
{
public:
	Tile();
	Tile(sf::Sprite, sf::Vector2f);
	~Tile();

	enum m_texture{ MAZE, GROUND};
	m_texture tex;



	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f);
	void SetSprite(sf::Sprite);

	void loadLevelOne();

private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};

