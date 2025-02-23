#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <cmath>

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
		calcAcc(bodies, sizeof(bodies) / sizeof(bodies[0]));
		updatePositions(bodies, sizeof(bodies) / sizeof(bodies[0]));
		drawBodies(
			&window,
			bodies,
			sizeof(bodies) / sizeof(bodies[0])
		);
	}
	return 0;
}


void printPos(Body* bodies)
{
	for (size_t i = 0; i < 3; i++)
	{
		printf("bodies[%d] (%.18f, %.18f)\n", i, bodies[i].shape.getPosition().x, bodies[i].shape.getPosition().y);
	}
}


void calcAcc(Body* bodies, int numberOfBodies)
{
	sf::Vector2f pos1 = bodies[0].shape.getPosition();
	sf::Vector2f pos2 = bodies[1].shape.getPosition();
	sf::Vector2f pos3 = bodies[2].shape.getPosition();

	float m1 = bodies[0].mass;
	float m2 = bodies[1].mass;
	float m3 = bodies[2].mass;

	float one_two   = powAbs3(pos1 - pos2);
	float one_three = powAbs3(pos1 - pos3);
	float two_three = powAbs3(pos3 - pos2);

	bodies[0].acc = -G * (m2 * (pos1 - pos2) / one_two   + m3 * (pos1 - pos3) / one_three);
	bodies[1].acc = -G * (m3 * (pos2 - pos3) / two_three + m1 * (pos2 - pos1) / one_two  );
	bodies[2].acc = -G * (m1 * (pos3 - pos1) / one_three + m3 * (pos3 - pos2) / two_three);
}


void updatePositions(Body* bodies, int numberOfBodies)
{
	for (size_t i = 0; i < numberOfBodies; i++)
	{
		// getPosition returns const
		sf::Vector2f pos = bodies[i].shape.getPosition();

		updatePositionEuler(
				pos,
				bodies[i].vel,
				bodies[i].acc,
				DELTA_TIME
		);

		bodies[i].shape.setPosition(pos);

		printf(
			"bodies[%d]: pos(%f, %f) vel(%.18f, %.18f) acc(%.18f, %.18f)\n",
			i,
			pos.x, pos.y,
			bodies[i].vel.x, bodies[i].vel.y,
			bodies[i].acc.x, bodies[i].acc.y
		);
	}
}


void updatePositionEuler(sf::Vector2f& pos, sf::Vector2f& vel, const sf::Vector2f& acc, float dt) {
    vel += acc * dt;
    pos += vel * dt;
}


sf::Vector2f vectorDiv(const sf::Vector2f pos1, const sf::Vector2f pos2)
{
	return sf::Vector2f(
		pos2.x != 0 ? pos1.x / pos2.x : pos1.x / CLOSE_ZERO,
		pos2.y != 0 ? pos1.y / pos2.y : pos1.y / CLOSE_ZERO
	);
}


float powAbs3(sf::Vector2f pos)
{
	float magnitude = std::sqrt(pos.x * pos.x + pos.y * pos.y);
	return magnitude * magnitude * magnitude;
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
		bodies[i].shape.setFillColor(getRandomColor());
		bodies[i].mass = getRandomInRange(MIN_MASS, MAX_MASS);
		bodies[i].vel = {0, 0};
		bodies[i].acc = {0, 0};
	}
	for (size_t i = 0; i < numberOfBodies; i++)
	{
		printf("bodies[%d].mass %.18f, bodies[%d].position(%.18f, %.18f)\n",
				i,
				bodies[i].mass,
				i,
				bodies[i].shape.getPosition().x,
				bodies[i].shape.getPosition().y);
	}
}


void initRand()
{
	 std::srand(std::time(nullptr));
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


sf::Color getRandomColor()
{
	sf::Color colors[6] = {
		sf::Color::Red,
		sf::Color::Green,
		sf::Color::Blue,
		sf::Color::Yellow,
		sf::Color::Magenta,
		sf::Color::Cyan
	};
	return colors[static_cast<int>(getRandomInRange(0, 6))];
}


