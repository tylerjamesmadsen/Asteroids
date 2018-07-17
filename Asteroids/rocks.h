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
	virtual int getRotationAmount() = 0;
};

//   BigRock
class BigRock : public Rock
{
private:
	const int rotationAmount = 2;
public:
	BigRock();
	void draw();
	std::string hit();
	int getRotationAmount() { return this->rotationAmount; }
};

//   MediumRock
class MediumRock : public Rock
{
private:
	const int rotationAmount = 5;
public:
	MediumRock(const Point point, const Velocity velocity);
	void draw();
	std::string hit();
	int getRotationAmount() { return this->rotationAmount; }
};

//   SmallRock
class SmallRock : public Rock
{
private:
	const int rotationAmount = 10;
public:
	SmallRock(const Point point, const Velocity velocity);
	void draw();
	std::string hit();
	int getRotationAmount() { return this->rotationAmount; }
};

#endif /* rocks_h */
