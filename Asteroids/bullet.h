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

	int life = 40;
	float orientation;
public:
	Bullet();
	Bullet(Velocity velocity, const Point point, const float orientation);

	int getLife() const { return this->life; }
	void setLife(const int life) { this->life = life; }
	float getOrientation() const { return this->orientation; }
	void setOrientation(const float orientation) { this->orientation = orientation; }

	void fire(Point point, Velocity shipVelocity, float angle);
	void draw();
};

#endif /* bullet_h */
