#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Opponents.h"
#include "Collisions.h"
#include <iostream>
#include <windows.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

using namespace std;

//doua contexte 
Visual2D *infos, *gameArea;

//jucator unu

//format din cerc si un poligon
Polygon2D *polygon;
Circle2D *circle;

//arma jucatorului
Polygon2D *weapon;

//coordonatele cu care se translateaza pe x si pe y
float translationX;
float translationY;

bool weaponOn;
bool slowDown;

float step = 0;
float rotationAngle = 0;

int killed = 0;
int previousLives = 0;

//scor si nr puncte
Text *score;
Text *points;
int nrScore = 0;

std::vector <Opponents*> opponents;

//oponent 1(reprezentat prin doua patrate)
float opponent1X;
float opponent1Y;

//oponent 2(reprezentat prin doua triunghiuri)
float opponent2X;
float opponent2Y;

//oponent 3(reprezentat prin patrat si romb in interior)
float opponent3X;
float opponent3Y;

//oponent 4(reprezentat prin doua triunghiuri in forma de stea)
float opponent4X;
float opponent4Y;

int time = 0;
bool addedNew = false;


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

	weapon = new Polygon2D(Color(1, 0.5, 0), true);
	weapon->addPoint(Point2D(x + 40, y + 15));
	weapon->addPoint(Point2D(x + 105, y));
	weapon->addPoint(Point2D(x + 40, y - 15));
}

