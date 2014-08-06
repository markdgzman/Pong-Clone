#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Ball.cpp"
#include <stdio.h>
#include <conio.h>

using namespace sf;
using namespace std;

const int screenWidth = 900, screenHeight = 600;
const float ballSize = 8.f;
Font font;
Text text;
Text p2Score;
Text retryText;
Text quitMenuText;

int direction = 0;
float angle = 0;
double paddleSpeed = 0;
bool winCondition = false , loseCondition = false, gameStart = false;
bool menuScreen = false, ballServe = false;
bool instructions = true;
int computerPaddleSpeed = 15;

int playerScore = 0, computerScore = 0;

//Paddle Left
Paddle p1(Paddle(Vector2f(10, screenHeight / 2 - 50), Vector2f(10, 100), Color::Red));
Ball b(Ball(Vector2f(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize), ballSize, Color::Green));

//Paddle Right
Paddle p2(Paddle(Vector2f(screenWidth - 20, screenHeight / 2 - 50), Vector2f(10, 100), Color::Blue));

//Sound
SoundBuffer buffer;
SoundBuffer scoreBuffer;
SoundBuffer menuSelectBuffer;
Sound scoreSound;
Sound sound;
Sound menuSelect;

void playerBallCollision();
void computerBallCollision();

int main()
{
	RenderWindow window(VideoMode(screenWidth, screenHeight), "Pong!");
	window.setFramerateLimit(60);
	CircleShape shape(ballSize);
	shape.setFillColor(Color::Green);
	shape.setPosition(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize);


	//Load Sound
	if (!buffer.loadFromFile("Audio/paddlehit.wav"))
		return -1;
	if (!scoreBuffer.loadFromFile("Audio/scoreUpdate.wav"))
		return -1;
	if (!menuSelectBuffer.loadFromFile("Audio/menuSelect.wav"))
		return -1;

	scoreSound.setBuffer(scoreBuffer);
	scoreSound.setVolume(35);
	sound.setBuffer(buffer);
	sound.setVolume(25);
	menuSelect.setBuffer(menuSelectBuffer);
	menuSelect.setVolume(25);

	//Load Image
	Texture texture;
	if (!texture.loadFromFile("Images/Back.png"))
		return -1;

	Texture controls;
	if (!controls.loadFromFile("Images/controls.png"))
		return -1;
	


	//Load Font
	if (!font.loadFromFile("Fonts/arial.ttf"))
		return -1;

	text.setFont(font);
	text.setString("0");

	p2Score.setFont(font);
	p2Score.setString("0");

	// set the character size
	text.setCharacterSize(44); // in pixels, not points!
	p2Score.setCharacterSize(44);

	//Set text position
	text.setPosition(screenWidth / 2 - 65, 10);
	p2Score.setPosition(screenWidth / 2 + 50, 10);

	//gameStart = true;
	//winCondition = true;
	//loseCondition = true;
	menuScreen = true;
	
	Text playMenu;
	Text quitMenu;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			
			if (Mouse::getPosition(window).x > 13 && Mouse::getPosition(window).x <112
				&& Mouse::getPosition(window).y > 313 && Mouse::getPosition(window).y < 354)
			{
				playMenu.setColor(Color::Red);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					gameStart = true;
					menuScreen = false;
					winCondition = false;
					loseCondition = false;
					menuSelect.play();
				}
			}
			else if (Mouse::getPosition(window).x > 13 && Mouse::getPosition(window).x < 112
				&& Mouse::getPosition(window).y > 413 && Mouse::getPosition(window).y < 454)
			{
				quitMenu.setColor(Color::Red);

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					window.close();
				}
			}
			else
			{
				//cout << "X: " << Mouse::getPosition(window).x << "  Y: " << Mouse::getPosition(window).y << endl;
				playMenu.setColor(Color::White);
				quitMenu.setColor(Color::White);
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				if (winCondition || loseCondition)
				{
					gameStart = false;
					winCondition = false;
					loseCondition = false;
					menuScreen = true;
					playerScore = 0;
					computerScore = 0;
					text.setString("0");
					p2Score.setString("0");
					
				}
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				if (gameStart)
				{

					if (direction == 0)
					{
						b.ball.setPosition(screenWidth / 2 - ballSize, screenHeight / 2 - ballSize);
						direction = 0;
						angle = 0;
						ballServe = true;
					}
					if (ballServe)
					{
						int randDirection = rand() % (10) + 1;
						switch (randDirection)
						{
						case 1:
							direction = -20;
							break;
						case 2:
							direction = 20;
							break;
						case 3:
							direction = -20;
							angle = 3;
							break;
						case 4:
							direction = -20;
							angle = -3;
							break;
						case 5:
							direction = 20;
							angle = 3;
							break;
						case 6:
							direction = 20;
							angle = -3;
							break;
						case 7:
							direction = -20;
							angle = 6;
							break;
						case 8:
							direction = -20;
							angle = -6;
							break;
						case 9:
							direction = 20;
							angle = 6;
							break;
						case 10:
							direction = 20;
							angle = -6;
							break;
						}

						ballServe = false;
					}
					
				}
				else if (winCondition || loseCondition && !gameStart)
				{
					playerScore = 0;
					computerScore = 0;
					text.setString(to_string(playerScore));
					p2Score.setString(to_string(computerScore));
					winCondition = false;
					loseCondition = false;
					//direction = 0;
					//angle = 0;
					gameStart = true;	
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Down) == false || Keyboard::isKeyPressed(Keyboard::Up) == false)
			{
				paddleSpeed = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				paddleSpeed = 15;
				//p1.paddle.move(0, 10);
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				paddleSpeed = -15;
				//p1.paddle.move(0, -10);
			}
		}

		if (menuScreen)
		{
				Sprite sprite;
				sprite.setTexture(texture);

				Sprite controlSprite;
				controlSprite.setTexture(controls);
				controlSprite.setPosition(300, 300);
				
				playMenu.setFont(font);
				playMenu.setString("Play");
				playMenu.setCharacterSize(55);
				playMenu.setPosition(Vector2f(10, 300));
				
				quitMenu.setFont(font);
				quitMenu.setString("Quit");
				quitMenu.setCharacterSize(55);
				quitMenu.setPosition(Vector2f(10, 400));

				window.clear(Color::Black);
				window.draw(playMenu);
				window.draw(sprite);
				window.draw(controlSprite);
				window.draw(quitMenu);
				window.display();
		}

		//Start Game
		if (gameStart)
		{
			//Computer AI
			if (direction == 0)
			{

			}
			else if (p2.bottom > screenHeight - 10)
			{
				p2.paddle.setPosition(Vector2f(screenWidth - 10, screenHeight - 111));
			}
			else if (p2.top < 10)
			{
				p2.paddle.setPosition(Vector2f(screenWidth - 10, 11));
			}
			else if (direction < 0)
			{
				if (p2.paddle.getPosition().y + 25 == screenHeight / 2)
				{
					p2.paddle.move(0, 0);
				}
				else if (p2.paddle.getPosition().y + 25 < screenHeight / 2)
				{
					p2.paddle.move(0, 5);
				}
				else if (p2.paddle.getPosition().y + 25 > screenHeight / 2)
				{
					p2.paddle.move(0, -5);
				}
			}
			else if (p2.paddle.getPosition().y - 50 != b.ball.getPosition().y + 4 &&
				p2.bottom < screenHeight-10 &&
				p2.top > 10)
			{
				if (b.ball.getPosition().y + 4 > p2.paddle.getPosition().y + 25)
				{
					p2.paddle.move(0, computerPaddleSpeed);
				}
				else if (b.ball.getPosition().y + 4 < p2.paddle.getPosition().y + 25)
				{
					p2.paddle.move(0, -computerPaddleSpeed);
				}
			}

			p1.paddle.move(0, paddleSpeed);

			p1.Update();
			p2.Update();
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

			//Edge Collisions
			//Right Edge Collision
			if (b.right >= screenWidth)
			{
				playerScore++;
				text.setString(to_string(playerScore));
				b.ball.setPosition(screenWidth / 2 - ballSize / 2, screenHeight / 2);
				direction = 0;
				angle = 0;
				scoreSound.play();
			}
			else if (b.left <= 0)
			{
				computerScore++;
				p2Score.setString(to_string(computerScore));
				b.ball.setPosition(screenWidth / 2 - ballSize / 2, screenHeight / 2);
				direction = 0;
				angle = 0;
				scoreSound.play();
			}

			//Ball Collision Method
			playerBallCollision();
			computerBallCollision();

			//Move ball
			b.ball.move(direction, angle);

			//Create Arena Objects
			//Top Line
			RectangleShape topLine(Vector2f(screenWidth, 10));
			topLine.setFillColor(Color::White);
			//Bottom Line
			RectangleShape bottomLine(Vector2f(screenWidth, 10));
			bottomLine.setPosition(0, screenHeight - 10);
			bottomLine.setFillColor(Color::White);
			//Middle Line
			RectangleShape middleLine(Vector2f(10, screenHeight));
			middleLine.setPosition(screenWidth / 2, 0);
			middleLine.setFillColor(Color::White);


			//Clear Screen and Draw objects
			window.clear();

			//Draw Arena
			window.draw(bottomLine);
			window.draw(topLine);
			window.draw(middleLine);

			window.draw(b.ball);
			window.draw(p1.paddle);
			window.draw(p2.paddle);
			window.draw(text);
			window.draw(p2Score);


			//Display
			window.display();


			//Win Condition
			if (playerScore >= 6)
			{
				gameStart = false;
				winCondition = true;
			}
			else if (computerScore >= 6)
			{
				gameStart = false;
				loseCondition = true;
			}
		}

		//Win or Lose Screen
		if (winCondition || loseCondition)
		{
			gameStart = false;
			Text endGame;
			endGame.setFont(font);
			retryText.setFont(font);
			quitMenuText.setFont(font);
			quitMenuText.setCharacterSize(50);
			quitMenuText.setString("Press Esc to return to Main Menu");

			if (winCondition)
			{
				endGame.setString("You Win!");
				endGame.setPosition(screenWidth / 2 - 350, screenHeight / 2 - 150);
			}
			else
			{
				endGame.setString("You Lose! \n You suck Mikey!");
				//Set endGame position
				endGame.setPosition(screenWidth / 2 - 350, screenHeight / 2 - 150);
			}
			// set the character size
			endGame.setCharacterSize(100); // in pixels, not points!

			retryText.setString("Press Space to try again");
			retryText.setCharacterSize(50);
			if (winCondition)
			{
				retryText.setPosition(screenWidth / 2 - 340, screenHeight / 2 - 10);
				quitMenuText.setPosition(screenWidth / 2 - 340, screenHeight / 2 + 70);
			}
			else
			{
				retryText.setPosition(screenWidth / 2 - 340, screenHeight / 2 + 100);
				quitMenuText.setPosition(screenWidth / 2 - 340, screenHeight / 2 + 170);
			}

			
			
			p1.paddle.move(0, paddleSpeed);

			p1.Update();
			p2.Update();
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


			window.clear(Color::Black);

			window.draw(b.ball);
			window.draw(p1.paddle);
			window.draw(p2.paddle);
			window.draw(text);
			window.draw(p2Score);
			window.draw(quitMenuText);
			window.draw(retryText);
			window.draw(endGame);
			window.display();
		}
	}

	return 0;
}



