#ifndef BULLET_H
#define BULLET_H

#include <graphics.h>

class Bullet
{
public:
	POINT position = { 0,0 };

public:
	Bullet() = default;
	~Bullet() = default;

	void Draw() const;

private:
	const int RADIUS = 10;
};

#endif // !BULLET_H
