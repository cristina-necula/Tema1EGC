//implementarea clasei pentru oponenti
#include "Opponents.h"

using namespace std;

	float opponent1x;
	float opponent1y;
	float step1x;
	float step1y;
	static int direction1 = 1;

	float opponent2x;
	float opponent2y;
	float step2x;
	float step2y;
	float angle2;

	float opponent3x;
	float opponent3y;
	float step3x;
	float step3y;
	static int direction3 = 1;

	float opponent4x;
	float opponent4y;
	float step4x;
	float step4y;
	static int direction4 = 1;
	float angle4;
	
	Opponents::Opponents(){
		
	}

	void Opponents::opponent1(float x, float y, Polygon2D *square1, Polygon2D *square2, Visual2D *context){

		this->opponent1x = x;
		this->opponent1y = y;
		this->step1x = 1;
		this->step1y = 1;

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

	void Opponents::moveOpponent1(Object2D *square1, Object2D *square2) {
		
		if(changeDirection(this->opponent1x, this->opponent1y)) {
			direction1 *= -1;
			this->step1x = (rand() % 10) / 5;
			this->step1y = (rand() % 10) / 3; 
		}

		this->opponent1x += this->step1x * direction1;
		this->opponent1y += this->step1y * direction1;

		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(this->step1x * direction1, this->step1y * direction1);
		Transform2D::applyTransform_o(square1);
		Transform2D::applyTransform_o(square2);
	}

	void Opponents::opponent2(float x, float y, Polygon2D *triangle1, Polygon2D *triangle2, Polygon2D *triangle3,
		Polygon2D *triangle4, Visual2D *context){

		this->opponent2x = x;
		this->opponent2y = y;
		this->step2x = 1;
		this->step2y = 1;
		this->angle2 = 0;

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

	void Opponents::moveOpponent2(Object2D *triangle1, Object2D *triangle2, Object2D *triangle3, Object2D *triangle4){

		Transform2D::loadIdentityMatrix();

		if(changeDirection(this->opponent2x, this->opponent2y)) {
			this->angle2 += 2.3;
			Transform2D::translateMatrix(-this->opponent2x, -this->opponent2y);
			Transform2D::rotateMatrix(2.3);
			Transform2D::translateMatrix(this->opponent2x, this->opponent2y);
		}

		this->opponent2x += this->step2x * cos(this->angle2);
		this->opponent2y += this->step2y * sin(this->angle2);

		Transform2D::translateMatrix(this->step2x * cos(this->angle2), 
									 this->step2y * sin(this->angle2));
		Transform2D::applyTransform_o(triangle1);
		Transform2D::applyTransform_o(triangle2);
		Transform2D::applyTransform_o(triangle3);
		Transform2D::applyTransform_o(triangle4);

	}

	void Opponents::opponent3(float x, float y, Rectangle2D *square, Polygon2D *rhomb, Visual2D *context){

		this->opponent3x = x;
		this->opponent3y = y;

		this->step3x = 1;
		this->step3y = 1;

		rhomb->addPoint(Point2D(x, y + 15));
		rhomb->addPoint(Point2D(x + 15, y));
		rhomb->addPoint(Point2D(x + 30, y + 15));
		rhomb->addPoint(Point2D(x + 15, y + 30));

		addOpponent_to_Visual2D(square, context);
		addOpponent_to_Visual2D(rhomb, context);

	}

	void Opponents::moveOpponent3(Object2D *square3, Object2D *rhomb){


		if(changeDirection(this->opponent3x, this->opponent3y)) {
			direction3 *= -1;
			this->step3x = (rand() % 10) / 2;
			this->step3y = (rand() % 10) / 5;
		}

		this->opponent3x += this->step3x * direction3;
		this->opponent3y += this->step3y * direction3;

		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(this->step3x * direction3, this->step3y * direction3);
		Transform2D::applyTransform_o(square3);
		Transform2D::applyTransform_o(rhomb);
	}

	void Opponents::opponent4(float x, float y, Polygon2D *star1, Polygon2D *star2, Visual2D *context){

		this->opponent4x = x;
		this->opponent4y = y;

		this->step4x = 1;
		this->step4y = 1;

		this->angle4 = 0.05;

		star1->addPoint(Point2D(x, y + 10));
		star1->addPoint(Point2D(x + 15, y - 15));
		star1->addPoint(Point2D(x - 15, y - 15));

		star2->addPoint(Point2D(x - 15, y));
		star2->addPoint(Point2D(x + 15, y));
		star2->addPoint(Point2D(x, y - 25));

		addOpponent_to_Visual2D(star1, context);
		addOpponent_to_Visual2D(star2, context);

	}

	void Opponents::moveOpponent4(Object2D *star1, Object2D *star2) {

		if(changeDirection(this->opponent4x, this->opponent4y)) {
			direction4 *= -1;
			this->step4x = (rand() % 10) / 4;
			this->step4y = (rand() % 10) / 3;
			this->angle4 += 0.01;
		}
		Transform2D::loadIdentityMatrix();
		Transform2D::translateMatrix(-this->opponent4x, -this->opponent4y + 7.5);
		Transform2D::rotateMatrix(this->angle4);
		Transform2D::translateMatrix(this->opponent4x, this->opponent4y - 7.5);
		Transform2D::translateMatrix(this->step4x * direction4, this->step4y *direction4);
		Transform2D::applyTransform_o(star1);
		Transform2D::applyTransform_o(star2);

		this->opponent4x += this->step4x * direction4;
		this->opponent4y += this->step4y *direction4;

	}

	void Opponents::addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context) {
		DrawingWindow::addObject2D_to_Visual2D(opponent, context);
	}

	bool Opponents::changeDirection(float x, float y){
		
		if(x>= 955)
			return true;
		if(x<= 25)
			return true;
		if(y >= 480)
			return true;
		if(y <= 40)
			return true;
		return false;

	}
