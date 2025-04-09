#pragma once
#define CARS_LIMIT 5
#include "base_car.h"

class World
{
protected:
	CarBody* cars[CARS_LIMIT];
	int total_cars = 0;
public:
	int add_car(CarBody* car);
	int check_car_bump(CarBody *car);
	void findndelete(CarBody* car);
	void make_explode(int x1, int y1, int x2, int y2);
};