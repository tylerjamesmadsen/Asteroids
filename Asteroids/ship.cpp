#include "ship.h"
#include "uiDraw.h"

// Put your ship methods here

Ship::Ship()
{
	this->point.setX(0.0f);
	this->point.setY(0.0f);
	this->orientation = 0;
	this->velocity.setDx(0.0f);
	this->velocity.setDy(0.0f);
	this->alive = true;
	this->thrust = false;
}

void Ship::draw()
{
	drawShip(this->point, this->orientation, this->thrust );
}
