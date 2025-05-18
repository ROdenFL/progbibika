#pragma once
#include "base_car.h"

class DoubleDeck : public Car
{
public:
	DoubleDeck(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void DrawRoof();
	void HideRoof();
};

class CarTireThree : public Car
{
public:
	CarTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
};

class DoubleDeckTireless : public DoubleDeck
{
public:
	DoubleDeckTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts();
};

class LowRider : public Car
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

class LowRiderTireless : public LowRider
{
public:
	LowRiderTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
};

class LowRiderTireThree : public LowRider
{
public:
	LowRiderTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
};

class Gazel : public Car
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

class GazelTireless : public Gazel
{
public:
	GazelTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
};

class GazelTireThree : public Gazel
{
public:
	GazelTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
};

class GazelDD : public Gazel
{
public:
	GazelDD(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void DrawRoof();
	void HideRoof();
};

class Truck : public Car
{
public:
	Truck(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор

	void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами

	//Функции отрисовки частей машины
	void DrawWindow();	// Отрисовка окна
	void DrawLights();	// Отрисовка фар
	void DrawRoof();	// Отрисовка крыши

	//Функции прятанья частей машины
	void HideWindow();	// Прятанье окна
	void HideLights();	// Прятанье фар
	void HideRoof();	// Прятанье крыши
};

// Класс пилы
class Saw : public ABCWorldObject {
protected:
	int index = 0;
public:
    Saw(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //коснтруктор

	void bump_action(ABCWorldObject* bumpedOne);
	void Show();
	void Hide();
};

// Класс крыши
class Roof : public Saw {
public:
	Roof(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //коснтруктор

	void Show();
	void Hide();
};

// Класс запаски
class ExtraTire : public Saw {
public:
	ExtraTire(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //коснтруктор

	void Show();
	void Hide();
};