#pragma once
#include <string>
#include "SFML/Graphics.hpp"
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void SetPosition(float x, float y);

private:
	sf::Sprite _sprite;
	sf::Image _iamge;
	std::string _filename;
	bool _isLoaded;
};
