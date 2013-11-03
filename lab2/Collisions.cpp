#include "Collisions.h"

using namespace std;

Collisions::Collisions(){

	this->opponent1 = true;
	this->opponent2 = true;
	this->opponent3 = true;
	this->opponent4 = true;
}

void Collisions::createImaginaryRectangles(Opponents *opponents, Polygon2D *weapon){
	
	if(opponents->squareO1 != NULL && opponents->squareO2 != NULL)
		this->imgOpponent1 = new Rectangle2D(Point2D(opponents->opponent1x, opponents->opponent1y - 30), 30, 30);
	else
		this->opponent1 = false;

	if(opponents->triangleO1 != NULL && opponents->triangleO2 != NULL && opponents->triangleO3 != NULL && opponents->triangleO4 != NULL)
		this->imgOpponent2 = new Rectangle2D(Point2D(opponents->opponent2x - 10, opponents->opponent2y - 20), 40, 40);
	else
		this->opponent2 = false;
	
	if(opponents->squareO != NULL && opponents->rhombO != NULL)
		this->imgOpponent3 = new Rectangle2D(Point2D(opponents->opponent3x, opponents->opponent3y), 30, 30);
	else
		this->opponent3 = false;

	if(opponents->starO1 != NULL && opponents->starO2 != NULL)
		this->imgOpponent4 = new Rectangle2D(Point2D(opponents->opponent4x - 15, opponents->opponent4y - 25), 30, 35);
	else
		this->opponent4 = false;

}

bool Collisions::killOpponent(Opponents *opponents, Polygon2D *player, Polygon2D *weapon){

	//creez dreptunghiuri imaginare pentru arma si oponenti
	createImaginaryRectangles(opponents, weapon);
	
	if(this->opponent1) {
		if(intersected(weapon, this->imgOpponent1)){
			DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO1, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO2, opponents->context);

			delete opponents->squareO1;
			opponents->squareO1 = NULL;
			delete opponents->squareO2;
			opponents->squareO2 = NULL;
		}
	}

	if(this->opponent3){
		if(intersected(weapon, this->imgOpponent3)){
			DrawingWindow::removeObject2D_from_Visual2D(opponents->rhombO, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO, opponents->context);

			delete opponents->rhombO;
			opponents->rhombO = NULL;
			delete opponents->squareO;
			opponents->squareO = NULL;
		}
	}

	if(this->opponent4){
		if(intersected(weapon, this->imgOpponent4)){
			DrawingWindow::removeObject2D_from_Visual2D(opponents->starO1, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->starO2, opponents->context);

			delete opponents->starO1;
			opponents->starO1 = NULL;
			delete opponents->starO2;
			opponents->starO2 = NULL;
		}
	}

	if(this->opponent2){
		if(intersected(weapon, this->imgOpponent2)){
			DrawingWindow::removeObject2D_from_Visual2D(opponents->triangleO1, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->triangleO2, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->triangleO3, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->triangleO4, opponents->context);

			delete opponents->triangleO1;
			opponents->triangleO1 = NULL;
			delete opponents->triangleO2;
			opponents->triangleO2 = NULL;
			delete opponents->triangleO3;
			opponents->triangleO3 = NULL;
			delete opponents->triangleO4;
			opponents->triangleO4 = NULL;
		}
	}
	return false;
}

bool Collisions::lineIntersection(Point2D *p1, Point2D *p2, Point2D *t1, Point2D *t2){
	
	float diff1x, diff1y, diff2x, diff2y;
    diff1x = p2->x - p1->x;     
	diff1y = p2->y - p1->y;
    diff2x = t2->x - t1->x;
	diff2y = t2->y - t1->y;

    float s, t;
	s = (-diff1y * (p1->x - t1->x) + diff1x * (p1->y - t1->y)) / (-diff2x * diff1y + diff1x * diff2y);
	t = (diff2x * (p1->y - t1->y) - diff2y * (p1->x - t1->x)) / (-diff2x * diff1y + diff1x * diff2y);

    if (s <0  || s > 1 || t < 0 || t > 1)
			return false;
	else 
		return true;
}

bool Collisions::intersected(Polygon2D *weapon, Rectangle2D *opnt){

		for(int j = 0; j < opnt->transf_points.size(); j++){

			if(j == 3){
				if(lineIntersection(weapon->transf_points[0], weapon->transf_points[1], 
									opnt->transf_points[3], opnt->transf_points[0]))
					return true;
				if(lineIntersection(weapon->transf_points[1], weapon->transf_points[2],
									opnt->transf_points[3], opnt->transf_points[0]))
					return true;
			} 
			else {
				if(lineIntersection(weapon->transf_points[0], weapon->transf_points[1],
									opnt->transf_points[j], opnt->transf_points[j+1]))
					return true;
				if(lineIntersection(weapon->transf_points[1], weapon->transf_points[2],
									opnt->transf_points[j], opnt->transf_points[j+1]))
					return true;
			}

		}
		return false;
}