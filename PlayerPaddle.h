#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle :
	public VisibleGameObject
{

public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow &renderWindow);

	float GetVelocity() const;

private:
	float _veloctiy; // -- left ++ right
	float _maxVelocity;
};