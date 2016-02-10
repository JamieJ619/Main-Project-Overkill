//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>
#include "XboxController.h"
#include "Player.h"
#include "BulletManager.h"
#include "Tile.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "Hostage.h"



// Variables
//////////////////
sf::Clock myClock;
sf::Time deltaTime;
sf::Texture m_playerTex;
sf::Texture m_hostageTex;
sf::Texture m_bulletTex;
sf::Texture m_hud;
Player player;
Hostage hostage;
BulletManager bulletManager2012;
sf::Sprite sprHud;
sf::Sprite sprMaze;
sf::Sprite sprEnd;
float timer = 0;
int bulletsFired = 0;
sf::IntRect m_spriteRect;
const float BULLETDELAY = 0.3f;
const float RELOADDELAY = 0.8f;

float timeSeconds = 0;
int timeMins = 0;

int bulletCounterForLevelCompleteText = 0;
int enemiesKilled = 0;
int friendliesSaved = 0;
int bulletsRemainingInHud = 6;

bool pushRight = false;
bool pushUp = false;

Tile tileMap[16][16];
Enemy em1, em2, em3, em5, em6, em7, em4;

enum GameStates{ menuState, gameSettings, playGameState, levelComplete, gameOver };

GameStates currentState = GameStates::menuState;
sf::View viewport((player.getPosition()), sf::Vector2f(360, 280));
sf::View radar(sf::Vector2f(300, 220), sf::Vector2f(60, 60));
int score;

sf::Sprite sprHealth;
sf::IntRect healthRect;
sf::Texture texHealthG;
sf::Texture texHealthY;
sf::Texture texHealthR;

SoundManager soundManager2014;

sf::Sprite sprCursor;
sf::IntRect m_cursorRect;
sf::Texture cursorImage;
sf::Vector2f cursorPosition;

bool soundEffectsEnabled = true;
bool backgroundMusicEnabled = true;
bool reloadingSound = true;
bool pressBtn = false;

bool pressedLastFrame = false;
bool pressedLastFrame1 = false;

int selectedButton = 1;
int newGame = 1;
int loadGame = 2;
int quitGame = 3;
int settings = 4;
float delay = 0;
//Settings Stuff
sf::Sprite sprSettingsScreen;
sf::IntRect m_settingsScreenRect;
sf::Texture settingsScreenImage;
//Menu Stuff
sf::Sprite sprMenu;
sf::IntRect m_menuRect;
sf::Texture menuImage;

sf::Sprite sprNewGame;
sf::IntRect m_newGameRect;
sf::Texture newGameImage;

sf::Sprite sprLoadGame;
sf::IntRect m_loadGameRect;
sf::Texture loadGameImage;

sf::Sprite sprQuitGame;
sf::IntRect m_quitGameRect;
sf::Texture quitGameImage;

sf::Sprite sprSettings;
sf::IntRect m_settingsRect;
sf::Texture settingsImage;

sf::Sprite sprLevelComplete;
sf::IntRect lcRect;
sf::Texture lcImage;

sf::Sprite sprGameOver;
sf::IntRect goRect;
sf::Texture goImage;

sf::Sprite sprControls;
sf::IntRect m_controlsRect;
sf::Texture controlsTex;

std::vector<Enemy> enemyList;

sf::Font font;
sf::Text text;
sf::Text timeText;

///////	LevelComplete Text
sf::Text scoreText;
sf::Text bulletsRemText;
sf::Text enemiesKilledText;
sf::Text shotsFiredText;
sf::Text friendliesSavedText;

bool saved = false;
// jamie's draw menu method
void DrawMenu(sf::RenderWindow & p_window)
{
	sprMenu.setTexture(menuImage);
	m_menuRect = sf::IntRect(0, 0, 800, 600);
	sprMenu.setTextureRect(m_menuRect);
	sprMenu.setPosition(sf::Vector2f(0, 0));

	sprNewGame.setTexture(newGameImage);
	m_newGameRect = sf::IntRect(0, 0, 190, 60);
	sprNewGame.setTextureRect(m_menuRect);
	sprNewGame.setPosition(sf::Vector2f(30, 450));
	sprNewGame.setScale(0.8, 0.8);

	sprLoadGame.setTexture(loadGameImage);
	m_loadGameRect = sf::IntRect(0, 0, 190, 60);
	sprLoadGame.setTextureRect(m_menuRect);
	sprLoadGame.setPosition(sf::Vector2f(220, 450));
	sprLoadGame.setScale(0.8, 0.8);

	sprQuitGame.setTexture(quitGameImage);
	m_quitGameRect = sf::IntRect(0, 0, 190, 60);
	sprQuitGame.setTextureRect(m_menuRect);
	sprQuitGame.setPosition(sf::Vector2f(420, 450));
	sprQuitGame.setScale(0.8, 0.8);

	

	sprSettings.setTexture(settingsImage);
	m_settingsRect = sf::IntRect(0, 0, 190, 60);
	sprSettings.setTextureRect(m_menuRect);
	sprSettings.setPosition(sf::Vector2f(600, 450));
	sprSettings.setScale(0.8, 0.8);

	sprCursor.setTexture(cursorImage);
	m_cursorRect = sf::IntRect(0, 0, 125, 108);
	sprCursor.setTextureRect(m_cursorRect);
	sprCursor.setPosition(cursorPosition);
	sprCursor.setScale(0.8, 0.8);
}

