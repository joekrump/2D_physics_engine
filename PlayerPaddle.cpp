#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle()
	: _velocity(0),
	_maxVelocity(600.0f)
{
	sf::Sprite _paddleSprite;

	Load("images/paddle.png");
	assert(IsLoaded());
	_paddleSprite = GetSprite();

	_paddleSprite.setOrigin(_paddleSprite.getGlobalBounds().width / 2, _paddleSprite.getGlobalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle() 
{
}

void PlayerPaddle::Draw(sf::RenderWindow &renderWindow)
{
	VisibleGameObject::Draw(renderWindow);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
	sf::Sprite sprite;
	sprite = GetSprite();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity < -(_maxVelocity - 3.0f) ? _velocity = -_maxVelocity : _velocity -= 3.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity > (_velocity + 3.0f) ? _velocity = _maxVelocity : _velocity += 3.0f;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f;
	}
	sf::Vector2f pos = this->GetPosition();

	if(pos.x < (sprite.getGlobalBounds().width / 2) || pos.x > (Game::getWindow().getSize().x - (sprite.getGlobalBounds().width / 2)))
	{
		_velocity = -_velocity; //Bounce by current velocity in oposite direction
	}

	sprite.move(_velocity * elapsedTime, 0);
}