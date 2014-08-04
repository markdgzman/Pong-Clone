#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Ball.cpp"

const int screenWidth = 900, screenHeight = 600;
const float ballSize = 8.f;

using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "Pong!");
	window.setFramerateLimit(60);
	CircleShape shape(ballSize);
	shape.setFillColor(Color::Green);
	shape.setPosition(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize);
	int direction = -20;
	float angle = 0;

	//Sound
	SoundBuffer buffer;


	if (!buffer.loadFromFile("Audio/paddlehit.wav"))
		return -1;

	Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(25);

	//Paddle Left
	Paddle p1(Paddle(Vector2f(10, screenHeight / 2 - 50), Vector2f(10, 100), Color::Red));
	Ball b(Ball(Vector2f(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize), ballSize, Color::Green));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				b.ball.setPosition(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize);
				direction = -20;
				angle = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				p1.paddle.move(0, 10);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				p1.paddle.move(0, -10);
			}
		}

		p1.Update();
		b.Update();

		//Paddle Wall Collision
		if (p1.collisionTop(0))
		{
			p1.paddle.setPosition(10, 1);
		}
		else if (p1.collisionBottom(screenHeight))
		{
			p1.paddle.setPosition(10, screenHeight - 101);
		}

		//Ball Collision
		if (b.collisionTop(p1))
		{
			direction = -direction;
			angle -= 5;
			sound.play();
			//angle -= 15;
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionTopCorner(p1))
		{
			direction = -direction;
			angle -= 8;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionMidTop(p1))
		{
			direction = -direction;
			angle -= 3;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionMiddle(p1))
		{
			direction = -direction;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionMidBottom(p1))
		{
			direction = -direction;
			angle += 3;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionBottomCorner(p1))
		{
			direction = -direction;
			angle += 8;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionBottom(p1))
		{
			direction = -direction;
			angle += 5;
			//angle -= 15;
			sound.play();
			std::cout << "Speed: " << direction << std::endl;
			std::cout << "Angle: " << angle << std::endl;
		}
		else if (b.collisionLast(p1))
		{
			direction = -direction;
			sound.play();
			std::cout << "Last Collision" << endl;
		}

		//Edge Collisions
		if (b.right >= screenWidth)
		{
			direction = -direction;
		}
		else if (b.bottom > screenHeight)
		{
			angle = -angle;
		}
		else if (b.top < 0)
		{
			angle = -angle;
		}

		b.ball.move(direction, angle);

		window.clear();
		window.draw(b.ball);
		window.draw(p1.paddle);
		//window.draw(shape);
		window.display();
	}

	return 0;
}

/*
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
RenderWindow window(sf::VideoMode(900, 600), "Pong");
window.setFramerateLimit(60);
//X Circle
CircleShape shape(20.f);
shape.setPosition(430, 280);
shape.setFillColor(sf::Color::Green);

//Position of Ball
float ballPosX = 430;
float ballPosY = 280;

//Speed of Ball
float ballVelX = 0;
float ballVelY = 0;

//Paddle Left
RectangleShape paddleLeft(Vector2f(20, 90));
paddleLeft.setFillColor(Color::White);
paddleLeft.setPosition(10, 260);

//Paddle Left Position
float pLeftY = 260;

float speed = 0;

float bottom;

while (window.isOpen())
{

Event event;
while (window.pollEvent(event))
{
if (event.type == Event::KeyPressed)
{
if (event.type == sf::Event::Closed)
window.close();

if (event.key.code == Keyboard::Space)
{
ballVelX = 1;
ballVelY = -1;
}

/*
if (event.key.code == Keyboard::Down)
{
pLeftY += 10;
paddleLeft.move(Vector2f(0, 15));
}

if (event.key.code == Keyboard::Up)
{
pLeftY -= 10;
paddleLeft.move(Vector2f(0, -15));
}


if (event.key.code == Keyboard::Up)
{
speed = -15;
}

if (event.key.code == Keyboard::Down)
{
speed = 15;
}
}

if (event.type == Event::KeyReleased)
{
if (event.key.code == Keyboard::Up)
{
speed = 0;
}
if (event.key.code == Keyboard::Down)
{
speed = 0;
}
}
}

if ((paddleLeft.getPosition().y + paddleLeft.getSize().y) < 600)
{
paddleLeft.move(Vector2f(0, speed));
}


//paddleLeft.

if (ballPosX < 0)
{
ballVelX = -ballVelX;
}
if (ballPosX > 860)
{
ballVelX = -ballVelX;
}

if (ballPosY > 0)
{
ballVelY = -ballVelY;
}
if (ballPosY < 580)
{
ballVelY = -ballVelY;
}

ballPosX += ballVelX;
ballPosY += ballVelY;

shape.setPosition(ballPosX, ballPosY);

window.clear();
window.draw(shape);
window.draw(paddleLeft);
window.display();
}

return 0;
}
*/