#include "stdafx.h"
#include "CollisonManager.h"
#include "Player.h"

void CollisonManager::CheckWalleyJobs(Player * p_player, std::vector<sf::IntRect> * p_tileList)
{
	sf::IntRect playerrectum = p_player->GetRectum();

	for (int i = 0; i < p_tileList->size(); i++)
	{
		sf::IntRect rectum = p_tileList->at(i);
		if (playerrectum.intersects(rectum))
		{

			bool isLeft = (p_player->getPosition().x < rectum.left);
			bool isRight = (p_player->getPosition().x + p_player->getSprite().getTextureRect().width > rectum.left + rectum.width);

			bool isAbove = (p_player->getPosition().y < rectum.top);
			bool isBelow = (p_player->getPosition().y > rectum.top + rectum.height);

			if (isLeft && !isAbove && !isBelow)
				p_player->SetPosition(sf::Vector2f(p_player->getPosition().x -1, p_player->getPosition().y));

			if (isRight && !isAbove && !isBelow)
				p_player->SetPosition(sf::Vector2f(p_player->getPosition().x + 1, p_player->getPosition().y));

			if (isAbove && !isRight && !isLeft)
				p_player->SetPosition(sf::Vector2f(p_player->getPosition().x, p_player->getPosition().y ));

			if (isBelow && !isRight && !isLeft)
				p_player->SetPosition(sf::Vector2f(p_player->getPosition().x, p_player->getPosition().y));
		}

	}
}
