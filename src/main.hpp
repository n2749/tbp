#include <SFML/Graphics.hpp>

// Constants

#define NUMBER_OF_BODIES 3
#define G 6.67430e-11f
#define BODY_RADIUS 3
#define WINDOW_WIDTH 990
#define WINDOW_HEIGHT 540
#define WINDOW_TITLE "tbp"
#define SPAWN_PADDING_IN_PIXELS 100
#define MIN_MASS 5e2
#define MAX_MASS 10e2
#define DELTA_TIME 1e3f
#define CLOSE_ZERO 1e-9f

// Structs

struct Body {
	sf::CircleShape shape;
	float mass;
	sf::Vector2f vel;
	sf::Vector2f acc;
};

// Function prototypes

/* calculate next position of the bodies, based on position and masses of the
 * other bodies. All the bodies' positions are updated during the calculations.
 *
 * @param bodies			i.e positions and masses
 */
void updatePositions(Body* bodies, int numberOfBodies);


void updatePositionEuler(sf::Vector2f& pos, sf::Vector2f& vel, const sf::Vector2f& acc, float dt);


void calcAcc(Body* bodies, int numberOfBodies);


/* helping function for calculation. Makes the argument positive, and raises it
 * to the power of three.
 */
float powAbs3(sf::Vector2f pos);


sf::Vector2f vectorDiv(const sf::Vector2f pos1, const sf::Vector2f pos2);


void initBodies(Body* bodies, int numberOfBodies);


void drawBodies(sf::RenderWindow* window, Body* bodies, int numberOfBodies);


void initRand();


float getRandom();


float getRandomInRange(int min, int max);


sf::Vector2f getRandomPosition(int minx, int maxx, int miny, int maxy);


sf::Color getRandomColor();

