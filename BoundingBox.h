#pragma once

//Axis-aligned bounding box
class BoundingBox
{
public:
	BoundingBox(void);
	BoundingBox(int x1, int y1, int x2, int y2);
	//BoundingBox(float x1, float y1, float x2, float y2);
	void setUPos(float x1, float y1, float x2, float y2);
	bool containsPoint(double x, double y);

	//bool collides()

	float fx1, fy1, fx2, fy2;

	int x1;
	int y1;
	int x2;
	int y2;

	~BoundingBox(void);
private:


	bool transport;
	int leadsTo;

	
};

