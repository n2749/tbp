#include <SFML/Graphics.hpp>
#include <iostream>

// Constants
#define RESIZE_STEP 5e-2
#define MOVING_SPEED 1e-1
#define START_RADIUS 100.f
#define CIRCLE_IS_MOVING true
#define CIRCLE_IS_RESIZING false

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

// function prototypes
float getNewRadius(float currentRadius, bool isIncreasing);
void updatePos(sf::Vector2f* currentPos, Direction currentDir);
Direction getNewDirection(sf::Vector2u windowSize, sf::Vector2f currentPos, Direction currentDir, float currentRadius);

int main()
{
	sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
	sf::CircleShape shape(START_RADIUS);
	shape.setFillColor(sf::Color::Green);

	float currentRadius = START_RADIUS;
	bool increaseRadius = false;

	sf::Vector2u windowSize;
	sf::Vector2f currentPos;
	Direction direction = RIGHT;

	while (window.isOpen())
	{
		// closing window if it closes
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ( CIRCLE_IS_MOVING )
		{
			currentPos = shape.getPosition();
			sf::Vector2f currentPos = shape.getPosition();
			windowSize = window.getSize();

			direction = getNewDirection(windowSize, currentPos, direction, currentRadius * 2); // passing diameter here
			// printf("direction: %d", direction);
			updatePos(&currentPos, direction);
			shape.setPosition(currentPos);
		}


		if ( CIRCLE_IS_RESIZING )
		{
			currentRadius = getNewRadius(currentRadius, increaseRadius);
			shape.setRadius(currentRadius);
			if ( currentRadius >= 100.f || currentRadius <= 0.f )
			{
				increaseRadius = !increaseRadius;
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}


float getNewRadius(float currentRadius, bool isIncreasing)
{
	return isIncreasing
		? currentRadius + RESIZE_STEP
		: currentRadius - RESIZE_STEP;
}


void updatePos(sf::Vector2f* currentPos, Direction currentDir)
{
	switch ( currentDir )
	{
		case RIGHT:
			currentPos->x += MOVING_SPEED;
			break;
		case DOWN:
			currentPos->y += MOVING_SPEED;
			break;
		case LEFT:
			currentPos->x -= MOVING_SPEED;
			break;
		case UP:
			currentPos->y -= MOVING_SPEED;
			break;
		default:
			std::cout << "you did something wrong";
			break;
	}
	// printf("dir: %d, x: %f, y: %f\n", currentDir, currentPos.x, currentPos.y);
}

Direction getNewDirection(sf::Vector2u windowSize, sf::Vector2f currentPos, Direction currentDir, float size)
{
	// if MOVING_STEP is greatly less than the window, then mostly it is
	// inbounds with the window
	bool xInBounds = currentPos.x > 0 && currentPos.x + size < windowSize.x;
	bool yInBounds = currentPos.y > 0 && currentPos.y + size < windowSize.y;
	bool keepPos = xInBounds && yInBounds;

	// printf("w(%d, %d), p(%f, %f), r: %f x %d, y %d, k %d\n"
	//		, windowSize.x
	//		, windowSize.y
	//		, currentPos.x
	//		, currentPos.y
	//		, size
	//		, xInBounds
	//		, yInBounds
	//		, keepPos);

	if ( keepPos )
	{
		return currentDir;
	}

	if ( currentDir == RIGHT && currentPos.x + size > windowSize.x ) return DOWN;
	if ( currentDir == DOWN  && currentPos.y + size > windowSize.y ) return LEFT;
	if ( currentDir == LEFT  && currentPos.x < 0 ) return UP;
	if ( currentDir == UP    && currentPos.y < 0 ) return RIGHT;

	return currentDir;
}