void playerBallCollision()
{
	if (b.collisionTop(p1))
	{
		direction = -direction;
		angle -= 5;
		sound.play();
	}
	else if (b.collisionTopCorner(p1))
	{
		direction = -direction;
		angle -= 8;
		sound.play();
	}
	else if (b.collisionMidTop(p1))
	{
		direction = -direction;
		angle -= 3;
		sound.play();
	}
	else if (b.collisionMiddle(p1))
	{
		direction = -direction;
		sound.play();
	}
	else if (b.collisionMidBottom(p1))
	{
		direction = -direction;
		angle += 3;
		sound.play();
	}
	else if (b.collisionBottomCorner(p1))
	{
		direction = -direction;
		angle += 8;
		sound.play();
	}
	else if (b.collisionBottom(p1))
	{
		direction = -direction;
		angle += 5;
		//angle -= 15;
		sound.play();
	}
	else if (b.collisionLast(p1))
	{
		direction = -direction;
		sound.play();
	}

	if (b.bottom > screenHeight-10)
	{
		angle = -angle;
	}
	else if (b.top < 10)
	{
		angle = -angle;
	}
}


void computerBallCollision()
{
	if (b.collisionTop(p2))
	{
		direction = -direction;
		angle -= 5;
		sound.play();
	}
	else if (b.collisionTopCorner(p2))
	{
		direction = -direction;
		angle -= 8;
		sound.play();
	}
	else if (b.collisionMidTop(p2))
	{
		direction = -direction;
		angle -= 3;
		sound.play();
	}
	else if (b.collisionMiddle(p2))
	{
		direction = -direction;
		sound.play();
	}
	else if (b.collisionMidBottom(p2))
	{
		direction = -direction;
		angle += 3;
		sound.play();
	}
	else if (b.collisionBottomCorner(p2))
	{
		direction = -direction;
		angle += 8;
		sound.play();
	}
	else if (b.collisionBottom(p2))
	{
		direction = -direction;
		angle += 5;
		//angle -= 15;
		sound.play();
	}
	else if (b.collisionLast(p2))
	{
		direction = -direction;
		sound.play();
	}
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