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
	Car(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~Car(); // ����������
	
	void Show(); // ���������� ������������ ������� Show
	void Hide(); // ���������� ������������ ������� Hide
	
	virtual void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
	void bump_action(BumpObject* bumpedOne);
	
	//������� ��������� ������ ������
	virtual void DrawBody();	// ��������� ��������� ���� ������
	void DrawObjectParts();		// ��������� ������ ������ ���������� ���������� ���������
	virtual void DrawParts();	// ��������� ���������� ������� ������
	virtual void DrawWindow();	// ��������� ����
	virtual void DrawLights();	// ��������� ���
	virtual void DrawRoof();	// ��������� �����
	
	//������� �������� ������ ������
	virtual void HideBody();	// �������� ��������� ���� ������
	virtual void HideParts();	// �������� ���������� ������� ������
	virtual void HideWindow();	// �������� ����
	virtual void HideLights();	// �������� ���
	virtual void HideRoof();	// �������� �����
	void HideObjectParts();		// �������� ������ ������ ���������� ���������� ���������
};