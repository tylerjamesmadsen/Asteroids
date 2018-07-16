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
	if (pUI.isSpace())
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
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();
			wrap(bullets[i]);
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
		if ((*rocks[i]).isAlive())
		{
			// this bullet is alive, so tell it to move forward
			(*rocks[i]).advance();
			// TODO: wrapping
			//wrap(rocks[i]);
		}
	}
}

void Game::handleCollisions()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, see if its too close
			for (int j = 0; j < rocks.size(); j++)
			{
				 //check if the rock is at this point (in case it was hit)
				if (/*rocks[i] != NULL && */(*rocks[j]).isAlive())
				{
					// BTW, this logic could be more sophisiticated, but this will
					// get the job done for now...
					/*if (fabs(bullets[i].getPoint().getX() - rocks[i].getPoint().getX()) < CLOSE_ENOUGH
						&& fabs(bullets[i].getPoint().getY() - rocks[i].getPoint().getY()) < CLOSE_ENOUGH)*/
					if (getClosestDistance(bullets[i], (*rocks[j])) < CLOSE_ENOUGH)
					{
						// make it easier to use rocks[j]
						Rock * pRock = rocks[j];
						// split the rock
 						if (pRock->hit() == "big")
						{
							Velocity mediumVelocity(pRock->getVelocity().getDx(), pRock->getVelocity().getDy() + 1.0f);
							MediumRock * mediumRock1 = new MediumRock(pRock->getPoint(), mediumVelocity);
							mediumVelocity.setDy(pRock->getVelocity().getDy() - 1.0f);
							MediumRock * mediumRock2 = new MediumRock(pRock->getPoint(), mediumVelocity);
							Velocity smallVelocity(pRock->getVelocity().getDx() + 2.0f, pRock->getVelocity().getDy());
							SmallRock * smallRock = new SmallRock(pRock->getPoint(), smallVelocity);

							// kill the rock and bullet
							pRock->kill();
							bullets[i].kill();

							// add the new rocks
							rocks.push_back(mediumRock1);
							rocks.push_back(mediumRock2);
							rocks.push_back(smallRock);
						}

						if ((*rocks[j]).hit() == "medium")
						{
							Velocity smallVelocity(pRock->getVelocity().getDx() + 3.0f, pRock->getVelocity().getDy());
							SmallRock * smallRock1 = new SmallRock(pRock->getPoint(), smallVelocity);
							smallVelocity.setDx(pRock->getVelocity().getDy() + 3.0f);
							SmallRock * smallRock2 = new SmallRock(pRock->getPoint(), smallVelocity);

							// kill the rock and bullet
							pRock->kill();
							bullets[i].kill();

							rocks.push_back(smallRock1);
							rocks.push_back(smallRock2);
						}

						if ((*rocks[j]).hit() == "small")
						{
							// kill the rock and bullet
							pRock->kill();
							bullets[i].kill();
						}
					}
				}
			}
		} // if bullet is alive

	} // for bullets
}

void Game::cleanUpZombies()
{
}

template <class T>
void Game::wrap(T object)
{
	if (object.getPoint().getX() > 200.0f ||
		object.getPoint().getX() < -200.0f)
	{
		object.getPoint().setX(
			object.getPoint().getX() * -1);
	}

	if (object.getPoint().getY() > 200.0f ||
		object.getPoint().getY() < -200.0f)
	{
		object.getPoint().setY(
			object.getPoint().getY() * -1);
	}
}

// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const
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
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

