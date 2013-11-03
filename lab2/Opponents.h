//implementarea clasei pentru oponenti
#pragma once
#include "Framework/Polygon2D.h"
#include "Framework/Visual2D.h"
#include "Framework/DrawingWindow.h"
#include "Framework/Rectangle2d.h"
#include "Framework/Transform2D.h"
#include "Framework/Circle2D.h"

using namespace std;

class Opponents {

public:

	Visual2D *context;

	float opponent1x;
	float opponent1y;
	Polygon2D *squareO1;
	Polygon2D *squareO2;
	float step1x;
	float step1y;
	float direction1;

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
	float direction3;

	float opponent4x;
	float opponent4y;
	Polygon2D *starO1;
	Polygon2D *starO2;
	float step4x;
	float step4y;
	float angle4;
	float direction4;

public:

	Opponents::Opponents();

	void opponent1(float x, float y, Visual2D *context);
	void opponent2(float x, float y, Visual2D *context);
	void opponent3(float x, float y, Visual2D *context);
	void opponent4(float x, float y, Visual2D *context);

	void moveOpponent1();
	void moveOpponent2();
	void moveOpponent3();
	void moveOpponent4();

	void addOpponent_to_Visual2D(Object2D *opponent, Visual2D *context);
	bool changeDirection(float x, float y);

};