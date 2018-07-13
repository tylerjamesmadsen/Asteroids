#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"

// Put your Ship class here
class Ship : public FlyingObject
{
private:
	int orientation;
	bool thrust;
	const int radius = 10;

public:
	Ship();

	int getOrientation() const { return this->orientation; }
	void setOrientation(const float orientation) { this->orientation = orientation; }
	bool getThrust() const { return this->thrust; }
	void setThrust(const bool thrust) { this->thrust = thrust; }
	int getRadius() const { return this->radius; }

	void rotateLeft();
	void rotateRight();
	void applyThrust();

	void draw();
};

#endif /* ship_h */
