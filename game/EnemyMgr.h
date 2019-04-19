#pragma once

#include<list>

#include<iostream>

#include<ctime>

using namespace std;

#include"Enemy.h"



class EnemyMgr

{

private:

	list<Enemy> EnemyList;

	Texture EnemyTexture;

	Texture newEnemyTexture;

	bool goleft;

	bool goright;

	bool goDown;

	int distance; //distance moved per frame aka speed

	int shooter;

	int lastShooter;

	int downDistance;



public:

	EnemyMgr()

	{

		if (!EnemyTexture.loadFromFile("enemy.png"))

		{

			cout << "Unable to load Enemy texture!" << endl;

			exit(EXIT_FAILURE);

		}
		if (!newEnemyTexture.loadFromFile("newEnemy.png"))

		{

			cout << "Unable to load Enemy texture!" << endl;

			exit(EXIT_FAILURE);

		}

		const int DISTANCEBETWEENBGUYS = 65;

		Vector2f firstPos(50, 100);

		Vector2f distanceBtwn(DISTANCEBETWEENBGUYS, 0);

		for (int i = 0; i < 10; i++)

		{

			Enemy newEnemy(newEnemyTexture, firstPos);

			EnemyList.push_back(newEnemy);

			firstPos = firstPos + distanceBtwn;

		}

		goleft = false;

		goright = true;

		goDown = false;

		distance = 3;

		downDistance = 15;

		lastShooter = 0;

	}



	void draw(RenderWindow& win)

	{

		list<Enemy>::iterator iter;

		for (iter = EnemyList.begin(); iter != EnemyList.end(); iter++)

		{

			iter->draw(win);

		}

	}

	void move(RenderWindow& win)

	{

		int counter = 0;

		// find last guy on the right

		list<Enemy>::iterator iter;

		for (iter = EnemyList.begin(); iter != EnemyList.end(); iter++)

		{

			counter++;

		}

		iter = EnemyList.begin();

		advance(iter, counter - 1);



		if (iter->getXPos() > 750)

		{

			goleft = true;

			goright = false;

			goDown = true;

		}

		else if (EnemyList.begin()->getXPos() < 20)

		{

			goleft = false;

			goright = true;

		}

		if (goleft)

		{

			list<Enemy>::iterator it;

			for (it = EnemyList.begin(); it != EnemyList.end(); it++)

			{

				it->moveDistance(-distance, 0);

			}

			if (goDown)

			{

				for (it = EnemyList.begin(); it != EnemyList.end(); it++)

				{

					it->moveDistance(-distance, downDistance);

				}

				goDown = false;

			}

		}

		else if (goright)

		{

			list<Enemy>::iterator it;

			for (it = EnemyList.begin(); it != EnemyList.end(); it++)

			{

				it->moveDistance(distance, 0);

			}

		}

	}



	bool isHit(list<missile>& missileList)

	{

		bool hit = false;

		// go through list of bad guys to check for hits

		list<Enemy>::iterator iter;

		for (iter = EnemyList.begin(); iter != EnemyList.end();)

		{

			if (iter->isHit(missileList))

			{

				hit = true;

				iter = EnemyList.erase(iter);

			}

			else

			{

				iter++;

			}

		}

		return hit;

	}

	list<Enemy>& getList()

	{

		return EnemyList;

	}

	void setSpeed(int speed)

	{

		distance = speed;

	}

	bool isEmpty()

	{

		bool empty = false;



		if (EnemyList.empty())

		{

			empty = true;

		}

		return empty;

	}

	void reset(int speed)

	{

		// delete all Enemys from previous state

		list<Enemy>::iterator it;

		for (it = EnemyList.begin(); it != EnemyList.end();)

		{

			it = EnemyList.erase(it);

		}



		// repopulate new bad guys and change speed/distance

		const int DISTANCEBETWEENBGUYS = 65;

		Vector2f firstPos(50, 100);

		Vector2f distanceBtwn(DISTANCEBETWEENBGUYS, 0);

		for (int i = 0; i < 10; i++)

		{

			Enemy newEnemy(EnemyTexture, firstPos);

			EnemyList.push_back(newEnemy);

			firstPos = firstPos + distanceBtwn;

		}

		goleft = false;

		goright = true;

		distance = speed;

	}



	bool didEnemyShoot()

	{

		bool enemyShot = false;

		srand(time(0));



		int maxValue = EnemyList.size() + 10;

		shooter = (rand() % maxValue);



		if (shooter > 0 && shooter < EnemyList.size())

		{

			if (shooter != lastShooter)

			{

				enemyShot = true;

				lastShooter = shooter;

			}

		}

		return enemyShot;

	}



	Vector2f getShooterPos()

	{

		Vector2f shooterPos;



		list<Enemy>::iterator iter;

		iter = EnemyList.begin();

		advance(iter, shooter); //advance to shooter position

		shooterPos = iter->getPosition();



		return shooterPos;

	}



	bool isAcrossLine()

	{

		bool acrossLine = false;



		list<Enemy>::iterator it;

		it = EnemyList.begin();

		if (it->getYPos() > 400)

		{

			acrossLine = true;

		}

		return acrossLine;

	}

};