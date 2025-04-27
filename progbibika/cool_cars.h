#pragma once
#include "base_car.h"

class LowRider : public Car
{
public:
	LowRider(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~LowRider(); // ����������

	//������� ��������� ������ ������
	void DrawBody();	// ��������� ��������� ���� ������
	void DrawWindow();	// ��������� ����
	void DrawLights();	// ��������� ���
	void DrawRoof();	// ��������� �����

	//������� �������� ������ ������
	void HideWindow();	// �������� ����
	void HideLights();	// �������� ���
	void HideBody();	// �������� ��������� ���� ������
	void HideRoof();	// �������� �����
};

class Gazel : public Car
{
public:
	Gazel(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~Gazel(); // ����������

	//������� ��������� ������ ������
	
	void DrawWindow();	// ��������� ����
	void DrawLights();	// ��������� ���
	void DrawRoof();	// ��������� �����

	//������� �������� ������ ������
	void HideWindow();	// �������� ����
	void HideBody();	// �������� ��������� ���� ������
	void HideRoof();	// �������� �����
};

// ����� ����
class Saw : public BumpObject {
public:
    Saw(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200);

    void bump_action(BumpObject* bumpedOne);
	void Show();
	void Hide();
};


// ����� �����
class Roof : public BumpObject {
public:
	Roof(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200);

	void bump_action(BumpObject* bumpedOne);
	void Show();
	void Hide();
};