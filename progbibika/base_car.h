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

class CarBody : public CarPart
{
protected:
	int width;
	int height;
	CarPart* parts[CAR_PARTS_CAP] = {};
	int parts_quantity = 0;
public:
	CarBody(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~CarBody(); // ����������
	
	void Show(); // ���������� ������������ ������� Show
	void Hide(); // ���������� ������������ ������� Hide
	void MoveTo(int NewX, int NewY); // ���������� ������������ ������� MoveTo

	int GetWidth(); // ����� ��� ������ ������
	int GetHeight(); // ����� ��� ������ ������
	
	virtual void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
	
	//������� ��������� ������ ������
	virtual void DrawBody();	// ��������� ��������� ���� ������
	void DrawObjectParts();		// ��������� ������ ������ ���������� ���������� ���������
	virtual void DrawParts();	// ��������� ���������� ������� ������
	virtual void DrawWindow();	// ��������� ����
	virtual void DrawLights();	// ��������� ���

	//������� �������� ������ ������
	virtual void HideBody(); // �������� ��������� ���� ������
	void HideObjectParts();	 // �������� ������ ������ ���������� ���������� ���������
};