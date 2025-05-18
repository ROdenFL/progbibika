#pragma once
#include "base_car.h"

class DoubleDeck : public Car
{
public:
	DoubleDeck(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void DrawRoof();
	void HideRoof();
};

class CarTireThree : public Car
{
public:
	CarTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
};

class DoubleDeckTireless : public DoubleDeck
{
public:
	DoubleDeckTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts();
};

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

class LowRiderTireless : public LowRider
{
public:
	LowRiderTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
};

class LowRiderTireThree : public LowRider
{
public:
	LowRiderTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
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

class GazelTireless : public Gazel
{
public:
	GazelTireless(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
};

class GazelTireThree : public Gazel
{
public:
	GazelTireThree(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������
};

class GazelDD : public Gazel
{
public:
	GazelDD(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void DrawRoof();
	void HideRoof();
};

class Truck : public Car
{
public:
	Truck(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������

	void PopulateParts(); // ���� �������� ������ ������, ���������� ���������� ���������

	//������� ��������� ������ ������
	void DrawWindow();	// ��������� ����
	void DrawLights();	// ��������� ���
	void DrawRoof();	// ��������� �����

	//������� �������� ������ ������
	void HideWindow();	// �������� ����
	void HideLights();	// �������� ���
	void HideRoof();	// �������� �����
};

// ����� ����
class Saw : public ABCWorldObject {
protected:
	int index = 0;
public:
    Saw(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //�����������

	void bump_action(ABCWorldObject* bumpedOne);
	void Show();
	void Hide();
};

// ����� �����
class Roof : public Saw {
public:
	Roof(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //�����������

	void Show();
	void Hide();
};

// ����� �������
class ExtraTire : public Saw {
public:
	ExtraTire(int InitX = 300, int InitY = 300, int initWidth = 200, int initHeight = 200); //�����������

	void Show();
	void Hide();
};