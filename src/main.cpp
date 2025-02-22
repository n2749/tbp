#include <SFML/Graphics.hpp>
#include <iostream>

#include "main.hpp"


int main()
{
	sf::RenderWindow window(
			sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
			WINDOW_TITLE);

	Body bodies[NUMBER_OF_BODIES];
	initRand();
	initBodies(bodies, sizeof(bodies) / sizeof(bodies[0]));

	while (window.isOpen())
	{
		// closing window if it closes
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		updatePositions(bodies, sizeof(bodies) / sizeof(bodies[0]));
		drawBodies(
			&window,
			bodies,
			sizeof(bodies) / sizeof(bodies[0])
		);
	}
	return 0;
}



void updatePositions(Body* bodies, int numberOfBodies)
{
	for (size_t i = 0; i < numberOfBodies; i++)
	{
		sf::Vector2f pos = bodies[i].shape.getPosition();
		// printf("%d, (%f, %f))\n", i, pos.x, pos.y);
	}
}


void drawBodies(sf::RenderWindow* window, Body* bodies, int numberOfBodies)
{
	window->clear();
	for (size_t i = 0; i < numberOfBodies; i++)
		window->draw(bodies[i].shape);
	window->display();
}


void initBodies(Body* bodies, int numberOfBodies)
{
	for (size_t i = 0; i < numberOfBodies; i++)
	{
		sf::Vector2f pos = getRandomPosition(
				SPAWN_PADDING_IN_PIXELS,
				WINDOW_WIDTH - SPAWN_PADDING_IN_PIXELS,
				SPAWN_PADDING_IN_PIXELS,
				WINDOW_HEIGHT - SPAWN_PADDING_IN_PIXELS);

		bodies[i].shape.setPosition(pos);
		bodies[i].shape.setRadius(BODY_RADIUS);
		bodies[i].mass = getRandomInRange(MIN_MASS, MAX_MASS);
	}
	for (size_t i = 0; i < numberOfBodies; i++)
	{
		printf("bodies[%d].mass %f, bodies[%d].position(%f, %f)\n",
				i,
				bodies[i].mass,
				i,
				bodies[i].shape.getPosition().x,
				bodies[i].shape.getPosition().y);
	}
}


void initRand()
{
	 std::srand(std::time({}));
}


float getRandom()
{
	return (static_cast <float> (std::rand())) /
		(static_cast <float> (RAND_MAX));
}


float getRandomInRange(int min, int max)
{
	float some = getRandom() * max;
	some = some > min ? some : min;
	return some;
}


sf::Vector2f getRandomPosition(int minx, int maxx, int miny, int maxy)
{
	float x = getRandomInRange(minx, maxx);
	float y = getRandomInRange(miny, maxy);
	return {x, y};
}

