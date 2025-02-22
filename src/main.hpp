#include <SFML/Graphics.hpp>

// Constants

#define NUMBER_OF_BODIES 3
#define G 6.67408e-11
#define BODY_RADIUS 10
#define WINDOW_WIDTH 990
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "tbp"
#define SPAWN_PADDING_IN_PIXELS 100
#define MIN_MASS 5
#define MAX_MASS 100

// Structs

struct Body {
	sf::CircleShape shape;
	float mass;
};

// Function prototypes

/* calculate next position of the bodies, based on position and masses of the
 * other bodies. All the bodies' positions are updated during the calculations.
 *
 * @param bodies			i.e positions and masses
 */
void updatePositions(Body* bodies, int numberOfBodies);


void initBodies(Body* bodies, int numberOfBodies);


void drawBodies(sf::RenderWindow* window, Body* bodies, int numberOfBodies);


void initRand();


float getRandom();


float getRandomInRange(int min, int max);


sf::Vector2f getRandomPosition(int minx, int maxx, int miny, int maxy);

