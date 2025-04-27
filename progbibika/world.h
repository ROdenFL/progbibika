#pragma once
#define OBJECTS_LIMIT 6
#include "base_figures.h"

class World
{
protected:
	BumpObject* objects[OBJECTS_LIMIT];
	int total_objects = 0;
public:
	int add_object(BumpObject* newObject);
	void check_bump(BumpObject* bumpObject);
	void findndelete(BumpObject* bumpObject);
	void make_explode(int x1, int y1, int x2, int y2);
};