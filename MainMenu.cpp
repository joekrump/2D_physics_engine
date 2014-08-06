#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow &window)
{
	//Load menu image from file
	sf::Texture image;
	if(image.loadFromFile("images/mainmenu.png") != true)
	{
		return Nothing;
	}

	sf::Sprite sprite(image);

	window.draw(sprite);
	window.display();

	// Setup clickable regions

	// Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.height = 235;
	playButton.rect.left = 0;
	playButton.rect.width = 1023;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.rect.top = 383;
	exitButton.rect.height = 157;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	return GetMenuResponse(window);

}


MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;


	for( it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;

		if( (menuItemRect.top < y)
			&& (menuItemRect.height + menuItemRect.top) > y
			&& (menuItemRect.left < x) && (menuItemRect.left + menuItemRect.width) > x)
		{
			return (*it).action;
		}
	}

	return Nothing;

}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow &window)
{
	sf::Event menuEvent;
	
	while(true)
	{

		while(window.pollEvent(menuEvent))
		{
			if(menuEvent.type == sf::Event::EventType::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if(menuEvent.type == sf::Event::EventType::Closed)
			{
				return Exit;
			}
		}
	}
}
