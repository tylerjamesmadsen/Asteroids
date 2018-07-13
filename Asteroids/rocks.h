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
class Rock : FlyingObject
{
protected:
	int rotation;
public:
	int getRotation() const { return this->rotation; }
	void setRotation(const int rotation) { this->rotation = rotation; }
};

//   BigRock
class BigRock : Rock
{
private:

public:
	BigRock();
};

//   MediumRock
class MediumRock : Rock
{
public:
	MediumRock();
};

//   SmallRock
class SmallRock : Rock
{
public:
	SmallRock();
};



#endif /* rocks_h */
