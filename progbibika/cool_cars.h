#pragma once
#include "base_car.h"

class LowRider : public CarBody
{
public:
	LowRider(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор
	~LowRider(); // деструктор

	//Функции отрисовки частей машины
	void DrawBody();	// Отрисовка основного тела машины
	void DrawWindow();	// Отрисовка окна
	void DrawLights();	// Отрисовка фар
	void DrawRoof();	// Отрисовка крыши

	//Функции прятанья частей машины
	void HideWindow();	// Прятанье окна
	void HideLights();	// Прятанье фар
	void HideBody();	// Прятанье основного тела машины
	void HideRoof();	// Прятанье крыши
};

class Gazel : public CarBody
{
public:
	Gazel(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор
	~Gazel(); // деструктор

	//Функции отрисовки частей машины
	
	void DrawWindow();	// Отрисовка окна
	void DrawLights();	// Отрисовка фар
	void DrawRoof();	// Отрисовка крыши

	//Функции прятанья частей машины
	void HideWindow();	// Прятанье окна
	void HideBody();	// Прятанье основного тела машины
	void HideRoof();	// Прятанье крыши
};

// Класс пилы
class Saw : public BumpObject {
public:
    Saw(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200);

    bool bump_action(BumpObject** bumpedOne);
	void Show();
};