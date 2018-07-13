#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "point.h"

class Bullet : public FlyingObject
{
private:
	//Velocity velocity;
	//Point point;
	//bool alive;

	float orientation;
public:
	Bullet();
	Bullet(Velocity velocity, const Point point, const float orientation);

	void fire(Point point, float angle);
	void draw();
};


#endif /* bullet_h */
