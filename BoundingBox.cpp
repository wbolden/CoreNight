#include "BoundingBox.h"


BoundingBox::BoundingBox(void)
{

}

BoundingBox::BoundingBox(int x1, int y1, int x2, int y2)
{
	this->y1 = y1;
	this->y2 = y2;
	this->x1 = x1;
	this->x2 = x2;
}

void BoundingBox::setUPos(float x1, float y1, float x2, float y2)
{
	this->fy1 = y1;
	this->fy2 = y2;
	this->fx1 = x1;
	this->fx2 = x2;
}
	
bool BoundingBox::containsPoint(double x, double y)
{
	return (((x1 < x) && (x < x2)) || ((x1 > x) && (x > x2))) && (((y2 < y) && (y < y1)) || ((y2 > y) && (y > y1)));
}


BoundingBox::~BoundingBox(void)
{
}
