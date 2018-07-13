/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"

#include "bullet.h"
#include "rocks.h"
#include "ship.h"

#define CLOSE_ENOUGH 15


class Game
{
private:
	Point topLeft;
	Point bottomRight;

	Ship ship;
	std::vector<Bullet> bullets;

	// TODO: rocks
	//std::vector<Rock> rocks;
	std::vector<BigRock> rocks;

public:
	Game(Point topLeft, Point bottomRight);

	float getClosestDistance(FlyingObject &obj1, FlyingObject &obj2) const;
	void advance();
	void handleInput(const Interface &pUI);
	void draw(const Interface &pUI);

	void advanceBullets();
	void advanceShip();
	void advanceRocks();

	void handleCollisions();
	void cleanUpZombies();

	template <class T>
	void wrap(T object);
};


#endif /* GAME_H */
