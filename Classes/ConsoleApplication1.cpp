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
#include "CollisonManager.h"
#include "SoundManager.h"



// Variables
//////////////////
sf::Clock myClock;
sf::Time deltaTime;
sf::Texture m_tex1;
sf::Texture m_tex2;
sf::Texture m_hud;
Player player;
BulletManager bulletManager2012;
SoundManager soundManager2014;
sf::Sprite sprHud;

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

sf::Sprite sprCursor;
sf::IntRect m_cursorRect;
sf::Texture cursorImage;
sf::Vector2f cursorPosition;

int selectedButton = 1;
int newGame = 1;
int loadGame = 2;
int quitGame = 3;
int settings = 4;

float delay = 0;
/////////////////////////////////

//Settings Stuff
sf::Sprite sprSettingsScreen;
sf::IntRect m_settingsScreenRect;
sf::Texture settingsScreenImage;


/////////////////////////////////////

float timer = 0;
float otherTimer = 0;
int bulletCount = 0;
sf::IntRect m_spriteRect;
const float BULLETDELAY = 0.3f;
const float RELOADDELAY = 2.5f;
Enemy em1;
Enemy em2;
Enemy em3;
bool emAlive1 = true;
bool emAlive2 = true;
bool emAlive3 = true;
sf::Sprite sprEnemy;
sf::Texture texEnemy;
sf::Vector2f playerCurrentPos;
sf::IntRect playerRect(player.getPosition().x - 13, player.getPosition().y - 13, 26, 26);  // size of player texture

sf::Sprite sprWall;
sf::Texture texWall;
sf::Sprite sprBarrier;
sf::Texture texBarrier;
sf::Sprite sprMaze;
sf::Texture texMaze;


Tile tileMap[16][16];

bool soundEffectsEnabled = true;
bool backgroundMusicEnabled = true;
bool reloadingSound = true;
bool pressBtn = false;

bool pressedLastFrame = false;
bool pressedLastFrame1 = false;

enum StateJob
{
	MAIN_MENU,
	SETTINGS,
	IN_GAME,
};

StateJob m_currentState = StateJob::MAIN_MENU;

void initGame()
{

	//soundManager2014.PlayGameMusic();
	texEnemy.loadFromFile("ZombieTest.png");
	sprEnemy.setTexture(texEnemy);
	em1 = Enemy(sprEnemy, sf::Vector2f(400, 250), 2);
	em2 = Enemy(sprEnemy, sf::Vector2f(200, 350), 2);
	em3 = Enemy(sprEnemy, sf::Vector2f(250, 100), 2);
	
}

