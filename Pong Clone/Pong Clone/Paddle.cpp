#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Paddle
{
public:
	RectangleShape paddle;
	float bottom, left, right, top;

	Paddle(Vector2f position, Vector2f size, Color color)
	{
		paddle.setPosition(position);
		paddle.setSize(size);
		paddle.setFillColor(color);
	}

	void Update()
	{
		bottom = paddle.getPosition().y + paddle.getSize().y;
		left = paddle.getPosition().x;
		right = paddle.getPosition().x + paddle.getSize().x;
		top = paddle.getPosition().y;
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

	bool collisionTop(float t)
	{
		if (top > t)
		{
			return false;
		}
		return true;
	}

	bool collisionBottom(float b)
	{
		if (bottom < b)
		{
			return false;
		}
		return true;
	}

};
