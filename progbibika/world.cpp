#include "world.h"
#include <algorithm>
using namespace std;

extern HDC hdc;

int World::add_car(CarBody* car)
{
	if (total_cars >= CARS_LIMIT)
	{
		return 3; //слишком много машин
	}
	cars[total_cars++] = car;
	car->SetWorld(this);
	return 0;
}

int World::check_car_bump(CarBody* mainCar)
{
	CarBody* currentCar;
	CarBody* carCrush = NULL;
	for (int i = 0; i < total_cars; i++)
	{
		currentCar = cars[i];
		if (currentCar == mainCar)	continue;

		int left	=	max(mainCar->GetX(), currentCar->GetX());
		int right	=	min(mainCar->GetX() + mainCar->GetWidth(), currentCar->GetX() + currentCar->GetWidth());
		int bottom = max(mainCar->GetY(), currentCar->GetY());
		int top = min(mainCar->GetY() + mainCar->GetHeight(), currentCar->GetY() + currentCar->GetHeight());

		int width = right - left;
		int height = top - bottom;

		if (width < 0 || height < 0)
			continue;
		
		carCrush = currentCar;
		break;
	}
	
	if (!carCrush)
		return 0;

	int left = min(mainCar->GetX(), carCrush->GetX());
	int right = max(mainCar->GetX() + mainCar->GetWidth(), carCrush->GetX() + carCrush->GetWidth());
	int bottom = min(mainCar->GetY(), carCrush->GetY());
	int top = max(mainCar->GetY() + mainCar->GetHeight(), carCrush->GetY() + carCrush->GetHeight());

	mainCar->Hide();
	carCrush->Hide();
	make_explode(right, top, left, bottom);
	findndelete(mainCar);
	findndelete(carCrush);
	return 1;

}

void World::findndelete(CarBody* car)
{
	bool found = false;
	for (int i = 0; i < total_cars; i++)
	{
		if (found)
		{
			cars[i - 1] = cars[i];
			continue;
		}
		if (cars[i] == car)
		{
			found = true;
			delete car;
			continue;
		}
	}
	total_cars--;
}

void World::make_explode(int x1, int y1, int x2, int y2)
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(hdc, Pen);
	SelectObject(hdc, hBrush);
	int centerX = (x1 + x2) / 2;
	int centerY = (y1 + y2) / 2;
	int radius = max(x2 - x1, y2 - y1) * 2; // начальный радиус
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	hBrush = CreateSolidBrush(RGB(255, 255, 0));
	SelectObject(hdc, Pen);
	SelectObject(hdc, hBrush);
	radius /= 1.5;
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 165, 0));
	hBrush = CreateSolidBrush(RGB(255, 165, 0));
	SelectObject(hdc, Pen);
	SelectObject(hdc, hBrush);
	radius /= 1.5;
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
	Sleep(2000);
	CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	hBrush = CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(hdc, Pen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, (x1 + x2) / 8, (y1 + y2) / 8, (x1 + x2) * 7 / 8, (y1 + y2) * 7 / 8);
}

void CarBody::MoveTo(int NewX, int NewY)
{
	Hide();
	X = NewX;
	Y = NewY;
	int check = world->check_car_bump(this);
	if (check)
		return;
	Show();
};