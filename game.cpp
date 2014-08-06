#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameObjectManager.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1023, 768, 32), "Pang!");

	// Create player1's paddle and load it
	PlayerPaddle *player1 = new PlyerPaddle();
	player1->Load("images/paddle.png");
	player1->SetPosition((1024/2)-45, 700);

	_gameObjectManager.Add("Paddle1", player1);
	
	// init the game's state
	_gameState = Game::ShowingSplash;
	
	while(!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if(_gameState == Game::Exiting)
		return true;
	else
		return false;
}
/*
Main game loop
*/
void Game::GameLoop()
{
	sf::Event currentEvent;

	while(_mainWindow.pollEvent(currentEvent))
	{
		switch(_gameState)
		{
		case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
		case Game::ShowingSplash:
			{
				ShowSplashScreen();
				break;
			}
		case Game::Playing:
			{ 
				sf::Event currentEvent;
				while(_mainWindow.pollEvent(currentEvent))
				{
					_mainWindow.clear(sf::Color(0, 0, 0));
					_player1.Draw(_mainWindow);
					_mainWindow.display();
					
					if(currentEvent.type == sf::Event::EventType::Closed)
					{
						_gameState = Game::Exiting;
					}

					if(currentEvent.type == sf::Event::EventType::KeyPressed)
					{
						if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
					}
				}
						
				break;
			}
		}
	}
}

/*
Displays the home screen
*/
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
	return;
}
/*
Displays the menu
*/
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
	}
	return;
}

/*
Initialization of static variables outside of the class as required by C++
*/
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
PlayerPaddle Game::_player1;
