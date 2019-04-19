#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;



class missile

{

private:

	Sprite missileSprite;

	float distance;

	bool isMissileInFlight;



public:

	missile(Texture& misTexture, Vector2f GoodGuyPos)

	{

		missileSprite.setTexture(misTexture);

		missileSprite.setPosition(GoodGuyPos);

		distance = -10.0;

		isMissileInFlight = true;

	}


	void move()

	{

		missileSprite.move(0, distance);

	}

	void draw(RenderWindow& window)

	{

		window.draw(missileSprite);

	}

	bool isOffScreen()

	{

		bool offScreen = false;



		if (missileSprite.getPosition().y < 0 || missileSprite.getPosition().y > 800)

		{

			offScreen = true;

		}



		return offScreen;

	}

	
	FloatRect getGlobalBounds()

	{

		return missileSprite.getGlobalBounds();

	}

	int getYPosition()

	{

		return missileSprite.getPosition().y;

	}


	void setSpeedandDirection(float speed)

	{

		distance = speed;

	}



};