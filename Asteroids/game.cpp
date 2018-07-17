/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include <vector>
#include <cassert>

 // These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;

/***************************************
* TODO: GAME CONSTRUCTOR
***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	for (int i = 0; i < 5; i++)
	{
		BigRock * bigRock = new BigRock();
		rocks.push_back(bigRock);
	}
}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	advanceBullets();
	advanceShip();
	advanceRocks();

	handleCollisions();
	cleanUpZombies();
}

void Game::handleInput(const Interface & pUI)
{
	// change rotation of ship
	if (pUI.isLeft())
	{
		ship.rotateLeft();
	}

	if (pUI.isRight())
	{
		ship.rotateRight();
	}

	// change thrust
	if (pUI.isUp())
	{
		ship.applyThrust();
	}

	// shoot bullets
	if (pUI.isSpace() && ship.isAlive())
	{
		Bullet newBullet;
		newBullet.fire(ship.getPoint(), ship.getVelocity(), (float)(ship.getOrientation() - 90));
		bullets.push_back(newBullet);
	}
}

void Game::draw(const Interface & pUI)
{
	if (ship.isAlive())
	{
		ship.draw();
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	for (int i = 0; i < rocks.size(); i++)
	{
		if ((*rocks[i]).isAlive())
		{
			(*rocks[i]).draw();
		}
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].getLife() <= 0)
		{
			bullets[i].kill();
			assert(!bullets[i].isAlive());
		}
		else if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
			wrap(bullets[i]);
			bullets[i].setLife(bullets[i].getLife() - 1);
		}
	}
}

void Game::advanceShip()
{
	if (ship.isAlive())
	{
		ship.advance();
		wrap(ship);
	}
}

void Game::advanceRocks()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->setRotation(rocks[i]->getRotation() + rocks[i]->getRotationAmount());
			// this bullet is alive, so tell it to move forward
			rocks[i]->advance();
			// TODO: wrapping
			wrap(*rocks[i]);
		}
	}
}

void Game::breakRock(Rock * pRock)
{
	if (pRock->hit() == "big")
	{
		// mediumRock1 velocity
		Velocity mediumVelocity(pRock->getVelocity().getDx(), pRock->getVelocity().getDy() + 1.0f);
		MediumRock * mediumRock1 = new MediumRock(pRock->getPoint(), mediumVelocity);
		// mediumRock2 velocity
		mediumVelocity.setDy(pRock->getVelocity().getDy() - 1.0f);
		MediumRock * mediumRock2 = new MediumRock(pRock->getPoint(), mediumVelocity);
		Velocity smallVelocity(pRock->getVelocity().getDx() + 2.0f, pRock->getVelocity().getDy());
		SmallRock * smallRock = new SmallRock(pRock->getPoint(), smallVelocity);

		// add the new rocks
		rocks.push_back(mediumRock1);
		rocks.push_back(mediumRock2);
		rocks.push_back(smallRock);

		// add another large rock
		rocks.push_back(new BigRock());
	}

	if (pRock->hit() == "medium")
	{
		// smallRock1 velocity
		Velocity smallVelocity(pRock->getVelocity().getDx() + 3.0f, pRock->getVelocity().getDy());
		SmallRock * smallRock1 = new SmallRock(pRock->getPoint(), smallVelocity);
		// smallRock2 velocity
		smallVelocity.setDx(pRock->getVelocity().getDy() - 3.0f);
		SmallRock * smallRock2 = new SmallRock(pRock->getPoint(), smallVelocity);

		rocks.push_back(smallRock1);
		rocks.push_back(smallRock2);
	}

	if (pRock->hit() == "small")
	{
		// do nothing, the rock just disappears
	}
}

void Game::handleCollisions()
{
	// ship collision
	if (ship.isAlive())
	{
		for (int j = 0; j < rocks.size(); j++)
		{
			if (getClosestDistance(ship, (*rocks[j])) < (*rocks[j]).getRadius())
			{
				Rock * pRock = rocks[j];
				breakRock(pRock);
				pRock->kill();
				ship.kill();
			}
		}
	}

	// bullet collisions
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, see if its too close
			for (int j = 0; j < rocks.size(); j++)
			{
				//check if the rock is at this point (in case it was hit)
				if ((*rocks[j]).isAlive())
				{
					if (getClosestDistance(bullets[i], (*rocks[j])) < (*rocks[j]).getRadius())
					{
						// make it easier to use rocks[j]
						Rock * pRock = rocks[j];
						// split the rock
						breakRock(pRock);

						// kill the rock and bullet
						pRock->kill();
						bullets[i].kill();
					}
				}
			}
		} // if bullet is alive

	} // for bullets
}

void Game::cleanUpZombies()
{
	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

	// Look for dead rocks
	vector<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock * pRock = *rockIt;

		if (!pRock->isAlive())
		{
			delete pRock;
			rockIt = rocks.erase(rockIt);
		}
		else
		{
			rockIt++; // advance
		}
	}
}

void Game::wrap(FlyingObject & object)
{
	if (object.getPoint().getX() >= 200.0f ||
		object.getPoint().getX() <= -200.0f)
	{
		float newX = object.getPoint().getX() * -1;
		Point newPoint(newX, object.getPoint().getY());
		object.setPoint(newPoint);
	}

	if (object.getPoint().getY() >= 200.0f ||
		object.getPoint().getY() <= -200.0f)
	{
		float newY = object.getPoint().getY() * -1;
		Point newPoint(object.getPoint().getX(), newY);
		object.setPoint(newPoint);
	}
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game::getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const
{
	// find the maximum distance traveled
	float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
	dMax = max(dMax, abs(obj2.getVelocity().getDx()));
	dMax = max(dMax, abs(obj2.getVelocity().getDy()));
	dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

	float distMin = std::numeric_limits<float>::max();
	for (float i = 0.0; i <= dMax; i++)
	{
		Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
			obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
		Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
			obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

		float xDiff = point1.getX() - point2.getX();
		float yDiff = point1.getY() - point2.getY();

		float distSquared = (xDiff * xDiff) + (yDiff * yDiff);

		distMin = min(distMin, distSquared);
	}

	return sqrt(distMin);
}

