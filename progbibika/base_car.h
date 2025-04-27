#pragma once
#include "world.h"
#define CAR_PARTS_CAP 10

class CarPart : public BumpObject
{
protected:
	int altRGB[3] = { 255, 0, 0 };
	int altHideRGB[3] = { 255, 255, 255 };
public:
	CarPart(int initX = 10, int initY = 10);
	~CarPart(void);
	COLORREF GetAltRGB();
	COLORREF GetAltHideRGB();
	void SetAltRGB(int R, int G, int B);
	void SetAltHideRGB(int R, int G, int B);
	virtual void Show(int baseX = 0, int baseY = 0);
	virtual void Hide(int baseX = 0, int baseY = 0);
};

class Wheel : public CarPart 
{
protected:
	int diskRadius;
	int tireRadius;
public:
	Wheel(int initX = 10, int initY = 10, int initTireRadius = 50, int initDiskRadius = 25);
	~Wheel();
	virtual void Show(int baseX = 0, int baseY = 0);
	virtual void Hide(int baseX = 0, int baseY = 0);
};

class Car : public CarPart
{
protected:
	CarPart* parts[CAR_PARTS_CAP] = {};
	int parts_quantity = 0;
public:
	Car(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор
	~Car(); // деструктор
	
	void Show(); // перегрузка родительской функции Show
	void Hide(); // перегрузка родительской функции Hide
	
	virtual void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
	void bump_action(BumpObject* bumpedOne);
	
	//Функции отрисовки частей машины
	virtual void DrawBody();	// Отрисовка основного тела машины
	void DrawObjectParts();		// Отрисовка частей машины являющихся отдельными объектами
	virtual void DrawParts();	// Отрисовка монолитных деталей машины
	virtual void DrawWindow();	// Отрисовка окна
	virtual void DrawLights();	// Отрисовка фар
	virtual void DrawRoof();	// Отрисовка крыши
	
	//Функции прятанья частей машины
	virtual void HideBody();	// Прятанье основного тела машины
	virtual void HideParts();	// Прятанье монолитных деталей машины
	virtual void HideWindow();	// Прятанье окна
	virtual void HideLights();	// Прятанье фар
	virtual void HideRoof();	// Прятанье крыши
	void HideObjectParts();		// Прятанье частей машины являющихся отдельными объектами
};