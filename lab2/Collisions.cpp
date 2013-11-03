#include "Collisions.h"

using namespace std;

Collisions::Collisions(){

	//variabile care determina daca au fost sau nu create dreptunghiuri imaginare
	this->opponent1 = true;
	this->opponent2 = true;
	this->opponent3 = true;
	this->opponent4 = true;
}

//functie care creeaza un dreptungi imaginar in jurul fiecarui oponent
void Collisions::createImaginaryRectangles(Opponents *opponents){
	
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

//functie care determina daca arma jucatorului omoara vreun oponent
int Collisions::killOpponent(Opponents *opponents, Polygon2D *weapon){

	int returnValue = 0;
	//creez dreptunghiuri imaginare pentru oponenti
	createImaginaryRectangles(opponents);
	
	//daca exista un dreptunghi imaginar in jurul oponentului X
	if(this->opponent1) {

		//verific daca cele doua se intersecteaza
		if(intersected(weapon, this->imgOpponent1)){

			//daca da, omor oponentul
			DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO1, opponents->context);
			DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO2, opponents->context);

			delete opponents->squareO1;
			opponents->squareO1 = NULL;
			delete opponents->squareO2;
			opponents->squareO2 = NULL;

			//si actualizez scorul
			returnValue += 10;
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

			returnValue += 20;
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

			returnValue += 30; 
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

			returnValue += 40;
		}
	}
	return returnValue;
}

//functie care verifica daca doua linii, reprezentate prin doua puncte, se intersecteaza
bool Collisions::lineIntersection(Point2D *p1, Point2D *p2, Point2D *t1, Point2D *t2){
	
	float diff1x, diff1y, diff2x, diff2y;

	//calculez diferenta pe x si pe y intre puntele ce reprezinta capetele segmentelor
    diff1x = p2->x - p1->x;     
	diff1y = p2->y - p1->y;
    diff2x = t2->x - t1->x;
	diff2y = t2->y - t1->y;

    float ua, ub;
	ua = (-diff1y * (p1->x - t1->x) + diff1x * (p1->y - t1->y)) / (-diff2x * diff1y + diff1x * diff2y);
	ub = (diff2x * (p1->y - t1->y) - diff2y * (p1->x - t1->x)) / (-diff2x * diff1y + diff1x * diff2y);

    if (ua >= 0  && ua <= 1 && ub >= 0 &&  ub <= 1)
			return true;
	else 
		return false;
}

//pe baza functiei lineIntersection, iau la rand fiecare linie a dreptungiului imaginar in care sunt incadrati oponetii
//si verific daca se intersecteaza cu una din cele doua linii ale armei
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

//functie care verifica daca o linie si un cerc se intersecteaza
//linia este reprezentata prin doua puncte, cercul prin centrul sau
bool Collisions::lineCircleIntersection(Point2D *p1, Point2D *p2, Point2D *center) {
	
	//diferenta pe x intre capetele dreptei
	float x = p2->x - p1->x;

	//diferenta pe y intre capetele dreptei
    float y = p2->y - p1->y;

	//diferenta intre un capat al dreptei si centrul cercului
    float diffx = p1->x - center->x;
    float diffy = p1->y - center->y;

    float a = pow(x, 2) + pow(y, 2);
    float b = 2 * ((x * diffx) + (y * diffy));

	//25 = raza cercului
    float c = pow(diffx, 2) + pow(diffy, 2) - pow(25, 2);
    float delta = pow(b, 2) - (4 * a * c);

    if (delta >= 0){
        
		//linia poate intersecta cercul
		//verific daca puntrul de intersectie se afla intre cele doua capete ale dreptei
        float rad=sqrt(delta);

        // calculez puctele de intersectie
        float m = (-1 * -b + rad) / (2 * a);
        float x1 = p1->x + (-1 * x * m);
        float y1 = p1->y + (-1 * y * m);

		// verific daca punctul de intersectie se afla pe dreapta
        if (x1 >= min(p1->x, p2->x) && x1 <= max(p1->x, p2->x) && y1 >= min(p1->y, p2->y) && y1 <= max(p1->y, p2->y)){
			return true;
		}

		m = (1 * -b + rad) / (2 * a);
        x1 = p1->x + (1 * x * m);
        y1 = p1->y + (1 * y * m);

        // verific daca punctul de intersectie se afla pe dreapta
        if (x1 >= min(p1->x, p2->x) && x1 <= max(p1->x, p2->x) && y1 >= min(p1->y, p2->y) && y1 <= max(p1->y, p2->y)){
			return true;
		}
    }
    return false;
}


//functie care determina daca jucatorul a fost atins de un oponent
int Collisions::killPlayer(Opponents *opponents, Point2D *center){

	createImaginaryRectangles(opponents);
	int m, n = 0;
	int dead = 0;

	//pentru fiecare oponent, pentru fiecare din cele patru laturi ale dreptunghiului imaginar, verific daca 
	//se intersecteaza cu cercul care inconjoara oponentul
	//daca da, oponentul moare si jucatorul pierde o viata
	for(int i = 0; i < 4; i++){

		if(i == 3){
			m = 3;
			n = 0;
		}
		else {
			m = i;
			n = i+1;
		} 

		if(this->opponent1){

			if(lineCircleIntersection(this->imgOpponent1->transf_points[m], this->imgOpponent1->transf_points[n], center)){

				dead += 1;

				DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO1, opponents->context);
				DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO2, opponents->context);

				delete opponents->squareO1;
				opponents->squareO1 = NULL;
				delete opponents->squareO2;
				opponents->squareO2 = NULL;

				this->opponent1 = false;
				
			}
		}
		if(this->opponent2){

			if(lineCircleIntersection(this->imgOpponent2->transf_points[m], this->imgOpponent2->transf_points[n], center)){

				dead += 1;

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

				this->opponent2 = false;
			}
		}
		if(this->opponent3){

			if(lineCircleIntersection(this->imgOpponent3->transf_points[m], this->imgOpponent3->transf_points[n], center)){

				dead += 1;

				DrawingWindow::removeObject2D_from_Visual2D(opponents->rhombO, opponents->context);
				DrawingWindow::removeObject2D_from_Visual2D(opponents->squareO, opponents->context);

				delete opponents->rhombO;
				opponents->rhombO = NULL;
				delete opponents->squareO;
				opponents->squareO = NULL;

				this->opponent3 = false;
			}
		}
		if(this->opponent4){

			if(lineCircleIntersection(this->imgOpponent4->transf_points[m], this->imgOpponent4->transf_points[n], center)){

				dead += 1;

				DrawingWindow::removeObject2D_from_Visual2D(opponents->starO1, opponents->context);
				DrawingWindow::removeObject2D_from_Visual2D(opponents->starO2, opponents->context);

				delete opponents->starO1;
				opponents->starO1 = NULL;
				delete opponents->starO2;
				opponents->starO2 = NULL;

				this->opponent4 = false;
			}
		}
	}

	return dead;
}