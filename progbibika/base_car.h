#pragma once
#include "world.h"
#define CAR_PARTS_CAP 10

class CarPart : public ABCWorldObject
{
protected:
	int altRGB[3] = { 255, 0, 0 };
	int altHideRGB[3] = { 255, 255, 255 };
public:
	CarPart(int initX = 10, int initY = 10, int initWidth = 100, int initHeight = 50);
	~CarPart(void);
	COLORREF GetAltRGB();
	COLORREF GetAltHideRGB();
	void SetAltRGB(int R, int G, int B);
	void SetAltHideRGB(int R, int G, int B);

	void bump_action(ABCWorldObject* bumpedOne);
	virtual void Show(int baseX = 0, int baseY = 0);
	virtual void Hide(int baseX = 0, int baseY = 0);
};

class Wheel : public CarPart 
{
protected:
	int diskRadius;
	int tireRadius;
public:
	Wheel(int initX = 10, int initY = 10, int initWidth = 250, int initHeight = 50);
	~Wheel();
	virtual void Show(int baseX = 0, int baseY = 0);
	virtual void Hide(int baseX = 0, int baseY = 0);
};

class ITransport
{
public:
	//Функции отрисовки частей машины
	virtual void DrawBody() = 0;		// Абстраткная отрисовка основного тела машины
	virtual void DrawObjectParts() = 0;	// Абстраткная отрисовка частей машины являющихся отдельными объектами
	virtual void DrawParts() = 0;		// Абстраткная отрисовка монолитных деталей машины
	virtual void DrawWindow() = 0;		// Абстраткная отрисовка окна
	virtual void DrawLights() = 0;		// Абстраткная отрисовка фар
	virtual void DrawRoof() = 0;		// Абстраткная отрисовка крыши

	//Функции прятанья частей машины
	virtual void HideBody() = 0;		// Абстраткное прятанье основного тела машины
	virtual void HideParts() = 0;		// Абстраткное прятанье монолитных деталей машины
	virtual void HideWindow() = 0;		// Абстраткное прятанье окна
	virtual void HideLights() = 0;		// Абстраткное прятанье фар
	virtual void HideRoof() = 0;		// Абстраткное прятанье крыши
	virtual void HideObjectParts() = 0;	// Абстраткное прятанье частей машины являющихся отдельными объектами
};
	

class Car : public CarPart, public ITransport
{
protected:
	CarPart* parts[CAR_PARTS_CAP] = {};
	int parts_quantity = 0;
	int index = 0; // индекс класса в иерархии
public:
	Car(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // конструктор
	~Car(); // деструктор
	
	void Show(); // перегрузка родительской функции Show
	void Hide(); // перегрузка родительской функции Hide
	
	int GetIndex(); // возращает индекс класса в иерархии

	virtual void PopulateParts(); // Сбор основных частей машины, являющихся отдельными объектами
	void bump_action(ABCWorldObject* bumpedOne);
	
	//Функции отрисовки частей машины
	void DrawBody();		// Отрисовка основного тела машины
	void DrawObjectParts();	// Отрисовка частей машины являющихся отдельными объектами
	void DrawParts();		// Отрисовка монолитных деталей машины
	void DrawWindow();		// Отрисовка окна
	void DrawLights();		// Отрисовка фар
	void DrawRoof();		// Отрисовка крыши
	
	//Функции прятанья частей машины
	void HideBody();		// Прятанье основного тела машины
	void HideParts();		// Прятанье монолитных деталей машины
	void HideWindow();		// Прятанье окна
	void HideLights();		// Прятанье фар
	void HideRoof();		// Прятанье крыши
	void HideObjectParts();	// Прятанье частей машины являющихся отдельными объектами
};