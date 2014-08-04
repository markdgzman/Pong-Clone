#include <SFML/Graphics.hpp>
#include <iostream>
#include "Paddle.cpp"

using namespace sf;

class Ball
{
public:
	CircleShape ball;
	float bottom, left, right, top;

	Ball(Vector2f position, float size, Color color)
	{
		ball.setPosition(position);
		ball.setRadius(size);
		ball.setFillColor(color);
	}

	void Update()
	{
		bottom = ball.getPosition().y + ball.getRadius() * 2;
		left = ball.getPosition().x;
		right = ball.getPosition().x + ball.getRadius() * 2;
		top = ball.getPosition().y;
	}

	bool Collision(Ball b)
	{
		if (right < b.left || left > b.right ||
			top > b.bottom || bottom < b.top)
		{
			return false;
		}
		return true;
	}


	bool Collision(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom || bottom < p.top)
		{
			return false;
		}
		return true;
	}

	bool collisionTopCorner(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 95 || bottom < p.top)
		{
			return false;
		}
		return true;
	}

	bool collisionTop(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 90 || bottom < p.top + 5)
		{
			return false;
		}
		return true;
	}

	bool collisionMidTop(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 70 || bottom < p.top + 10)
		{
			return false;
		}
		return true;
	}

	bool collisionMiddle(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 40 || bottom < p.top + 30)
		{
			return false;
		}
		return true;
	}

	bool collisionMidBottom(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 10 || bottom < p.top + 70)
		{
			return false;
		}
		return true;
	}

	bool collisionBottom(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom - 90 || bottom < p.top + 5)
		{
			return false;
		}
		return true;
	}

	bool collisionBottomCorner(Paddle p)
	{
		if (right < p.left || left > p.right ||
			top > p.bottom || bottom < p.top + 95)
		{
			return false;
		}
		return true;
	}

	bool collisionLast(Paddle p)
	{
		if (right < p.left || left > p.right - 5 ||
			top > p.bottom || bottom < p.top)
		{
			return false;
		}
		return true;
	}

};
