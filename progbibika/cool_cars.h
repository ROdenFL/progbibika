#pragma once
#include "base_car.h"

class LowRider : public CarBody
{
public:
	LowRider(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~LowRider(); // ����������

	//������� ��������� ������ ������
	void DrawBody();	// ��������� ��������� ���� ������
	void DrawWindow();	// ��������� ����
	void DrawLights();	// ��������� ���
	void DrawRoof();	// ��������� �����
	void DrawWheels();	// ��������� �����

	//������� �������� ������ ������
	void HideWindow();	// �������� ����
	void HideLights();	// �������� ���
	void HideBody();	// �������� ��������� ���� ������
	void HideRoof();	// �������� �����
	void HideWheels();	// �������� �����

	/* �������������� ������� ��� ������ ������������� ������� */
	void Show();
	void Hide();
	void DrawParts();
	void HideParts();
	void MoveTo(int NewX, int NewY);
	void Drag(int Step);
};

class Gazel : public CarBody
{
public:
	Gazel(int initX = 10, int initY = 10, int initWidth = 300, int initHeight = 200); // �����������
	~Gazel(); // ����������

	//������� ��������� ������ ������
	
	void DrawWindow();	// ��������� ����
	void DrawLights();	// ��������� ���
	void DrawRoof();	// ��������� �����
	void DrawWheels();	// ��������� �����

	//������� �������� ������ ������
	void HideWindow();	// �������� ����
	void HideBody();	// �������� ��������� ���� ������
	void HideRoof();	// �������� �����
	void HideWheels();	// �������� �����

	/* �������������� ������� ��� ������ ������������� ������� */
	void Show();
	void Hide();
	void DrawParts();
	void HideParts();
	void MoveTo(int NewX, int NewY);
	void Drag(int Step);
};