void DrawLevelComplete(sf::RenderWindow & p_window)
{
	sprLevelComplete.setTexture(lcImage);
	lcRect = sf::IntRect(0, 0, 800, 600);
	sprLevelComplete.setTextureRect(lcRect);
	sprLevelComplete.setPosition(sf::Vector2f(0, 0));
	p_window.draw(sprLevelComplete);

	scoreText.setPosition(sf::Vector2f(200, 120));
	scoreText.setString(std::to_string(player.GetScore()));

	shotsFiredText.setPosition(sf::Vector2f(310, 260));
	shotsFiredText.setString(std::to_string(bulletCounterForLevelCompleteText));

	enemiesKilledText.setPosition(sf::Vector2f(360, 190));
	enemiesKilledText.setString(std::to_string(enemiesKilled));

	friendliesSavedText.setPosition(sf::Vector2f(400, 325));
	friendliesSavedText.setString(std::to_string(friendliesSaved));

	timeText.setPosition(sf::Vector2f(290, 400));
	timeText.setString(std::to_string(timeMins) + ":" + std::to_string((int)timeSeconds));

	p_window.draw(scoreText);
	p_window.draw(enemiesKilledText);
	p_window.draw(shotsFiredText);
	p_window.draw(friendliesSavedText);
	p_window.draw(timeText);

}
// jamie's method for updating menu
void UpdateMenu()
{
	delay++;
	if (sf::Joystick::isButtonPressed(0, 5)) //"RB" button on the XBox 360 controller
	{
		if (delay > 1000)
		{
			delay = 0;
			selectedButton++;
		}

		if (selectedButton > settings)
		{
			selectedButton = newGame;
		}
	}
	else if (sf::Joystick::isButtonPressed(0, 4))
	{
		if (delay > 1000)
		{
			delay = 0;
			selectedButton--;
		}
		if (selectedButton < newGame)
		{
			selectedButton = settings;
		}
	}

	if (selectedButton == newGame)
	{
		cursorPosition = sf::Vector2f(50, 500);
	}
	if (selectedButton == loadGame)
	{
		cursorPosition = sf::Vector2f(240, 500);
	}
	if (selectedButton == quitGame)
	{
		cursorPosition = sf::Vector2f(440, 500);

	}
	if (selectedButton == settings)
	{
		cursorPosition = sf::Vector2f(620, 500);
	}
}

