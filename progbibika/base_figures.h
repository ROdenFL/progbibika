#pragma once
#include <windows.h>
class World;
/******************************************************************/
/*                  � � � �    � � � � � �                        */
/******************************************************************/

/*------------------  ����� �������������� ----------------------*/
class Location
{
protected:
    int X;
    int Y;
public:
    Location(int InitX, int InitY);
    ~Location();                   
    int GetX();
    int GetY();
};

/*------------------  ����� ����� -------------------------------*/
class Point : public Location
{
protected:
    bool Visible;
    //�������� ���� �������
    int baseRGB[3] = { 255, 0, 0 };
    //���� ����������� �������
    int hideRGB[3] = { 255, 255, 255 };
    
public:
    Point(int InitX, int InitY); // �����������
    ~Point(); //�������������     
    bool GetVisible(); //������ ��� Visible    
    void SetVisible(bool NewVisible); //������ ��� Visible 
    COLORREF GetBaseRGB(); //������ ��������� ����� �������
    COLORREF GetHideRGB(); //������ ����� ����������� �������
    void SetBaseRGB(int R, int G, int B); // ������ ��������� ����� �������
    void SetHideRGB(int R, int G, int B); // ������ ����� ����������� �������
    void Drag(int Step); // ������� ����������� ������� �� �������
    
    virtual void MoveTo(int NewX, int NewY);
    virtual void Show();
    virtual void Hide(); 
};

//������ ������������
class ABCWorldObject : public Point
{
protected:
    int width = 0; //������
    int height = 0; //�����
public:
    ABCWorldObject(int InitX, int InitY, int initWidth, int initHeight); // �����������
    ~ABCWorldObject(); //������������� 
    virtual void bump_action(ABCWorldObject* bumpedOne) = 0; // ��������, ������������ � ������ ������
    void MoveTo(int NewX, int NewY); // ���������� MoveTo ��� �������� ������������

    int GetWidth(); // ����� ��� ������
    int GetHeight(); // ����� ��� ������ 
};