//implementarea clasei pentru oponenti
#include "Opponents.h"

using namespace std;

	float opponent1x;
	float opponent1y;
	Polygon2D *squareO1;
	Polygon2D *squareO2;
	float step1x = 0;
	float step1y = 0;

	float opponent2x;
	float opponent2y;
	Polygon2D *triangleO1;
	Polygon2D *triangleO2;
	Polygon2D *triangleO3;
	Polygon2D *triangleO4;
	float step2x;
	float step2y;
	float angle2;

	float opponent3x;
	float opponent3y;
	Polygon2D *squareO;
	Polygon2D *rhombO;
	float step3x;
	float step3y;

	float opponent4x;
	float opponent4y;
	Polygon2D *starO1;
	Polygon2D *starO2;
	float step4x;
	float step4y;
	float angle4;
	
	Opponents::Opponents(){
		
		//initializare forme geometrice pentru cele patru tipuri de oponenti
		this->squareO1 = new Polygon2D(Color(0.5, 0, 0.5), false);
		this->squareO2 = new Polygon2D(Color(0.5, 0, 0.5), false);
		this->direction1 = 1.0;

		this->triangleO1 = new Polygon2D(Color(1, 0, 0), false);
		this->triangleO2 = new Polygon2D(Color(1, 0, 0), false);
		this->triangleO3 = new Polygon2D(Color(1, 1, 0), true);
		this->triangleO4 = new Polygon2D(Color(1, 1, 0), true);

		this->squareO = new Polygon2D(Color(0, 1, 0), false);
		this->rhombO = new Polygon2D(Color(0, 1, 0), false);
		this->direction3 = 1.0;

		this->starO1 = new Polygon2D(Color(0, 0, 1), false);
		this->starO2 = new Polygon2D(Color(0, 0, 1), false);
		this->direction4 = 1.0;
		this->angle2 = 0;
		this->angle4 = 0;
		
	}

	void Opponents::opponent1(float x, float y, Visual2D *context){

		//adaugare oponent de tip 1 pe ecran
		this->context = context;

		this->opponent1x = x;
		this->opponent1y = y;

		this->step1x = 1;
		this->step1y = 1;

		this->squareO1->addPoint(Point2D(x, y));
		this->squareO1->addPoint(Point2D(x + 20, y));
		this->squareO1->addPoint(Point2D(x + 20, y - 20));
		this->squareO1->addPoint(Point2D(x, y - 20));

		this->squareO2->addPoint(Point2D(x + 10, y - 10));
		this->squareO2->addPoint(Point2D(x + 30, y - 10));
		this->squareO2->addPoint(Point2D(x + 30, y - 30));
		this->squareO2->addPoint(Point2D(x + 10, y - 30));

		addOpponent_to_Visual2D(this->squareO1, context);
		addOpponent_to_Visual2D(this->squareO2, context);

	}

	//functia care realizeaza miscarea pentru primul tip de oponenti
	void Opponents::moveOpponent1() {
		
		//daca oponentul nu a fost omorat
		if(this->squareO1 != NULL && this->squareO2 != NULL){

			Transform2D::loadIdentityMatrix();

			//in cazul in care oponentul se loveste de un zid, se schimba directia
			if(changeDirection(this->opponent1x, this->opponent1y)) {
				direction1 *= -1;

				this->step1x = (rand() % 10) / 5;
				this->step1y = (rand() % 10) / 3; 
				
			}

			this->opponent1x += this->step1x * direction1;
			this->opponent1y += this->step1y * direction1;

			//oponentul se translateaza cu un pas random
			Transform2D::translateMatrix(this->step1x * direction1, this->step1y * direction1);
			Transform2D::applyTransform_o(this->squareO1);
			Transform2D::applyTransform_o(this->squareO2);
		}
	}

	void Opponents::opponent2(float x, float y, Visual2D *context){

		//initializare si adaugare pe ecran a oponentului 2
		this->opponent2x = x;
		this->opponent2y = y;

		this->step2x = 1.5;
		this->step2y = 1.5;
		this->angle2 = 0;

		this->triangleO1->addPoint(Point2D(x, y));
		this->triangleO1->addPoint(Point2D(x + 30, y));
		this->triangleO1->addPoint(Point2D(x - 10, y + 20));

		this->triangleO2->addPoint(Point2D(x, y));
		this->triangleO2->addPoint(Point2D(x + 30, y));
		this->triangleO2->addPoint(Point2D(x - 10, y - 20));

		this->triangleO3->addPoint(Point2D(x, y));
		this->triangleO3->addPoint(Point2D(x + 30, y));
		this->triangleO3->addPoint(Point2D(x - 10, y + 20));

		this->triangleO4->addPoint(Point2D(x, y));
		this->triangleO4->addPoint(Point2D(x + 30, y));
		this->triangleO4->addPoint(Point2D(x - 10, y - 20));

		addOpponent_to_Visual2D(this->triangleO1, context);
		addOpponent_to_Visual2D(this->triangleO2, context);
		addOpponent_to_Visual2D(this->triangleO3, context);
		addOpponent_to_Visual2D(this->triangleO4, context);

	}


	//functie care realizeaza miscarea oponentului 2
	void Opponents::moveOpponent2(){

		if(this->triangleO1 != NULL && this->triangleO2 != NULL && this->triangleO3 != NULL && this->triangleO4 != NULL) {

			Transform2D::loadIdentityMatrix();
			//cand schimba directia, oponentul de tipul 2 se roteste mereu la 135 grade
			//si se deplaseaza pe directia respectiva cu pas constant
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
			Transform2D::applyTransform_o(this->triangleO1);
			Transform2D::applyTransform_o(this->triangleO2);
			Transform2D::applyTransform_o(this->triangleO3);
			Transform2D::applyTransform_o(this->triangleO4);
		}

	}

	void Opponents::opponent3(float x, float y, Visual2D *context){

		//initializare si adaugate pe ecran oponent de tip3
		this->opponent3x = x;
		this->opponent3y = y;

		this->step3x = 1;
		this->step3y = 1;

		this->squareO->addPoint(Point2D(x, y));
		this->squareO->addPoint(Point2D(x + 30, y));
		this->squareO->addPoint(Point2D(x + 30, y + 30));
		this->squareO->addPoint(Point2D(x, y + 30));
		
		this->rhombO->addPoint(Point2D(x, y + 15));
		this->rhombO->addPoint(Point2D(x + 15, y));
		this->rhombO->addPoint(Point2D(x + 30, y + 15));
		this->rhombO->addPoint(Point2D(x + 15, y + 30));

		addOpponent_to_Visual2D(this->squareO, context);
		addOpponent_to_Visual2D(this->rhombO, context);

	}

	//miscarea pentru oponentul de tip 3
	void Opponents::moveOpponent3(){
		
		//ca si oponentul de tipul 1, se translateaza cu pasi random
		if(this->squareO != NULL && this->rhombO != NULL){

			Transform2D::loadIdentityMatrix();

			if(changeDirection(this->opponent3x, this->opponent3y)) {
				direction3 *= -1;
				this->step3x = (rand() % 10) / 2;
				this->step3y = (rand() % 10) / 5;
			}

			this->opponent3x += this->step3x * direction3;
			this->opponent3y += this->step3y * direction3;

			Transform2D::translateMatrix(this->step3x * direction3, this->step3y * direction3);
			Transform2D::applyTransform_o(this->squareO);
			Transform2D::applyTransform_o(this->rhombO);
		}
	}

	void Opponents::opponent4(float x, float y, Visual2D *context){

		//initializare oponent de tipul 4 si afisare pe ecran
		this->opponent4x = x;
		this->opponent4y = y;

		this->step4x = 1;
		this->step4y = 1;

		this->angle4 = 0.05;

		this->starO1->addPoint(Point2D(x, y + 10));
		this->starO1->addPoint(Point2D(x + 15, y - 15));
		this->starO1->addPoint(Point2D(x - 15, y - 15));

		this->starO2->addPoint(Point2D(x - 15, y));
		this->starO2->addPoint(Point2D(x + 15, y));
		this->starO2->addPoint(Point2D(x, y - 25));

		addOpponent_to_Visual2D(this->starO1, context);
		addOpponent_to_Visual2D(this->starO2, context);

	}
	
	//miscarea pentru oponentul de tip 4
	void Opponents::moveOpponent4() {

		//se realizeaza translatie si rotatie in jurul centrului propriu
		//cu cat se deplaseaza mai mult, viteza de rotatie creste
		if(this->starO1 != NULL && this->starO2 != NULL){

			Transform2D::loadIdentityMatrix();

			if(changeDirection(this->opponent4x, this->opponent4y)) {
				direction4 *= -1;
				this->step4x = (rand() % 10) / 4;
				this->step4y = (rand() % 10) / 3;
				this->angle4 += 0.01;
			}

			Transform2D::translateMatrix(-this->opponent4x, -this->opponent4y + 7.5);
			Transform2D::rotateMatrix(this->angle4);
			Transform2D::translateMatrix(this->opponent4x, this->opponent4y - 7.5);
			Transform2D::translateMatrix(this->step4x * direction4, this->step4y *direction4);
			Transform2D::applyTransform_o(this->starO1);
			Transform2D::applyTransform_o(this->starO2);

			this->opponent4x += this->step4x * direction4;
			this->opponent4y += this->step4y *direction4;
		}

	}

	void Opponents::addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context) {
		DrawingWindow::addObject2D_to_Visual2D(opponent, context);
	}

	//frunctie care determina, pentru doua puncte, reprezentand coordonate reprezentand un punct al oponentului,
	//daca trebuie schimbata directia de deplasare a oponentului
	bool Opponents::changeDirection(float x, float y){
		
		if(x >= 955)
			return true;
		if(x<= 25)
			return true;
		if(y >= 480)
			return true;
		if(y <= 40)
			return true;
		return false;

	}
