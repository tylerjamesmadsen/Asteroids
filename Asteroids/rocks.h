#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

# include "flyingObject.h"

// Define the following classes here:
//   Rock
class Rock : public FlyingObject
{
protected:
	int rotation;
	int radius;
public:
	int getRotation() const { return this->rotation; }
	void setRotation(const int rotation) { this->rotation = rotation; }
	int getRadius() const { return this->radius; }
	void setRadius(const int radius) { this->radius = radius; }
	void draw();
	virtual std::string hit() = 0;
};

//   BigRock
class BigRock : public Rock
{
private:

public:
	BigRock();
	void draw();
	std::string hit();
};

//   MediumRock
class MediumRock : public Rock
{
public:
	MediumRock(const Point point, const Velocity velocity);
	void draw();
	std::string hit();
};

//   SmallRock
class SmallRock : public Rock
{
public:
	SmallRock(const Point point, const Velocity velocity);
	void draw();
	std::string hit();
};

#endif /* rocks_h */
