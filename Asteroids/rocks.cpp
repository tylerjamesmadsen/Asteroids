#include "rocks.h"
#include "uiDraw.h"

// Put your Rock methods here

BigRock::BigRock()
{
	this->radius = 16;
	float rand = (float)random(-200.0, 200.0);
	if (rand < 50.0f && rand >= 0.0f)
	{
		rand = 50.0f;
	}
	if (rand > -50.0f && rand <= 0.0f)
	{
		rand = -50.0f;
	}
	this->point.setX(rand);
	rand = (float)random(-200.0, 200.0);
	if (rand < 50.0f && rand >= 0.0f)
	{
		rand = 50.0f;
	}
	if (rand > -50.0f && rand <= 0.0f)
	{
		rand = -50.0f;
	}
	this->point.setY(rand);
	this->velocity.setDx((float)random(-1.0, 1.0));
	this->velocity.setDy((float)random(-1.0, 1.0));
	this->alive = true;
	this->rotation = 2; // TODO?
}

void BigRock::draw()
{
	drawLargeAsteroid(this->point, this->rotation);
}

std::string BigRock::hit()
{
	return "big";
}

MediumRock::MediumRock(const Point point, const Velocity velocity)
{
	this->radius = 8;
	this->point = point;
	this->velocity = velocity;
	this->alive = true;
	this->rotation = 5; // TODO?
}

void MediumRock::draw()
{
	drawMediumAsteroid(this->point, this->rotation);
}

std::string MediumRock::hit()
{
	return "medium";
}

SmallRock::SmallRock(const Point point, const Velocity velocity)
{
	this->radius = 4;
	this->point = point;
	this->velocity = velocity;
	this->alive = true;
	this->rotation = 10; // TODO?
}

void SmallRock::draw()
{
	drawSmallAsteroid(this->point, this->rotation);
}

std::string SmallRock::hit()
{
	return "small";
}

void Rock::draw()
{
	drawCircle(new Point(), 2);
}