//functia pentru numarul de vieti
//initial, jucatorul are 3 vieti
//in momentul in care jucatorul pierde o viata, in dreapta sus apare cate o cruce
void lives(int killed, int previousLives, Visual2D *context){

	if(previousLives < killed && killed <= 3) {
		
		for(int i = previousLives; i < killed; i++){

			Line2D *line1;
			Rectangle2D *cross11;
			Rectangle2D *cross12;

			cross11 = new Rectangle2D(Point2D(960 - 40 * i, 35), 30, 10, Color(0.333333, 0.333333, 0.333333), true);
			cross12 = new Rectangle2D(Point2D(970 - 40 * i, 25), 10, 30, Color(0.333333, 0.333333, 0.333333), true);
			line1 = new Line2D(Point2D(960 - 40 * i, 25), Point2D(990 - 40 * i, 25), Color(0.333333, 0.333333, 0.333333));

			DrawingWindow::addObject2D_to_Visual2D(line1, infos);
			DrawingWindow::addObject2D_to_Visual2D(cross11, infos);
			DrawingWindow::addObject2D_to_Visual2D(cross12, infos);
		}
	}
}

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{

	//conetxt pentru informatii legate de scor si numarul de vieti ramase
  
	infos = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height / 8, 0, 0, 
						 DrawingWindow::width, DrawingWindow::height / 8);
	addVisual2D(infos);
	infos->tipTran(true);

	//adaugare text "SCORE"
	score = new Text("SCORE", Point2D(450, 40), Color(0, 1, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(score, infos);

	//adaugare nr de puncte
	points = new Text("0", Point2D(450, 20), Color(0, 1, 0), BITMAP_HELVETICA_18);
	addText_to_Visual2D(points, infos);

	//context pentru suprafata de joc
	gameArea = new Visual2D(0, 0, DrawingWindow::width, DrawingWindow::height, 0, DrawingWindow::height / 8, 
							DrawingWindow::width, DrawingWindow::height);
	gameArea->tipTran(true);
	addVisual2D(gameArea);

	//desenare jucator
	translationX = 500;
	translationY = 300;
	playerOne(500, 300);
	addObject2D_to_Visual2D(circle, gameArea);
	addObject2D_to_Visual2D(polygon, gameArea);

	//initializare arma
	showWeapon(500, 300);

	//coordonate oponenti

	//oponent 1
	opponent1X = 300;
	opponent1Y = 100;

	//oponent 2
	opponent2X = 200;
	opponent2Y = 300;

	//oponent 3;
	opponent3X = 200;
	opponent3Y = 420;

	//oponent 4
	opponent4X = 700;
	opponent4Y = 100;

}


//functia care permite animatia
void DrawingWindow::onIdle()
{
	time++;

	if(time == 100 || time % 400 == 0) {
		
		//resetez timpul la fiecare 1000 de frameuri
		if(time == 1000)
			time  = 0;

		//adaug pe ecran cate un tip din fiecare oponent la fiecare 400 de frame-uri
		Opponents *op = new Opponents();
		opponents.push_back(op);

		opponents[opponents.size() - 1]->opponent1(opponent1X, opponent1Y, gameArea);
		opponents[opponents.size() - 1]->opponent2(opponent2X, opponent2Y, gameArea);
		opponents[opponents.size() - 1]->opponent3(opponent3X, opponent3Y, gameArea);
		opponents[opponents.size() - 1]->opponent4(opponent4X, opponent4Y, gameArea);

		addedNew = true;
	}

	if(addedNew) {

		for(int i = 0; i < opponents.size(); i++){

			opponents[i]->moveOpponent1();
			opponents[i]->moveOpponent2();
			opponents[i]->moveOpponent3();
			opponents[i]->moveOpponent4();
			
			//dupa fiecare miscare a oponentilos, verific daca se produce vreo coliziune

			Collisions *collissions = new Collisions();
			
			//daca jucatorul are arma activata, pot verifica daca omoara vreun inamic
			if(weaponOn) {
				
				//functia killOpponent returneaza scorul aferent in cazul in care un inamic a fost omorat si 0 altfel
				nrScore += collissions->killOpponent(opponents[i], weapon);

				//actualizez scorul
				removeText_from_Visual2D(points, infos);
				points = NULL;
				char nrPoints[100];
				points = new Text(itoa(nrScore, nrPoints, 10), Point2D(450, 20), Color(0, 1, 0), BITMAP_HELVETICA_18);
				addText_to_Visual2D(points, infos);
			}

			//indiferent daca jucatorul are sau nu arma activata, verific daca un oponent l-a atins
			//functia killPlayer intoarce numarul de oponenti care au atins jucatorul la un moment de timp
			killed += collissions->killPlayer(opponents[i], new Point2D(translationX, translationY));
			
			//daca variabila isi schimba valoarea, jucatorul a pierdut o viata, pe ecran apare o cruce
			if(killed != previousLives) {
				lives(killed, previousLives, gameArea);
				previousLives = killed;
			}
			

			//cand jucatorul pierde trei vieti, jocul se termina
			if(killed >= 3){

				//textul GAME OVER va aparea pe ecran
				Text *gameOver;
				gameOver = new Text("GAME OVER", Point2D(450, 300), Color(1, 0, 1), BITMAP_HELVETICA_18);
				addText_to_Visual2D(gameOver, gameArea);

				//jucatorul unu dispare de pe ecran
				removeObject2D_from_Visual2D(polygon, gameArea);
				removeObject2D_from_Visual2D(circle, gameArea);
				if(weapon)
					removeObject2D_from_Visual2D(weapon, gameArea);
			}
			
		}
	}

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	infos->poarta(0, 0, width, height / 8); 
	gameArea->poarta(0, 0, width, height);
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case 27 : exit(0);

		case KEY_UP : 

			//deplasare pe directia indicata de jucator
			//daca arma este activata, viteza de deplasare este mai mica
			if(slowDown) {
				//daca se ajunge la marginea contextului de vizualizare, jucatorul nu mai poate inainta
				//trebuie sa schimbe directia
				if((translationX + step * cos(rotationAngle) <= 895 &&
				   translationX + step * cos(rotationAngle) >= 100) &&
				   (translationY + step * sin(rotationAngle) <= 420 &&
				   translationY + step * sin(rotationAngle) >= 100)) {
						translationX += step * cos(rotationAngle);
						translationY += step * sin(rotationAngle);
						Transform2D::loadIdentityMatrix();
						Transform2D::translateMatrix(-500, -300);
						Transform2D::rotateMatrix(rotationAngle);
						Transform2D::translateMatrix(translationX, translationY);
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
				if((translationX + step * cos(rotationAngle) <= 895 &&
				   translationX + step * cos(rotationAngle) >= 100) &&
				   (translationY + step * sin(rotationAngle) <= 420 &&
				   translationY + step * sin(rotationAngle) >= 100)) {
						translationX += step * cos(rotationAngle);
						translationY += step * sin(rotationAngle);
						Transform2D::loadIdentityMatrix();
						Transform2D::translateMatrix(-500, -300);
						Transform2D::rotateMatrix(rotationAngle);
						Transform2D::translateMatrix(translationX, translationY);
						Transform2D::applyTransform(polygon);
						Transform2D::applyTransform(circle);
						Transform2D::applyTransform(weapon);
						step += 0.5;
				}
			}
			break;

		case KEY_SPACE : 

			//se activeaza sau se dezactiveaza arma
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
			
			//rotatie la stanga
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-500, -300);
			rotationAngle += 0.1;
			Transform2D::rotateMatrix(rotationAngle);
			Transform2D::translateMatrix(translationX, translationY);
			Transform2D::applyTransform(polygon);
			Transform2D::applyTransform(circle);
			Transform2D::applyTransform(weapon);
			break;

		case KEY_RIGHT :

			//rotatie la dreapta
			Transform2D::loadIdentityMatrix();
			Transform2D::translateMatrix(-500, -300);
			rotationAngle -= 0.1;
			Transform2D::rotateMatrix(rotationAngle);
			Transform2D::translateMatrix(translationX, translationY);
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