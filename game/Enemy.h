#pragma once

//#include <iostream>

//using namespace std;

#include <SFML/Graphics.hpp>

using namespace sf;



class Enemy

{

private:

	Sprite EnemySprite;

public:

	Enemy(Texture &text, Vector2f pos)

	{

		EnemySprite.setTexture(text);

		EnemySprite.setPosition(pos);

	}

	void draw(RenderWindow& win)

	{

		win.draw(EnemySprite);

	}

	Vector2f getPosition()

	{

		return EnemySprite.getPosition();

	}

	void setPosition(Vector2f pos)

	{

		EnemySprite.setPosition(pos);

	}

	void moveDistance(float x, float y)

	{

		EnemySprite.move(x, y);

	}

	int getXPos()

	{

		return EnemySprite.getPosition().x;

	}

	int getYPos()

	{

		return EnemySprite.getPosition().y;

	}

	FloatRect getEnemyBounds()

	{

		return EnemySprite.getGlobalBounds();

	}

	bool isHit(list<missile>& missileList)

	{

		bool enemyHit = false;

		FloatRect enemyBounds = EnemySprite.getGlobalBounds();



		list<missile>::iterator iter;

		for (iter = missileList.begin(); iter != missileList.end();)

		{

			FloatRect missileBounds = iter->getGlobalBounds();



			if (missileBounds.intersects(enemyBounds))

			{

				enemyHit = true;

				iter = missileList.erase(iter);

			}

			else

			{

				iter++;

			}

		}

		return enemyHit;

	}

};