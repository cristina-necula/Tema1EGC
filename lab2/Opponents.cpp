//implementarea clasei pentru oponenti
#include "Framework/Polygon2D.h"
#include "Framework/Visual2D.h"
#include "Framework/DrawingWindow.h"
#include "Opponents.h"

using namespace std;

void opponent1(int x, int y, Polygon2D *square1, Polygon2D *square2){
	
	square1 = new Polygon2D(Color(0.5, 0, 0.5), false);
	square1->addPoint(Point2D(x, y));
	square1->addPoint(Point2D(x + 20, y));
	square1->addPoint(Point2D(x + 20, y - 20));
	square1->addPoint(Point2D(x, y - 20));

	square2 = new Polygon2D(Color(0.5, 0, 0.5), false);
	square2->addPoint(Point2D(x + 10, y - 10));
	square2->addPoint(Point2D(x + 30, y - 10));
	square2->addPoint(Point2D(x + 30, y - 30));
	square2->addPoint(Point2D(x + 10, y - 30));

}

void addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context) {
	DrawingWindow::addObject2D_to_Visual2D(opponent, context);
}