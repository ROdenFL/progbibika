#pragma once
#define OBJECTS_LIMIT 6
#include "base_figures.h"

class World
{
protected:
	ABCWorldObject* objects[OBJECTS_LIMIT];
	int total_objects = 0;
public:
	int add_object(ABCWorldObject* newObject); //���������� ������� � "���"
	void check_bump(ABCWorldObject* bumpObject); //�������� ������������
	void findndelete(ABCWorldObject* bumpObject); //�������� ������� �� ������ �������� ������������
	void make_explode(int x1, int y1, int x2, int y2); //����� ������ � �������� �����������
};