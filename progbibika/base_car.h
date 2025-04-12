#pragma once
#include "base_figures.h"
#define CAR_PARTS_CAP 10

class CarPart : public Point
{
protected:
	int altRGB[3] = { 255, 0, 0 };
	int altHideRGB[3] = { 0, 0, 255 };
public:
	CarPart(int initX = 10, int initY = 10);
	~CarPart(void);
	COLORREF GetAltRGB();
	COLORREF GetAltHideRGB();
	void SetAltRGB(int R, int G, int B);
	void SetAltHideRGB(int R, int G, int B);
	void Show(int baseX = 0, int baseY = 0);
	void Hide(int baseX = 0, int baseY = 0);
};

//class Wheel : public CarPart 
//{
//protected:
//	int diskRadius;
//	int tireRadius;
//public:
//	Wheel(int initX = 10, int initY = 10, int initTireRadius = 50, int initDiskRadius = 25);
//	~Wheel();
//	virtual void Show(int baseX = 0, int baseY = 0);
//	virtual void Hide(int baseX = 0, int baseY = 0);
//};

class CarBody : public CarPart
{
protected:
	int width;
	int height;
	//CarPart* parts[CAR_PARTS_CAP] = {};
	//int parts_quantity = 0;
public:
	CarBody(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор
	~CarBody(); // деструктор
	
	void Show(); // перегрузка родительской функции Show
	void Hide(); // перегрузка родительской функции Hide
	void MoveTo(int NewX, int NewY); // перегрузка родительской функции MoveTo

	int GetWidth(); // гетер для ширины машины
	int GetHeight(); // гетер для высоты машины
	
	//virtual void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
	
	/* ВИРТУАЛЬНЫЕ */
	
	////Функции отрисовки частей машины
	//virtual void DrawBody();	// Отрисовка основного тела машины
	////void DrawObjectParts();		// Отрисовка частей машины являющихся отдельными объектами
	//virtual void DrawParts();	// Отрисовка монолитных деталей машины
	//virtual void DrawWindow();	// Отрисовка окна
	//virtual void DrawLights();	// Отрисовка фар
	//virtual void DrawRoof();	// Отрисовка крыши
	//virtual void DrawWheels();	// Отрисовка колес
	//
	////Функции прятанья частей машины
	//virtual void HideBody();	// Прятанье основного тела машины
	//virtual void HideParts();	// Прятанье монолитных деталей машины
	//virtual void HideWindow();	// Прятанье окна
	//virtual void HideLights();	// Прятанье фар
	//virtual void HideRoof();	// Прятанье крыши
	//virtual void HideWheels();	// Прятанье колес
	////void HideObjectParts();	// Прятанье частей машины являющихся отдельными объектами
	
	
	/* НЕВИРТУАЛЬНЫЕ */
	
	void Drag(int Step); 
	
	//Функции отрисовки частей машины
	void DrawBody();	// Отрисовка основного тела машины
	void DrawParts();	// Отрисовка монолитных деталей машины
	void DrawWindow();	// Отрисовка окна
	void DrawLights();	// Отрисовка фар
	void DrawRoof();	// Отрисовка крыши
	void DrawWheels();	// Отрисовка колес

	//Функции прятанья частей машины
	void HideBody();	// Прятанье основного тела машины
	void HideParts();	// Прятанье монолитных деталей машины
	void HideWindow();	// Прятанье окна
	void HideLights();	// Прятанье фар
	void HideRoof();	// Прятанье крыши
	void HideWheels();	// Прятанье колес
	
};