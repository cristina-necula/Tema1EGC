#include "Opponents.h"

using namespace std;

class Collisions {

public:

	std::vector <Opponents*> opponents;
	Polygon2D *player;
	Polygon2D *weapon;

public:

	Collisions::Collisions();
	bool weaponOpponent();

};