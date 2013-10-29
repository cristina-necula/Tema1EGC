#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Opponents.h"
#include <iostream>
#include <windows.h>

#define PI 3.14159265358979323846

using namespace std;

//doua contexte
Visual2D *infos, *gameArea;

//jucator unu
Polygon2D *polygon;
Circle2D *circle;
Polygon2D *weapon;
float rotationX;
float rotationY;
bool weaponOn;
bool slowDown;
float step = 0;
float angle = 0;
float rotationAngle = 0;

//scor si nr puncte
Text *score;
Text *points;
Text *lives;

//oponent 1(reprezentat prin doua patrate)
Polygon2D *square1;
Polygon2D *square2;
float opponent1X;
float opponent1Y;

//oponent 2(reprezentat prin doua triunghiuri)
Polygon2D *triangle1;
Polygon2D *triangle2;
Polygon2D *triangle3;
Polygon2D *triangle4;
float opponent2X;
float opponent2Y;

//oponent 3(reprezentat prin patrat si romb in interior)
Rectangle2D *square3;
Polygon2D *rhomb;
float opponent3X;
float opponent3Y;

//oponent 4(reprezentat prin doua triunghiuri in forma de stea)
Polygon2D *star1;
Polygon2D *star2;
float opponent4X;
float opponent4Y;

float step1, u1;

void timeSleep(){

}

//functia care deseneaza jucatorul
void playerOne(float x, float y){
	
	//jucator
	circle = new Circle2D(Point2D(x, y), 25, Color(1, 0.5, 0), false);

	polygon = new Polygon2D(Color(1, 0.5, 0), false);

	polygon->addPoint(Point2D(x - 20, y));
	polygon->addPoint(Point2D(x, y + 20));
	polygon->addPoint(Point2D(x + 20, y + 10));
	polygon->addPoint(Point2D(x, y + 18));
	polygon->addPoint(Point2D(x - 10, y));
	polygon->addPoint(Point2D(x ,y - 18));
	polygon->addPoint(Point2D(x + 20, y - 10));
	polygon->addPoint(Point2D(x, y - 20));

}

