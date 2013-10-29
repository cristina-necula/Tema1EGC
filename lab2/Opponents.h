//implementarea clasei pentru oponenti
#include "Framework/Polygon2D.h"
#include "Framework/Visual2D.h"
#include "Framework/DrawingWindow.h"
#include "Framework/Rectangle2d.h"
#include "Framework/Transform2D.h"

using namespace std;

class Opponents {

public:

	Opponents::Opponents(){
	}

	void opponent1(int x, int y, Polygon2D *square1, Polygon2D *square2, Visual2D *context){

		square1->addPoint(Point2D(x, y));
		square1->addPoint(Point2D(x + 20, y));
		square1->addPoint(Point2D(x + 20, y - 20));
		square1->addPoint(Point2D(x, y - 20));

		square2->addPoint(Point2D(x + 10, y - 10));
		square2->addPoint(Point2D(x + 30, y - 10));
		square2->addPoint(Point2D(x + 30, y - 30));
		square2->addPoint(Point2D(x + 10, y - 30));

		addOpponent_to_Visual2D(square1, context);
		addOpponent_to_Visual2D(square2, context);

	}

	void opponent2(int x, int y, Polygon2D *triangle1, Polygon2D *triangle2, Polygon2D *triangle3,
		Polygon2D *triangle4, Visual2D *context){

		triangle1->addPoint(Point2D(x, y));
		triangle1->addPoint(Point2D(x + 30, y));
		triangle1->addPoint(Point2D(x - 10, y + 20));

		triangle2->addPoint(Point2D(x, y));
		triangle2->addPoint(Point2D(x + 30, y));
		triangle2->addPoint(Point2D(x - 10, y - 20));

		triangle3->addPoint(Point2D(x, y));
		triangle3->addPoint(Point2D(x + 30, y));
		triangle3->addPoint(Point2D(x - 10, y + 20));

		triangle4->addPoint(Point2D(x, y));
		triangle4->addPoint(Point2D(x + 30, y));
		triangle4->addPoint(Point2D(x - 10, y - 20));

		addOpponent_to_Visual2D(triangle1, context);
		addOpponent_to_Visual2D(triangle2, context);
		addOpponent_to_Visual2D(triangle3, context);
		addOpponent_to_Visual2D(triangle4, context);

	}

	void opponent3(int x, int y, Rectangle2D *square, Polygon2D *rhomb, Visual2D *context){

		rhomb->addPoint(Point2D(x, y + 15));
		rhomb->addPoint(Point2D(x + 15, y));
		rhomb->addPoint(Point2D(x + 30, y + 15));
		rhomb->addPoint(Point2D(x + 15, y + 30));

		addOpponent_to_Visual2D(square, context);
		addOpponent_to_Visual2D(rhomb, context);

	}

	void opponent4(int x, int y, Polygon2D *star1, Polygon2D *star2, Visual2D *context){

		star1->addPoint(Point2D(x, y + 10));
		star1->addPoint(Point2D(x + 15, y - 15));
		star1->addPoint(Point2D(x - 15, y - 15));

		star2->addPoint(Point2D(x - 15, y));
		star2->addPoint(Point2D(x + 15, y));
		star2->addPoint(Point2D(x, y - 25));

		addOpponent_to_Visual2D(star1, context);
		addOpponent_to_Visual2D(star2, context);

	}

	void moveOpponent1(float step, float u, Polygon2D *square1, Polygon2D *square2, int x, int y){
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(x, y);
	}

	void translateOpponent(Object2D *opponent, float x, float y){
		Transform2D::translateMatrix(x, y);
	}

	void addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context) {
		DrawingWindow::addObject2D_to_Visual2D(opponent, context);
	}

};