#include "ship.h"
#include "uiDraw.h"

// Put your ship methods here

Ship::Ship()
{
	this->point.setX(0.0f);
	this->point.setY(0.0f);
	this->orientation = 270;
	this->velocity.setDx(0.0f);
	this->velocity.setDy(0.0f);
	this->alive = true;
	this->thrust = false;
}

void Ship::rotateLeft()
{
	this->orientation += 6;
}

void Ship::rotateRight()
{
	this->orientation -= 6;
}

void Ship::applyThrust()
{
	this->thrust = true;
	// TODO
	/*this->velocity.setDy(0.5);
	this->velocity.setDx(0.5);*/
}

void Ship::draw()
{
	drawShip(this->point, this->orientation, this->thrust );
}
