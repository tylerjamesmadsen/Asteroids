/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include "flyingObject.h"

class Game
{
private:

public:
	Game(Point topLeft, Point topRight);

	float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;
	void advance();
	void handleInput(const Interface &pUI);
	void draw(const Interface &pUI);
};


#endif /* GAME_H */