// jamie's draw settings method
void DrawSettings(sf::RenderWindow &p_window)
{
	// try this here? if not make an init
	settingsScreenImage.loadFromFile("Resources/settingsBackground.png");
	controlsTex.loadFromFile("Resources/controls.png");

	sprSettingsScreen.setTexture(settingsScreenImage);
	m_settingsScreenRect = sf::IntRect(0, 0, 800, 600);
	sprSettingsScreen.setTextureRect(m_settingsScreenRect);
	sprSettingsScreen.setPosition(sf::Vector2f(0, 0));

	sprControls.setTexture(controlsTex);
	m_controlsRect = sf::IntRect(0, 0, 800, 600);
	sprControls.setTextureRect(m_settingsScreenRect);
	sprControls.setPosition(sf::Vector2f(0, 50));
}
void DrawGameOver(sf::RenderWindow &p_window)
{
	sprGameOver.setTexture(goImage);
	goRect = sf::IntRect(0, 0, 800, 600);
	sprGameOver.setTextureRect(goRect);
	sprGameOver.setPosition(sf::Vector2f(0, 0));
	p_window.draw(sprGameOver);
}
// Collision between game objects
///////////////////////////
void Collisions(sf::RenderWindow &p_window)
{

	// move the enemy towards the player with a simple position check 
	// target position taken from player and passed to enemy
	sf::Vector2f playerCurrentPos = player.getPosition();
	sf::IntRect playerRect(player.getPosition().x - 8, player.getPosition().y - 11, 24, 24);  // size of player texture


	// start of tile loop
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (tileMap[i][j].tex == Tile::m_texture::END)
			{
				sf::IntRect goalRect(j * 50, i * 50, 50, 50);

				if (playerRect.intersects(goalRect))
				{
					timeText.setCharacterSize(68);
					currentState = GameStates::levelComplete;
					int x = 0;
				}
			}
			if (tileMap[i][j].tex == Tile::m_texture::MAZE)
			{
				sf::IntRect mazeRect(j * 50, i * 50, 50, 50);
				// added bullet collision with walls 
				for (int k = 0; k < bulletManager2012.m_bulletList.size(); k++)
				{
					if (bulletManager2012.m_bulletList.at(k).GetBulletRectangle().intersects(mazeRect))
					{
						bulletManager2012.m_bulletList.erase(bulletManager2012.m_bulletList.begin() + k);
					}
				}


				if (playerRect.intersects(mazeRect))
				{
					// check distance from player centre and maze centre
					//sf::Vector2f mazePos(mazeRect.left, mazeRect.top);
					//sf::Vector2f mazeCentre(mazePos.x + 25, mazePos.y + 25);
					//sf::Vector2f playerCentre(player.getPosition().x + 16, player.getPosition().y + 16);



					float distanceX;

					//distanceX = playerCentre.x - mazePos.x;
					distanceX = (player.getPosition().x + 16) - mazeRect.left;
					pushRight = false;

					if (distanceX > 5)  // ie must have been coming from right side to left 
					{
						distanceX = playerRect.left - (mazeRect.left + 50);
						pushRight = true;
					}
					if (distanceX < 0)
					{
						distanceX = distanceX * -1;   // if negative, multiply by -1 to get a positive value
					}

					// check x and y seperately
					float pushBackDistX; // distance between current player and ideal distance , ie distance to push back
					pushBackDistX = distanceX;


					float distanceY;
					distanceY = (player.getPosition().y + 12) - mazeRect.top;
					pushUp = false;

					if (distanceY > 5)  // ie must be coming from bottom to top
					{
						distanceY = playerRect.top - (mazeRect.top + 50);
						pushUp = true;
					}



					if (distanceY < 0)
					{
						distanceY = distanceY * -1;   // if negative, multipy by -1 to get a positive value
					}

					float pushBackDistY;
					pushBackDistY = distanceY;

					if (pushBackDistX < pushBackDistY)
					{
						if (pushRight == true)
						{
							player.SetPosition(sf::Vector2f(player.getPosition().x + pushBackDistX, player.getPosition().y));  // collide right
						}
						else
						{
							player.SetPosition(sf::Vector2f(player.getPosition().x - pushBackDistX, player.getPosition().y));  // collide left
						}
					}


					if (pushBackDistX > pushBackDistY)
					{
						if (pushUp == true)
						{
							player.SetPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + pushBackDistY));  // collide up
						}
						else
						{
							player.SetPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - pushBackDistY));  // collide down
						}
					}
				}
			}
		}
	}


			///////////////////////////////////////////////////////////////////////////////////////
			for (int i = 0; i < enemyList.size(); i++)
			{
				sf::IntRect enemyRect(enemyList.at(i).GetPosition().x - 12.5f, enemyList.at(i).GetPosition().y - 12.5f, 25, 25);

				// enemy collision box, un comment to see
				/*sf::RectangleShape rectEm;
				rectEm.setPosition(sf::Vector2f(enemyRect.left, enemyRect.top));
				rectEm.setFillColor(sf::Color::Red);
				rectEm.setSize(sf::Vector2f(25, 25));
				p_window.draw(rectEm);*/


				if (enemyList.at(i).GetAlive() == true)
				{
					if (playerRect.intersects(enemyRect) == true)
					{
						enemyList.at(i).SetAlive(false);
						enemyList.erase(enemyList.begin() + i);

						int health = player.GetHealth();
						player.SetHealth(health - 35);
						if (player.GetHealth() <= 0)
						{
							bool playerDead = false;
							player.SetAlive(playerDead);

							currentState = GameStates::gameOver;
						}
					}
				}

				// start of bullet loop
				for (int j = 0; j < bulletManager2012.m_bulletList.size(); j++)
				{
					if (bulletManager2012.m_bulletList.at(j).GetBulletRectangle().intersects(enemyRect))
					{
						enemiesKilled++;
						enemyList.at(i).SetAlive(false);
						enemyList.erase(enemyList.begin() + i);
						bulletManager2012.m_bulletList.erase(bulletManager2012.m_bulletList.begin() + j);

						score = player.GetScore() + 100;
						player.SetScore(score);
						text.setString("Score: " + score);

					}
				}
				// end of bullet loop

				if (enemyList.at(i).GetAlive() == true)
				{
					enemyList.at(i).update(playerCurrentPos, deltaTime);

					p_window.draw(enemyList.at(i).GetSprite());
				}
			}

			sf::IntRect hostageRect(hostage.getPosition().x - 16, hostage.getPosition().y -12, 32, 24);
			// hostage collision box, un comment to see
			/*sf::RectangleShape hostRect;
			hostRect.setPosition(sf::Vector2f(hostageRect.left, hostageRect.top));
			hostRect.setFillColor(sf::Color::Red);
			hostRect.setSize(sf::Vector2f(32, 24));
			p_window.draw(hostRect);*/


			if (playerRect.intersects(hostageRect))
			{
				
				if (!saved)
				{
					int temp = player.GetScore() + 250;
					player.SetScore(temp);
				}
				saved = true;
				friendliesSaved = 1;
				hostage.setRescue(true);
			}
			////////////////////////////////////////////////////////////////////////////////////
	
}

