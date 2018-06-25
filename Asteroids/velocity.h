#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float dx;
	float dy;

public:
	// constructors
	Velocity();
	Velocity(float dx, float dy);

	// getters
	float getDx()	const	{ return dx; }
	float getDy()	const	{ return dy; }

	// setters
	void setDx(const float dx);
	void setDy(const float dy);
};

#endif // !VELOCITY_H

