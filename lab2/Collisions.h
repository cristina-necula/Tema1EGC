#include "Opponents.h"

using namespace std;

class Collisions {

public:

	Opponents opponent;
	Polygon2D *player;
	Polygon2D *weapon;

	/*std::vector<Polygon2D*> opponent1;
	std::vector<Polygon2D*> opponent2;
	std::vector<Polygon2D*> opponent3;
	std::vector<Polygon2D*> opponent4;*/

	Rectangle2D *imgOpponent1;
	bool opponent1;
	
	Rectangle2D *imgOpponent2;
	bool opponent2;

	Rectangle2D *imgOpponent3;
	bool opponent3;

	Rectangle2D *imgOpponent4;
	bool opponent4;

	Rectangle2D *imgWeapon;

public:

	Collisions::Collisions();
	void createImaginaryRectangles(Opponents *opponents, Polygon2D *weapon);
	bool intersected(Polygon2D *weapon, Rectangle2D *opnt);
	bool lineIntersection(Point2D *p1, Point2D *p2, Point2D *t1, Point2D *t2);
	bool killOpponent(Opponents *opponents, Polygon2D *player, Polygon2D *weapon);
	std::pair<float, float> getMinMax(Polygon2D *polygon);
};