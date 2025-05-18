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
	//������� ��������� ������ ������
	virtual void DrawBody() = 0;		// ����������� ��������� ��������� ���� ������
	virtual void DrawObjectParts() = 0;	// ����������� ��������� ������ ������ ���������� ���������� ���������
	virtual void DrawParts() = 0;		// ����������� ��������� ���������� ������� ������
	virtual void DrawWindow() = 0;		// ����������� ��������� ����
	virtual void DrawLights() = 0;		// ����������� ��������� ���
	virtual void DrawRoof() = 0;		// ����������� ��������� �����

	//������� �������� ������ ������
	virtual void HideBody() = 0;		// ����������� �������� ��������� ���� ������
	virtual void HideParts() = 0;		// ����������� �������� ���������� ������� ������
	virtual void HideWindow() = 0;		// ����������� �������� ����
	virtual void HideLights() = 0;		// ����������� �������� ���
	virtual void HideRoof() = 0;		// ����������� �������� �����
	virtual void HideObjectParts() = 0;	// ����������� �������� ������ ������ ���������� ���������� ���������
};
	

class Car : public CarPart, public ITransport
{
protected:
	CarPart* parts[CAR_PARTS_CAP] = {};
	int parts_quantity = 0;
	int index = 0; // ������ ������ � ��������
public:
	Car(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~Car(); // ����������
	
	void Show(); // ���������� ������������ ������� Show
	void Hide(); // ���������� ������������ ������� Hide
	
	int GetIndex(); // ��������� ������ ������ � ��������

	virtual void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
	void bump_action(ABCWorldObject* bumpedOne);
	
	//������� ��������� ������ ������
	void DrawBody();		// ��������� ��������� ���� ������
	void DrawObjectParts();	// ��������� ������ ������ ���������� ���������� ���������
	void DrawParts();		// ��������� ���������� ������� ������
	void DrawWindow();		// ��������� ����
	void DrawLights();		// ��������� ���
	void DrawRoof();		// ��������� �����
	
	//������� �������� ������ ������
	void HideBody();		// �������� ��������� ���� ������
	void HideParts();		// �������� ���������� ������� ������
	void HideWindow();		// �������� ����
	void HideLights();		// �������� ���
	void HideRoof();		// �������� �����
	void HideObjectParts();	// �������� ������ ������ ���������� ���������� ���������
};