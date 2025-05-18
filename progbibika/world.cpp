#include "world.h"
#include <algorithm>
using namespace std;

extern HDC hdc;

//добавление объекта в список объектов столкновения
int World::add_object(ABCWorldObject* newObject)
{
	if (total_objects >= OBJECTS_LIMIT)
	{
		return 3; //слишком много машин
	}
	objects[total_objects++] = newObject;
	return 0;
}

void World::check_bump(ABCWorldObject* bumpObject)
{
	ABCWorldObject* curObject;
	ABCWorldObject* crushObject = NULL;
	//поиск объекта с ненулевой площадью пересечения
	for (int i = 0; i < total_objects; i++)
	{
		curObject = objects[i];
		if (curObject == bumpObject)	continue;

		int left	=	max(bumpObject->GetX(), curObject->GetX());
		int right	=	min(bumpObject->GetX() + bumpObject->GetWidth(), curObject->GetX() + curObject->GetWidth());
		int bottom	=	max(bumpObject->GetY(), curObject->GetY());
		int top		=	min(bumpObject->GetY() + bumpObject->GetHeight(), curObject->GetY() + curObject->GetHeight());

		int width = right - left;
		int height = top - bottom;

		if (width < 0 || height < 0)
			continue;
		
		crushObject = curObject;
		break;
	}
	
	//если объект не найден
	if (!crushObject)
		return;

	//вызов функции столкновения
	crushObject->bump_action(bumpObject);
}

void World::findndelete(ABCWorldObject* object)
{
	for (int i = 0; i < total_objects; i++)
	{
		if (objects[i] == object)
		{
			// Сдвигаем все элементы после найденного
			for (int j = i; j < total_objects; j++)
			{
				objects[j] = objects[j + 1];
			}

			total_objects--;
			return; // Выходим после удаления
		}
	}
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
	Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	hBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	SelectObject(hdc, hBrush);
	Rectangle(hdc, (x1 + x2) / 8, (y1 + y2) / 12, (x1 + x2) * 7 / 8, (y1 + y2));
}