// DRAW EVENT
/////////////////////////////
void Draw(sf::RenderWindow &p_window)
{
	if (currentState == GameStates::playGameState)
	{
		sprHud.setTexture(m_hud);
		m_spriteRect = sf::IntRect(0, 0, 800, 600);
		sprHud.setTextureRect(m_spriteRect);
		sprHud.setScale(0.45f, 0.47f);
		sprHud.setPosition(sf::Vector2f(player.getPosition().x - 180, player.getPosition().y - 140));
		text.setPosition(sf::Vector2f(player.getPosition().x - 38, player.getPosition().y - 145));
		text.setString("Score: " + std::to_string(player.GetScore()));
		p_window.draw(sprHud);

		p_window.draw(text);
		p_window.draw(timeText);
		p_window.draw(bulletsRemText);

		if (player.GetHealth() <= 60 && player.GetHealth() >= 30)
		{
			sprHealth.setTexture(texHealthY);
		}
		else if (player.GetHealth() <= 30)
		{
			sprHealth.setTexture(texHealthR);
		}
		else
			sprHealth.setTexture(texHealthG);

		healthRect = sf::IntRect(0, 0, 50, 50);
		sprHealth.setTextureRect(healthRect);
		sprHealth.setScale((float)player.GetHealth() / 27, 0.3f);
		sprHealth.setPosition(sf::Vector2f(player.getPosition().x - 179, player.getPosition().y + 130));



		p_window.draw(sprHealth);
	}

}
// UPDATE EVENT
/////////////////////////////
void Update(sf::RenderWindow &p_window)
{
	switch (currentState)
	{

	case menuState:
		// update menu
		UpdateMenu();
		// draw menu
		DrawMenu(p_window);
		p_window.draw(sprMenu);
		p_window.draw(sprNewGame);
		p_window.draw(sprLoadGame);
		p_window.draw(sprQuitGame);
		p_window.draw(sprSettings);
		p_window.draw(sprCursor);
		break;

	case playGameState:
		timer += deltaTime.asSeconds();
		deltaTime = myClock.getElapsedTime();
		myClock.restart();
		XboxController::Instance().Update(deltaTime);
		Collisions(p_window);

		if (player.GetAlive() == true && currentState == GameStates::playGameState)
		{
			deltaTime = myClock.restart();
			player.Update(deltaTime,hostage.getRescue());
			viewport.setCenter(player.getPosition());
			bulletManager2012.Update(deltaTime);
			bulletManager2012.Draw(p_window);
			p_window.draw(player.getSprite());
			p_window.draw(hostage.getSprite());
			if (player.hostagePositions.size() == 1000)
			{
				hostage.Update(player.GetHostagePos(), player.getRotation());
			}
			timeSeconds += deltaTime.asSeconds() * 2.3f;

			
			if (timeSeconds >= 60)
			{
				timeSeconds = 0;
				timeMins += 1;
			}

			timeText.setPosition(sf::Vector2f(player.getPosition().x - 130, player.getPosition().y - 146));
			timeText.setString(std::to_string(timeMins) + ":" + std::to_string((int)timeSeconds));

			bulletsRemText.setPosition(sf::Vector2f(player.getPosition().x + 110, player.getPosition().y - 146));
			bulletsRemText.setString(std::to_string(bulletsRemainingInHud));
		}


		break;

	case gameSettings:
		// update settings
		// draw settings
		DrawSettings(p_window);
		p_window.draw(sprSettingsScreen);
		p_window.draw(sprControls);
		break;

	case levelComplete:
		DrawLevelComplete(p_window);
		break;

	case gameOver:
		DrawGameOver(p_window);
		break;
	}
	soundManager2014.Update(player.getPosition(), player.getVelocity());
}
// Load the first level
/////////////////////////
void LoadFirstLevel()
{
	

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			tileMap[i][j] = Tile(sprMaze, sf::Vector2f(50 * i, 50 * j));
		}
	}

	tileMap[5][9] = Tile(sprEnd, sf::Vector2f(450, 250));
	/////////////////////////////////////////////////////////
		//	Top  Wall
		tileMap[0][0].tex = Tile::m_texture::MAZE;
		tileMap[0][1].tex = Tile::m_texture::MAZE;
		tileMap[0][2].tex = Tile::m_texture::MAZE;
		tileMap[0][3].tex = Tile::m_texture::MAZE;
		tileMap[0][4].tex = Tile::m_texture::MAZE;
		tileMap[0][5].tex = Tile::m_texture::MAZE;
		tileMap[0][6].tex = Tile::m_texture::MAZE;
		tileMap[0][7].tex = Tile::m_texture::MAZE;
		tileMap[0][8].tex = Tile::m_texture::MAZE;
		tileMap[0][9].tex = Tile::m_texture::MAZE;
		tileMap[0][10].tex = Tile::m_texture::MAZE;
		tileMap[0][11].tex = Tile::m_texture::MAZE;
		tileMap[0][12].tex = Tile::m_texture::MAZE;
		tileMap[0][13].tex = Tile::m_texture::MAZE;
		tileMap[0][14].tex = Tile::m_texture::MAZE;
		tileMap[0][15].tex = Tile::m_texture::MAZE;

		/////////////////////////////////////////////////////////
		//	Bottom  Wall
		tileMap[11][0].tex = Tile::m_texture::MAZE;
		tileMap[11][1].tex = Tile::m_texture::MAZE;
		tileMap[11][2].tex = Tile::m_texture::MAZE;
		tileMap[11][3].tex = Tile::m_texture::MAZE;
		tileMap[11][4].tex = Tile::m_texture::MAZE;
		tileMap[11][5].tex = Tile::m_texture::MAZE;
		tileMap[11][6].tex = Tile::m_texture::MAZE;
		tileMap[11][7].tex = Tile::m_texture::MAZE;
		tileMap[11][8].tex = Tile::m_texture::MAZE;
		tileMap[11][9].tex = Tile::m_texture::MAZE;
		tileMap[11][10].tex = Tile::m_texture::MAZE;
		tileMap[11][11].tex = Tile::m_texture::MAZE;
		tileMap[11][12].tex = Tile::m_texture::MAZE;
		tileMap[11][13].tex = Tile::m_texture::MAZE;
		tileMap[11][14].tex = Tile::m_texture::MAZE;
		tileMap[11][15].tex = Tile::m_texture::MAZE;

		tileMap[5][9].tex = Tile::m_texture::END;
	

		/////////////////////////////////////////////////////////
		//	Right Wall
		tileMap[1][15].tex = Tile::m_texture::MAZE;
		tileMap[2][15].tex = Tile::m_texture::MAZE;
		tileMap[3][15].tex = Tile::m_texture::MAZE;
		tileMap[4][15].tex = Tile::m_texture::MAZE;
		tileMap[5][15].tex = Tile::m_texture::MAZE;
		tileMap[6][15].tex = Tile::m_texture::MAZE;
		tileMap[7][15].tex = Tile::m_texture::MAZE;
		tileMap[8][15].tex = Tile::m_texture::MAZE;
		tileMap[9][15].tex = Tile::m_texture::MAZE;
		tileMap[10][15].tex = Tile::m_texture::MAZE;
		tileMap[11][15].tex = Tile::m_texture::MAZE;


		/////////////////////////////////////////////////////////
		//	Left Wall
		tileMap[1][0].tex = Tile::m_texture::MAZE;
		tileMap[2][0].tex = Tile::m_texture::MAZE;
		tileMap[3][0].tex = Tile::m_texture::MAZE;
		tileMap[4][0].tex = Tile::m_texture::MAZE;
		tileMap[5][0].tex = Tile::m_texture::MAZE;
		tileMap[6][0].tex = Tile::m_texture::MAZE;
		tileMap[7][0].tex = Tile::m_texture::MAZE;
		tileMap[8][0].tex = Tile::m_texture::MAZE;
		tileMap[9][0].tex = Tile::m_texture::MAZE;
		tileMap[10][0].tex = Tile::m_texture::MAZE;
		tileMap[11][0].tex = Tile::m_texture::MAZE;


		/////////////////////////////////////////////////////////
		//	Maze Bit
		tileMap[1][2].tex = Tile::m_texture::MAZE;
		tileMap[2][2].tex = Tile::m_texture::MAZE;
		tileMap[3][2].tex = Tile::m_texture::MAZE;
		tileMap[4][2].tex = Tile::m_texture::MAZE;
		tileMap[5][2].tex = Tile::m_texture::MAZE;

		tileMap[8][2].tex = Tile::m_texture::MAZE;
		tileMap[9][2].tex = Tile::m_texture::MAZE;
		tileMap[10][3].tex = Tile::m_texture::MAZE;
		tileMap[10][4].tex = Tile::m_texture::MAZE;

		tileMap[3][4].tex = Tile::m_texture::MAZE;
		tileMap[4][4].tex = Tile::m_texture::MAZE;
		tileMap[5][4].tex = Tile::m_texture::MAZE;
		tileMap[6][4].tex = Tile::m_texture::MAZE;
		tileMap[7][4].tex = Tile::m_texture::MAZE;

		tileMap[8][5].tex = Tile::m_texture::MAZE;
		tileMap[8][6].tex = Tile::m_texture::MAZE;
		tileMap[8][7].tex = Tile::m_texture::MAZE;
		tileMap[8][8].tex = Tile::m_texture::MAZE;
		tileMap[8][9].tex = Tile::m_texture::MAZE;
		tileMap[8][10].tex = Tile::m_texture::MAZE;

		tileMap[8][11].tex = Tile::m_texture::MAZE;
		tileMap[7][12].tex = Tile::m_texture::MAZE;

		tileMap[6][10].tex = Tile::m_texture::MAZE;
		tileMap[6][9].tex = Tile::m_texture::MAZE;
		tileMap[6][8].tex = Tile::m_texture::MAZE;
		tileMap[6][7].tex = Tile::m_texture::MAZE;
		tileMap[6][6].tex = Tile::m_texture::MAZE;
		tileMap[5][10].tex = Tile::m_texture::MAZE;
		tileMap[4][10].tex = Tile::m_texture::MAZE;
		tileMap[4][9].tex = Tile::m_texture::MAZE;
		tileMap[4][8].tex = Tile::m_texture::MAZE;
		tileMap[4][7].tex = Tile::m_texture::MAZE;
		tileMap[4][6].tex = Tile::m_texture::MAZE;

		tileMap[6][13].tex = Tile::m_texture::MAZE;
		tileMap[4][13].tex = Tile::m_texture::MAZE;
		tileMap[3][12].tex = Tile::m_texture::MAZE;

		tileMap[2][5].tex = Tile::m_texture::MAZE;
		tileMap[2][6].tex = Tile::m_texture::MAZE;
		tileMap[2][7].tex = Tile::m_texture::MAZE;
		tileMap[2][8].tex = Tile::m_texture::MAZE;
		tileMap[2][9].tex = Tile::m_texture::MAZE;
		tileMap[2][10].tex = Tile::m_texture::MAZE;
		tileMap[2][11].tex = Tile::m_texture::MAZE;
}
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	m_playerTex.loadFromFile("Resources/playerWpistol.png");
	m_hostageTex.loadFromFile("Resources/Hostage.png");
	m_bulletTex.loadFromFile("Resources/bullet.png");
	m_hud.loadFromFile("Resources/Game HUD.png");
	texHealthG.loadFromFile("Resources/HealthG.png");
	texHealthY.loadFromFile("Resources/HealthY.png");
	texHealthR.loadFromFile("Resources/HealthR.png");
	lcImage.loadFromFile("Resources/LevelComplete.png");
	goImage.loadFromFile("Resources/GameOver.png");

	player = Player(*&m_playerTex, sf::Vector2f(75, 75));
	hostage = Hostage(*&m_hostageTex, sf::Vector2f(280, 260));
	bulletManager2012 = BulletManager(*&m_bulletTex);
	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");
	viewport.setViewport(sf::FloatRect(0, 0, 1, 1));
	radar.setViewport(sf::FloatRect(0.757f, 0.71f, 0.25f, 0.32f));
	radar.zoom(20.f);

	font.loadFromFile("youmurdererbb_reg.otf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setPosition(sf::Vector2f(player.getPosition().x - 35, player.getPosition().y - 145));

	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setColor(sf::Color::Red);

	bulletsRemText.setFont(font);
	bulletsRemText.setCharacterSize(24);
	bulletsRemText.setColor(sf::Color::Red);

	scoreText.setFont(font);
	scoreText.setCharacterSize(68);
	scoreText.setColor(sf::Color::Red);

	shotsFiredText.setFont(font);
	shotsFiredText.setCharacterSize(68);
	shotsFiredText.setColor(sf::Color::Red);

	enemiesKilledText.setFont(font);
	enemiesKilledText.setCharacterSize(68);
	enemiesKilledText.setColor(sf::Color::Red);

	friendliesSavedText.setFont(font);
	friendliesSavedText.setCharacterSize(68);
	friendliesSavedText.setColor(sf::Color::Red);

	sf::Sprite sprFloor;
	sf::Texture texFloor;
	texFloor.loadFromFile("Resources/floor.png");
	sprFloor.setTexture(texFloor);

	sf::Texture texMaze;
	texMaze.loadFromFile("Resources/MazeTest.png");
	sprMaze.setTexture(texMaze);
	

	sf::Texture texEnd;
	texEnd.loadFromFile("Resources/EndGoal.png");
	sprEnd.setTexture(texEnd);


	sf::Sprite sprEnemy;
	sf::Texture texEnemy;
	texEnemy.loadFromFile("Resources/ZombieTest.png");
	sprEnemy.setTexture(texEnemy);

	// try put the init in  here..
	// if it doesn't work put back in initMenu() method
	menuImage.loadFromFile("Resources/UnderkillCover.png");
	newGameImage.loadFromFile("Resources/NewGame.png");
	loadGameImage.loadFromFile("Resources/LoadGame.png");
	quitGameImage.loadFromFile("Resources/QuitGame.png");
	settingsImage.loadFromFile("Resources/Settings.png");
	cursorImage.loadFromFile("Resources/cursor.png");
	soundManager2014 = SoundManager();
	soundManager2014.Inititialise();
	soundManager2014.PlayBackgroundMusic();
	cursorPosition = sf::Vector2f(50, 500);

	//soundManager2014.PlayGameMusic();  // this was commented out on jamie's edition
	em1 = Enemy(sprEnemy, sf::Vector2f(650, 480), 5);
	em2 = Enemy(sprEnemy, sf::Vector2f(250, 480), 5);
	em3 = Enemy(sprEnemy, sf::Vector2f(180, 480), 5);
	em5 = Enemy(sprEnemy, sf::Vector2f(300, 480), 5);
	em6 = Enemy(sprEnemy, sf::Vector2f(400, 480), 5);
	em7 = Enemy(sprEnemy, sf::Vector2f(500, 480), 5);
	em4 = Enemy(sprEnemy, sf::Vector2f(50000, 35000), 5);
	enemyList.push_back(em1);
	enemyList.push_back(em2);
	enemyList.push_back(em3);
	enemyList.push_back(em5);
	enemyList.push_back(em6);
	enemyList.push_back(em7);
	enemyList.push_back(em4);


	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();

		}

		if (sf::Joystick::isButtonPressed(0, 6)) //"Back" button on the XBox 360 controller
		{
			if (soundEffectsEnabled == true && pressedLastFrame1 == false)
			{
				soundEffectsEnabled = false;
			}
			else if (pressedLastFrame1 == false && soundEffectsEnabled == false)
				soundEffectsEnabled = true;

		}
		else
			pressedLastFrame1 = false;

		if (sf::Joystick::isButtonPressed(0, 7)) //"Start" button on the XBox 360 controller
		{
			if (backgroundMusicEnabled == true && pressedLastFrame == false)
			{
				soundManager2014.PauseMusic();
				backgroundMusicEnabled = false;
			}
			else if (pressedLastFrame == false && backgroundMusicEnabled == false)
			{
				soundManager2014.UnPauseMusic();
				backgroundMusicEnabled = true;
			}

			pressedLastFrame = true;

		}
		else
			pressedLastFrame = false;


		if (sf::Joystick::isButtonPressed(0, 3) && selectedButton == newGame) //"Y" button on the XBox 360 controller
		{
			if (soundManager2014.enable3dAudio == true)
			{
				soundManager2014.enable3dAudio = false;
				soundManager2014.dopplerEnabaled = false;
			}


			else if (soundManager2014.enable3dAudio == false)
			{
				soundManager2014.enable3dAudio = true;
				soundManager2014.dopplerEnabaled = true;

			}

		}

		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == quitGame) //"A" button on the XBox 360 controller
		{
			window.close();
		}
		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == newGame) //"A" button on the XBox 360 controller
		{
			soundManager2014.StopSound();
			soundManager2014.PlayZombieSound();
			currentState = GameStates::playGameState;
			pressBtn = true;
		}
		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == settings) //"A" button on the XBox 360 controller
		{
			currentState = GameStates::gameSettings;
		}
		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == loadGame) //"A" button on the XBox 360 controller
		{
			currentState = GameStates::playGameState;
		}
		if (sf::Joystick::isButtonPressed(0, 1) && currentState == GameStates::gameSettings) //"B" button on the XBox 360 controller
		{
			currentState = GameStates::menuState;
		}

		if (sf::Joystick::isButtonPressed(0, 5) && currentState == GameStates::playGameState) //"RB" button on the XBox 360 controller
		{

			sf::Vector2f temp;
			float angle = player.getAngle();
			temp = sf::Vector2f(cos(angle), sin(angle));

			if (timer > BULLETDELAY && player.GetBullets() > 0)
			{
				if (bulletsFired <= 5)
				{
					bulletsFired++;
					bulletsRemainingInHud--;
					bulletCounterForLevelCompleteText++;
					//int bulletsLeft = player.GetBullets() -1;
					player.SetBullets(player.GetBullets() - 1);
					bulletManager2012.AddBullet(player.getPosition(), temp, bulletManager2012.getSprite());
					if (hostage.getRescue() == true)
					{
						bulletManager2012.AddBullet(hostage.getPosition(), temp, bulletManager2012.getSprite());
					}
					if (soundEffectsEnabled && pressedLastFrame1 == false)
					{
						soundManager2014.PlayBulletSound();
					}

					timer = 0;
					reloadingSound = true;
				}
			
				else if (timer > RELOADDELAY && player.GetBullets() > 0)
				{
					bulletsFired = 0;
					bulletsRemainingInHud = 6;
					//bulletManager2012.AddBullet(player.getPosition(), temp, bulletManager2012.getSprite());
					if (hostage.getRescue() == true)
					{
						bulletManager2012.AddBullet(hostage.getPosition(), temp, bulletManager2012.getSprite());
					}
					if (soundEffectsEnabled && pressedLastFrame1 == false)
					{
						soundManager2014.PlayBulletSound();
					}
				}

				else if (timer < RELOADDELAY && soundEffectsEnabled)
				{
					if (reloadingSound == true)
					{
						bulletsRemainingInHud = 6;
						soundManager2014.PlayReloadSound();
						reloadingSound = false;
					}

				}
			}
		}
	

		//prepare frame
		// please dont change order these methods are done in 

		window.clear();
		if (currentState == playGameState)
		{
			window.setView(viewport); // main view
		}
		window.draw(sprFloor);
		LoadFirstLevel();  // this has to load first before being drawn so keep method before the following draw statement
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{	
				if (tileMap[i][j].tex == Tile::m_texture::MAZE)
				{
					window.draw(tileMap[j][i].GetSprite());
				}
			}
		}
		window.draw(tileMap[5][9].GetSprite());
		
		Update(window);  // do collisions after update and before draw
		Draw(window);

		if (currentState == playGameState)
		{
			window.setView(radar); // radar view drawn on top of main view
		}
		window.draw(sprFloor);
		LoadFirstLevel();  // this has to load first before being drawn so keep method before the following draw statement
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (tileMap[i][j].tex == Tile::m_texture::MAZE)
				{
					window.draw(tileMap[j][i].GetSprite());
				}
			}
		}
		window.draw(tileMap[5][9].GetSprite());

		Update(window);  // do collisions after update and before draw

		
		if (currentState == GameStates::levelComplete || currentState == GameStates::gameOver)
		{
			viewport = window.getDefaultView();
			window.setView(viewport);
		}

		// player's collision box, un comment to see 
		/*	sf::RectangleShape rect;
		rect.setPosition(sf::Vector2f(playerRect.left, playerRect.top));
		rect.setFillColor(sf::Color::Red);
		rect.setSize(sf::Vector2f(24, 24));
		window.draw(rect);*/


	

		// Finally, display rendered frame on screen 
		window.display();

	} //loop back for next frame

	return EXIT_SUCCESS;
}


// Joystick Buttons
// (0, 0) - Y
// (0, 1) - A
// (0, 2) - X
// (0, 3) - B
// (0, 4) - Left Bumper
// (0, 5) - Right Bumper
// (0, 6) - Back Bumper
// (0, 7) - Start Bumper
// (0, 8) - Left Analog Press
// (0, 9) - Right Analog Press

// sf::Joystick::X - Left Analog X-Axis
// sf::Joystick::Y - Left Analog Y-Axis
// sf::Joystick::R - Right Analog X-Axis
// sf::Joystick::U - Right Analog Y-Axis
// sf::Joystick::PovX - D-Pad X-Axis
// sf::Joystick::PovY - D-Pad Y-Axis