void DrawMap(sf::RenderWindow &p_window)
{
	texWall.loadFromFile("WallTest.png");
	sprWall.setTexture(texWall);

	texBarrier.loadFromFile("Barrier.png");
	sprBarrier.setTexture(texBarrier);

	texMaze.loadFromFile("MazeTest.png");
	sprMaze.setTexture(texMaze);


	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (tileMap[i][j].tex == Tile::m_texture::MAZE)
			{
				p_window.draw(tileMap[i][j].GetSprite());
			}
			else if (tileMap[i][j].tex == Tile::m_texture::BARRIER)
			{
				tileMap[i][j] = Tile(sprBarrier, sf::Vector2f(50 * i, 50 * j));
				p_window.draw(tileMap[i][j].GetSprite());
			}
			else if (tileMap[i][j].tex == Tile::m_texture::GROUND)
			{
				tileMap[i][j] = Tile(sprWall, sf::Vector2f(50 * i, 50 * j));
				p_window.draw(tileMap[i][j].GetSprite());
			}

		}
	}
}
void UpdateMap()
{
#pragma region Map
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			tileMap[i][j] = Tile(sprMaze, sf::Vector2f(50 * i, 50 * j));
		}
	}

	/////////////////////////////////////////////////////////
	//	Left Side Wall
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

	/////////////////////////////////////////////////////////
	//	Bottom Wall
	tileMap[1][11].tex = Tile::m_texture::MAZE;
	tileMap[2][11].tex = Tile::m_texture::MAZE;
	tileMap[3][11].tex = Tile::m_texture::MAZE;
	tileMap[4][11].tex = Tile::m_texture::MAZE;
	tileMap[5][11].tex = Tile::m_texture::MAZE;
	tileMap[6][11].tex = Tile::m_texture::MAZE;
	tileMap[7][11].tex = Tile::m_texture::MAZE;
	tileMap[8][11].tex = Tile::m_texture::MAZE;
	tileMap[9][11].tex = Tile::m_texture::MAZE;
	tileMap[10][11].tex = Tile::m_texture::MAZE;
	tileMap[11][11].tex = Tile::m_texture::MAZE;
	tileMap[12][11].tex = Tile::m_texture::MAZE;
	tileMap[13][11].tex = Tile::m_texture::MAZE;
	tileMap[14][11].tex = Tile::m_texture::MAZE;
	tileMap[15][11].tex = Tile::m_texture::MAZE;

	/////////////////////////////////////////////////////////
	//	Top Wall
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
	tileMap[12][0].tex = Tile::m_texture::MAZE;
	tileMap[13][0].tex = Tile::m_texture::MAZE;
	tileMap[14][0].tex = Tile::m_texture::MAZE;
	tileMap[15][0].tex = Tile::m_texture::MAZE;

	/////////////////////////////////////////////////////////
	//	Maze Bit
	tileMap[3][1].tex = Tile::m_texture::MAZE;
	tileMap[3][2].tex = Tile::m_texture::MAZE;
	tileMap[3][3].tex = Tile::m_texture::MAZE;
	tileMap[3][4].tex = Tile::m_texture::MAZE;
	tileMap[3][5].tex = Tile::m_texture::MAZE;
	tileMap[3][6].tex = Tile::m_texture::MAZE;

	//
	tileMap[1][9].tex = Tile::m_texture::BARRIER;
	tileMap[2][9].tex = Tile::m_texture::BARRIER;
	tileMap[3][9].tex = Tile::m_texture::BARRIER;
	tileMap[4][9].tex = Tile::m_texture::BARRIER;
	tileMap[5][9].tex = Tile::m_texture::BARRIER;
	tileMap[6][9].tex = Tile::m_texture::BARRIER;

	//
	tileMap[7][8].tex = Tile::m_texture::MAZE;
	tileMap[7][7].tex = Tile::m_texture::MAZE;
	tileMap[8][6].tex = Tile::m_texture::MAZE;
	tileMap[9][6].tex = Tile::m_texture::MAZE;
	tileMap[10][6].tex = Tile::m_texture::MAZE;
	tileMap[11][6].tex = Tile::m_texture::MAZE;

	//
	tileMap[11][5].tex = Tile::m_texture::MAZE;
	tileMap[11][4].tex = Tile::m_texture::MAZE;
	tileMap[11][3].tex = Tile::m_texture::MAZE;
	tileMap[11][2].tex = Tile::m_texture::MAZE;

	//	
	tileMap[15][5].tex = Tile::m_texture::MAZE;
	tileMap[15][4].tex = Tile::m_texture::MAZE;
	tileMap[15][3].tex = Tile::m_texture::MAZE;
	tileMap[15][2].tex = Tile::m_texture::MAZE;
	tileMap[15][1].tex = Tile::m_texture::MAZE;

	//
	tileMap[12][9].tex = Tile::m_texture::MAZE;
	tileMap[12][10].tex = Tile::m_texture::MAZE;
	tileMap[12][12].tex = Tile::m_texture::MAZE;
	tileMap[12][13].tex = Tile::m_texture::MAZE;

	std::vector<sf::IntRect> wallRect;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (tileMap[i][j].tex != Tile::m_texture::BARRIER && tileMap[i][j].tex != Tile::m_texture::MAZE)
			{
				tileMap[i][j].tex = Tile::m_texture::GROUND;
			}
			if (tileMap[i][j].tex != Tile::m_texture::GROUND)
			{
				wallRect.push_back(sf::IntRect(i * 50, j * 50, 50, 50));
			}
		}
	}

	//CollisonManager::CheckWalleyJobs(&player, &wallRect);
	
	
