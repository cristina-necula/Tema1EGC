//implementarea clasei pentru oponenti
#include "Framework/Polygon2D.h"
#include "Framework/Visual2D.h"
#include "Framework/DrawingWindow.h"
#include "Framework/Rectangle2d.h"
#include "Framework/Transform2D.h"

using namespace std;

class Opponents {

public:
	float opponent1x;
	float opponent1y;
	float step1x;
	float step1y;

	float opponent2x;
	float opponent2y;
	float step2x;
	float step2y;
	float angle2;

	float opponent3x;
	float opponent3y;
	float step3x;
	float step3y;

	float opponent4x;
	float opponent4y;
	float step4x;
	float step4y;
	float angle4;

public:

	Opponents::Opponents();

	void opponent1(float x, float y, Polygon2D *square1, Polygon2D *square2, Visual2D *context);
	void opponent2(float x, float y, Polygon2D *triangle1, Polygon2D *triangle2, Polygon2D *triangle3,
					Polygon2D *triangle4, Visual2D *context);
	void opponent3(float x, float y, Rectangle2D *square, Polygon2D *rhomb, Visual2D *context);
	void opponent4(float x, float y, Polygon2D *star1, Polygon2D *star2, Visual2D *context);

	void moveOpponent1(Object2D *square1, Object2D *square2);
	void moveOpponent2(Object2D *triangle1, Object2D *triangle2, Object2D *triangle3, Object2D *triangle4);
	void moveOpponent3(Object2D *square3, Object2D *rhomb);
	void moveOpponent4(Object2D *star1, Object2D *star2);

	void translateOpponent(Object2D *opponent, float x, float y);
	void addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context);
	void addAllOpponents_to_Visual2D(Visual2D *context);
	bool changeDirection(float x, float y);

};