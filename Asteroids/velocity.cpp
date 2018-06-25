#include "velocity.h"

// constructors
Velocity::Velocity()
{
	setDx(0.0f);
	setDy(0.0f);
}

Velocity::Velocity(float dx, float dy)
{
	setDx(dx);
	setDy(dy);
}

// setters
void Velocity::setDx(const float dx)
{
	this->dx = dx;
}

void Velocity::setDy(const float dy)
{
	this->dy = dy;
}