#pragma endregion Map
}

void UpdateEnemy()
{
	sf::IntRect enemyRect1(em1.GetPosition().x, em1.GetPosition().y, 35, 35); // 2nd vector here is the size of the texture
	sf::IntRect enemyRect2(em2.GetPosition().x, em2.GetPosition().y, 35, 35); // 2nd vector here is the size of the texture
	sf::IntRect enemyRect3(em3.GetPosition().x, em3.GetPosition().y, 35, 35); // 2nd vector here is the size of the texture

	

	if (emAlive1)
	{
		if (playerRect.intersects(enemyRect1) == true)
		{
			bool playerDead = false;
			player.SetAlive(playerDead);
		}
	}
	if (emAlive2)
	{
		if (playerRect.intersects(enemyRect2) == true)
		{
			bool playerDead = false;
			player.SetAlive(playerDead);
		}
	}
	if (emAlive3)
	{
		if (playerRect.intersects(enemyRect3) == true)
		{
			bool playerDead = false;
			player.SetAlive(playerDead);
		}
	}
	if (bulletManager2012.GetBulletRectangle().intersects(enemyRect1))
	{
		emAlive1 = false;
	}
	if (bulletManager2012.GetBulletRectangle().intersects(enemyRect2))
	{
		emAlive2 = false;
	}
	if (bulletManager2012.GetBulletRectangle().intersects(enemyRect3))
	{
		emAlive3 = false;
	}
	if (emAlive1 == true)
	{
		em1.update(playerCurrentPos, deltaTime);
	}
	if (emAlive2 == true)
	{
		em2.update(playerCurrentPos, deltaTime);
	}
	if (emAlive3 == true)
	{
		em3.update(playerCurrentPos, deltaTime);
	}
}
void DrawEnemy(sf::RenderWindow &p_window)
{
	if (emAlive1 == true)
	{
		p_window.draw(em1.GetSprite());
	}
	if (emAlive2 == true)
	{
		p_window.draw(em2.GetSprite());
	}
	if (emAlive3 == true)
	{
		p_window.draw(em3.GetSprite());
	}

}

void initMenu()
{
	menuImage.loadFromFile("UnderkillCover.png");
	newGameImage.loadFromFile("NewGame.png");
	loadGameImage.loadFromFile("LoadGame.png");
	quitGameImage.loadFromFile("QuitGame.png");
	settingsImage.loadFromFile("Settings.png");
	cursorImage.loadFromFile("cursor.png");
	soundManager2014 = SoundManager();
	soundManager2014.Inititialise();
	soundManager2014.PlayBackgroundMusic();
	cursorPosition = sf::Vector2f(50, 500);
}
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

void initSettings()
{
	settingsScreenImage.loadFromFile("settingsBackground.png");
}
void DrawSettings(sf::RenderWindow & p_window)
{
	sprSettingsScreen.setTexture(settingsScreenImage);
	m_settingsScreenRect = sf::IntRect(0, 0, 800, 600);
	sprSettingsScreen.setTextureRect(m_settingsScreenRect);
	sprSettingsScreen.setPosition(sf::Vector2f(0, 0));
}

void Update()
{
	
	timer += deltaTime.asSeconds();
	deltaTime = myClock.getElapsedTime();
	myClock.restart();
	playerCurrentPos = player.getPosition();

	// Updates Controller
	XboxController::Instance().Update(deltaTime);

	switch (m_currentState)
	{
	case IN_GAME:
		//doing game stuff

		if (player.GetAlive() == true)
		{
			player.Update(deltaTime);
			bulletManager2012.Update(deltaTime);
			UpdateMap();
			UpdateEnemy();
		}

		break;

	case MAIN_MENU:
		UpdateMenu();
		//updating buttons
		break;

	case SETTINGS:
		//doing all the settings

		break;
	}
	soundManager2014.Update(player.getPosition(), player.getVelocity());
}
// DRAW EVENT
/////////////////////////////
void Draw(sf::RenderWindow &p_window)
{
	switch (m_currentState)
	{
	case IN_GAME:
		//doing game stuff
		
		if (player.GetAlive() == true)
		{
			DrawMap(p_window);
			bulletManager2012.Draw(p_window);
			p_window.draw(player.getSprite());
			p_window.draw(sprHud);
		}
		DrawEnemy(p_window);
		break;

	case MAIN_MENU:
		DrawMenu(p_window);
		p_window.draw(sprMenu);
		p_window.draw(sprNewGame);
		p_window.draw(sprLoadGame);
		p_window.draw(sprQuitGame);
		p_window.draw(sprSettings);
		p_window.draw(sprCursor);
		break;

	case SETTINGS:
		DrawSettings(p_window);
		p_window.draw(sprSettingsScreen);
		//doing all the settings

		break;
	}
	
}


