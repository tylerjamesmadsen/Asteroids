#include "ship.h"
#include "uiDraw.h"

#define _USE_MATH_DEFINES
#include <math.h>

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
	/*this->velocity.setDy(BULLET_SPEED * (cos(M_PI / 180.0 * angle)));
	this->velocity.setDx(BULLET_SPEED * (-sin(M_PI / 180.0 * angle)));*/
	float newDx = this->getVelocity().getDx() + 0.5f * (-sin(M_PI / 180.0 * this->orientation));
	float newDy = this->getVelocity().getDy() + 0.5f * (cos(M_PI / 180.0 * this->orientation));
	Velocity newVelocity(newDx, newDy);
	this->setVelocity(newVelocity);
}

void Ship::draw()
{
	drawShip(this->point, this->orientation, this->thrust );
}