//functia pentru arma jucatorului
void showWeapon(int x, int y){
	//arma
	weapon = new Polygon2D(Color(1, 0.5, 0), true);
	weapon->addPoint(Point2D(x + 40, y + 15));
	weapon->addPoint(Point2D(x + 105, y));
	weapon->addPoint(Point2D(x + 40, y - 15));
}

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	//conetxt pentru informatii legate de scor si numarul de vieti ramase
	//infos = new Visual2D(0,0,DrawingWindow::width,DrawingWindow::height,0,0,DrawingWindow::width,DrawingWindow::height);  
	infos = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height / 8, 0, 0, 
		DrawingWindow::width, DrawingWindow::height / 8);
	infos->tipTran(true);
	addVisual2D(infos);

	//adaugare text "SCORE"
	score = new Text("SCORE", Point2D(450, 40), Color(0, 1, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(score, infos);

	//adaugare nr de puncte
	points = new Text("12345", Point2D(450, 20), Color(0, 1, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(points, infos);

	//adaugare numar de vieti
	lives = new Text("3 X ", Point2D(800, 30), Color(1, 0.5, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(lives, infos);

	//context pentru suprafata de joc
	gameArea = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, DrawingWindow::height / 8, 
		DrawingWindow::width, DrawingWindow::height);
	gameArea->tipTran(true);
	addVisual2D(gameArea);
	//desenare jucator
	rotationX = 500;
	rotationY = 300;
	playerOne(500, 300);
	addObject2D_to_Visual2D(circle, gameArea);
	addObject2D_to_Visual2D(polygon, gameArea);

	//adaugare imagine jucator pentru numarul de vieti
	

	//initializare arma
	showWeapon(500, 300);

	//incep sa adaug oponenti
	Opponents opponents;

	//adaug oponent 1
	square1 = new Polygon2D(Color(0.5, 0, 0.5), false);
	square2 = new Polygon2D(Color(0.5, 0, 0.5), false);
	opponent1X = 300;
	opponent1Y = 100;

	//adaug oponent 2
	triangle1 = new Polygon2D(Color(1, 0, 0), false);
	triangle2 = new Polygon2D(Color(1, 0, 0), false);
	triangle3 = new Polygon2D(Color(1, 1, 0), true);
	triangle4 = new Polygon2D(Color(1, 1, 0), true);
	opponent2X = 200;
	opponent2Y = 300;

	//adaug oponent 3;
	opponent3X = 200;
	opponent3Y = 500;
	square3 = new Rectangle2D(Point2D(opponent3X, opponent3Y), 30, 30, Color(0, 1, 0), false);
	rhomb = new Polygon2D(Color(0, 1, 0), false);

	//adaug oponent 4
	opponent4X = 700;
	opponent4Y = 100;
	star1 = new Polygon2D(Color(0, 0, 1), false);
	star2 = new Polygon2D(Color(0, 0, 1), false);

	opponents.opponent1(opponent1X, opponent1Y, square1, square2, gameArea);
	opponents.opponent2(opponent2X, opponent2Y, triangle1, triangle2, triangle3, triangle4, gameArea);
	opponents.opponent3(opponent3X, opponent3Y, square3, rhomb, gameArea);
	opponents.opponent4(opponent4X, opponent4Y, star1, star2, gameArea);

	Transform2D::loadIdentityMatrix();
}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	step1 = 0.1;
	u1 = 0.1;
	//Transform2D::translateMatrix(u1 * cos(step1), u1 * cos(step1));
	//Transform2D::applyTransform(square1);
	//Transform2D::applyTransform(square2);
	step1 += 0.1;
	u1 += 0.1;
}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	infos->poarta(0, 0,width,height / 8); 
	gameArea->poarta(0, 0, width, height);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case 27 : exit(0);

		case KEY_UP : 

			//daca arma este activata, viteza de deplasare este mai mica
			if(slowDown) {
				//daca se ajunge la marginea contextului de vizualizare, jucatorul nu mai poate inainta
				//trebuie sa schimbe directia
				if((rotationX + step * cos(rotationAngle) <= 895 &&
				   rotationX + step * cos(rotationAngle) >= 105) &&
				   (rotationY + step * sin(rotationAngle) <= 420 &&
				   rotationY + step * sin(rotationAngle) >= 105)) {
						rotationX += step * cos(rotationAngle);
						rotationY += step * sin(rotationAngle);
						Transform2D::translateMatrix(step * cos(rotationAngle), step * sin(rotationAngle));
						Transform2D::applyTransform(polygon);
						Transform2D::applyTransform(circle);
						Transform2D::applyTransform(weapon);
						step += 0.1;
				}
			}
			//viteza de deplasare mare, arma nu este activata
			else {
				//daca se ajunge la marginea contextului de vizualizare, jucatorul nu mai poate inainta
				//trebuie sa schimbe directia
				if((rotationX + step * cos(rotationAngle) <= 895 &&
				   rotationX + step * cos(rotationAngle) >= 105) &&
				   (rotationY + step * sin(rotationAngle) <= 420 &&
				   rotationY + step * sin(rotationAngle) >= 105)) {
						rotationX += step * cos(rotationAngle);
						rotationY += step * sin(rotationAngle);
						Transform2D::translateMatrix(step * cos(rotationAngle), step * sin(rotationAngle));
						Transform2D::applyTransform(polygon);
						Transform2D::applyTransform(circle);
						Transform2D::applyTransform(weapon);
						step += 0.5;
				}
			}
			break;

		case KEY_SPACE : 

			if(weaponOn) {
				removeObject2D_from_Visual2D(weapon, gameArea);
				weaponOn = false;
				slowDown = false;
			}
			else {
				addObject2D_to_Visual2D(weapon, gameArea);
				weaponOn = true;
				slowDown = true;
			}
			break;

		case KEY_LEFT :

			Transform2D::translateMatrix(-rotationX, -rotationY);
			angle = 0.1;
			rotationAngle += 0.1;
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(rotationX, rotationY);
			Transform2D::applyTransform(polygon);
			Transform2D::applyTransform(circle);
			Transform2D::applyTransform(weapon);
			break;

		case KEY_RIGHT :

			Transform2D::translateMatrix(-rotationX, -rotationY);
			angle = -0.1;
			rotationAngle -= 0.1;
			Transform2D::rotateMatrix(angle);
			Transform2D::translateMatrix(rotationX, rotationY);
			Transform2D::applyTransform(polygon);
			Transform2D::applyTransform(circle);
			Transform2D::applyTransform(weapon);
			break;
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 1000, 600, 200, 100, "Geometry Wars");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}