////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 



int main()
{
	initGame();
	initMenu();
	initSettings();
	m_tex1.loadFromFile("playerWpistol.png");
	m_tex2.loadFromFile("bullet.png");
	m_hud.loadFromFile("Game HUD.png");
	player = Player(*&m_tex1,sf::Vector2f(280, 240));
	bulletManager2012 = BulletManager(*&m_tex2);

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML First Program");

	sprHud.setTexture(m_hud);
	m_spriteRect = sf::IntRect(0, 0, 800, 600);
	sprHud.setTextureRect(m_spriteRect);
	sprHud.setPosition(sf::Vector2f(0,0));

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
			m_currentState = StateJob::IN_GAME;
			pressBtn = true;
		}
		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == settings) //"A" button on the XBox 360 controller
		{
			m_currentState = StateJob::SETTINGS;
		}
		if (sf::Joystick::isButtonPressed(0, 0) && selectedButton == loadGame) //"A" button on the XBox 360 controller
		{
			m_currentState = StateJob::IN_GAME;
		}
		if (sf::Joystick::isButtonPressed(0, 1) && m_currentState == StateJob::SETTINGS) //"B" button on the XBox 360 controller
		{
			m_currentState = StateJob::MAIN_MENU;
		}

		if (sf::Joystick::isButtonPressed(0, 5) && m_currentState == StateJob::IN_GAME) //"RB" button on the XBox 360 controller
		{

			sf::Vector2f temp;
			float angle = player.getAngle();
			temp = sf::Vector2f(cos(angle), sin(angle));

			if (timer > BULLETDELAY)
			{
				if (bulletCount <= 10)
				{
					bulletCount++;
					bulletManager2012.AddBullet(player.getPosition(), temp, bulletManager2012.getSprite());
					if (soundEffectsEnabled && pressedLastFrame1 == false)
					{
						soundManager2014.PlayBulletSound();
					}

					timer = 0;
					reloadingSound = true;
				}

				else if (timer > RELOADDELAY)
				{
					bulletCount = 0;
					bulletCount++;
					bulletManager2012.AddBullet(player.getPosition(), temp, bulletManager2012.getSprite());
					if (soundEffectsEnabled && pressedLastFrame1 == false)
					{
						soundManager2014.PlayBulletSound();
					}
				}

				else if (timer < RELOADDELAY && soundEffectsEnabled)
				{
					if (reloadingSound == true)
					{
						soundManager2014.PlayReloadSound();
						reloadingSound = false;
					}

				}
			}
		}

	
		//prepare frame
		window.clear();
		Update();
		Draw(window);
		// Finally, display rendered frame on screen 
		window.display();

	} //loop back for next frame

	return EXIT_SUCCESS;
}


// Joystick Buttons
// (0, 0) - A
// (0, 1) - B
// (0, 2) - X
// (0, 3) - Y
// (0, 4) - Left Bumper
// (0, 5) - Right Bumper
// (0, 6) - Back 
// (0, 7) - Start 
// (0, 8) - Left Analog Press
// (0, 9) - Right Analog Press

// sf::Joystick::X - Left Analog X-Axis
// sf::Joystick::Y - Left Analog Y-Axis
// sf::Joystick::R - Right Analog X-Axis
// sf::Joystick::U - Right Analog Y-Axis
// sf::Joystick::PovX - D-Pad X-Axis
// sf::Joystick::PovY - D-Pad Y-Axis