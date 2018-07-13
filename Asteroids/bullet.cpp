#include "bullet.h"
#include "uiDraw.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define BULLET_SPEED 5.0f

Bullet::Bullet()
{
	this->point.setX(0.0f);
	this->point.setY(0.0f);
	this->velocity.setDx(0.0f);
	this->orientation = 60.0f;
}

Bullet::Bullet(Velocity velocity, const Point point, const float orientation)
{
	this->velocity = velocity;
	this->point = point;
	this->orientation = orientation;
}

void Bullet::fire(Point point, float angle)
{
	this->point = point;
	this->orientation = orientation;
	this->velocity.setDx(BULLET_SPEED * (-cos(M_PI / 180.0 * angle)));
	this->velocity.setDy(BULLET_SPEED * (sin(M_PI / 180.0 * angle)));
}

void Bullet::draw()
{
	drawDot(this->point);
}
