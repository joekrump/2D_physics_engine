#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"

void Game::Start(void)
{
	if(_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1023, 768, 32), "Pang!");
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
					_mainWindow.clear(sf::Color(255, 0, 0));
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

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
	return;
}

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

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
