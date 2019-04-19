#pragma once

#include <iostream>

using namespace std;

#include <SFML/Graphics.hpp>

using namespace sf;



class Ally

{

private:

	Sprite AllySprite;

	Texture shipTexture;



public:

	Ally(RenderWindow &window)

	{

		if (!shipTexture.loadFromFile("ship.png"))

		{

			cout << "Unable to load ship texture!" << endl;

			exit(EXIT_FAILURE);

		}

		AllySprite.setTexture(shipTexture);



		// set initial position

		float shipX = window.getSize().x * 0.75f;

		float shipY = window.getSize().y * 0.75f;

		AllySprite.setPosition(shipX, shipY);



	}

	void move()

	{

		const float DISTANCE = 5.0;



		if (Keyboard::isKeyPressed(Keyboard::Left))

		{

			// left arrow is pressed: move our ship left 5 pixels

			// 2nd parm is y direction. We don't want to move up/down, so it's zero.

			AllySprite.move(-DISTANCE, 0);

		}

		else if (Keyboard::isKeyPressed(Keyboard::Right))

		{

			// right arrow is pressed: move our ship right 5 pixels

			AllySprite.move(DISTANCE, 0);

		}

	}

	void draw(RenderWindow& win)

	{

		win.draw(AllySprite);

	}

	Vector2f getPosition()

	{

		return AllySprite.getPosition();

	}



	/*bool isHit(list<missile>& enemyMissileList)

	{

		bool AllyHit = false;

		FloatRect AllyBounds = AllySprite.getGlobalBounds();



		list<missile>::iterator iter;

		for (iter = enemyMissileList.begin(); iter != enemyMissileList.end();)

		{

			FloatRect missileBounds = iter->getGlobalBounds();



			if (missileBounds.intersects(AllyBounds))

			{

				AllyHit = true;

				iter = enemyMissileList.erase(iter);

			}

			else

			{

				iter++;

			}

		}

		return AllyHit;

	}*/



};