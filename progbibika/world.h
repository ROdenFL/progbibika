#pragma once
#define OBJECTS_LIMIT 6
#include "base_figures.h"

class World
{
protected:
	ABCWorldObject* objects[OBJECTS_LIMIT];
	int total_objects = 0;
public:
	int add_object(ABCWorldObject* newObject); //добавление объекта в "мир"
	void check_bump(ABCWorldObject* bumpObject); //проверка столкновения
	void findndelete(ABCWorldObject* bumpObject); //удаление объекта из списка объектов столкновения
	void make_explode(int x1, int y1, int x2, int y2); //вызов взрыва в заданных координатах
};