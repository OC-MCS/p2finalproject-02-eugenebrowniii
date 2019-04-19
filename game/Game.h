#pragma once

#include "EnemyMgr.h"

#include "Ally.h"

#include "MissileMgr.h"

#include "Hud.h"



enum GameState { STARTSCREEN, LEVEL1, LEVEL2, GAMELOST, GAMEWON };



class Game

{

private:

	Ally Ally;

	MissileMgr missileMgr;

	MissileMgr enemyMissileMgr;

	EnemyMgr EnemyMgr;

	Hud hud;

	int score;

	int lives;

	Sprite background;

	bool runGame;

	GameState gameState;

	Texture starsTexture;



public:

	// create game elements & set score and lives

	Game(RenderWindow& window) : Ally(window), hud(window)

	{

		if (!starsTexture.loadFromFile("stars.jpg"))

		{

			cout << "Unable to load stars texture!" << endl;

			exit(EXIT_FAILURE);

		}



		background.setTexture(starsTexture);

		// The texture file is 640x480, so scale it up a little to cover 800x600 window

		background.setScale(1.5, 1.5);



		score = 0;

		lives = 3;

		runGame = false;

		gameState = STARTSCREEN;



		enemyMissileMgr.setSpeed(10.0);

	}



	bool drawGameElements(RenderWindow& win)

	{

		win.draw(background);

		hud.update(lives, score);

		hud.draw(win);



		Ally.move();

		Ally.draw(win);



		EnemyMgr.move(win);

		EnemyMgr.draw(win);



		if (EnemyMgr.didEnemyShoot())

		{

			Vector2f shooterPos;

			shooterPos = EnemyMgr.getShooterPos();

			enemyMissileMgr.addMissile(shooterPos);

		}

		if (enemyMissileMgr.areMissilesInFlight())

		{

			enemyMissileMgr.move();

			enemyMissileMgr.draw(win);

			// check hit here

			/*if (Ally.isHit(enemyMissileMgr.getList()))

			{

				cout << "youve been hit" << endl;

			}*/

		}

		if (missileMgr.areMissilesInFlight())

		{

			missileMgr.move();

			missileMgr.draw(win);

			if (EnemyMgr.isHit(missileMgr.getList()))

			{

				score++;

			}

		}

		if (!isLevelCleared() && EnemyMgr.isAcrossLine())

		{

			setGameState(gameState);



			lives--;

			if (lives == 0)

				gameState = GAMELOST;

		}



		return isLevelCleared();

	}



	Vector2f getAllyPos()

	{

		return Ally.getPosition();

	}



	void addMissile()

	{

		Vector2f curAllyPos = Ally.getPosition();

		missileMgr.addMissile(curAllyPos);

	}



	void setRunGame(bool run)

	{

		runGame = run;

	}



	bool isStartBtnPressed()

	{

		return runGame;

	}



	bool isLevelCleared()

	{

		bool levelCleared = false;

		if (EnemyMgr.isEmpty())

		{

			levelCleared = true;

		}

		return levelCleared;

	}



	GameState getGameState()

	{

		return gameState;

	}



	void setGameState(GameState state)

	{

		gameState = state;



		if (gameState == LEVEL2)

		{

			int newSpeed = 4;

			EnemyMgr.reset(newSpeed);

		}

		else if (gameState == LEVEL1 || gameState == STARTSCREEN)

		{

			int defaultSpeed = 3;

			EnemyMgr.reset(defaultSpeed);

		}

	}

	int getLivesCounter()

	{

		return lives;

	}

	int getScore()

	{

		return score;

	}

};