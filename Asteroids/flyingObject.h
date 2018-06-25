#ifndef FLYING_OBJECT_H
#define FLYING_OBJECT_H

#include "velocity.h"
#include "point.h"

class FlyingObject {
protected:
	Velocity velocity;
	Point point;
	bool alive;
public:
	FlyingObject();
	virtual ~FlyingObject();

	Point getPoint() { return this->point; }
	Velocity getVelocity() { return this->velocity; }

	void setPoint(Point point) { this->point = point; }
	void setVelocity(Velocity velocity) { this->velocity = velocity; }

	bool isAlive();
	void kill();
	virtual void advance();
	virtual void draw() = 0;
};

#endif // !FLYING_OBJECT_H

