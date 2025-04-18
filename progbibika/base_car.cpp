#include <windows.h>
#include "base_car.h"
#include "base_figures.cpp"

extern HDC hdc;
class World;

const COLORREF WINDOW_COLOR = RGB(0, 128, 168);
const COLORREF LIGHTS_COLOR = RGB(250, 250, 0);

CarPart::CarPart(int InitX, int InitY) :Point(InitX, InitY)
{
};

CarPart::~CarPart(void)
{
};

COLORREF CarPart::GetAltRGB()
{
    return RGB(altRGB[0], altRGB[1], altRGB[2]);
}

COLORREF CarPart::GetAltHideRGB()
{
    return RGB(altHideRGB[0], altHideRGB[1], altHideRGB[2]);
}

void CarPart::SetAltRGB(int R, int G, int B)
{
    altRGB[0] = R;
    altRGB[1] = G;
    altRGB[2] = B;
}

void CarPart::SetAltHideRGB(int R, int G, int B)
{
    altHideRGB[0] = R;
    altHideRGB[1] = G;
    altHideRGB[2] = B;
}

void CarPart::Show(int baseX, int baseY) {}
void CarPart::Hide(int baseX, int baseY) {}

//Wheel::Wheel(int initX, int initY, int initTireRadius, int initDiskRadius) :CarPart(initX, initY)
//{
//    tireRadius = initTireRadius;
//    diskRadius = initDiskRadius;
//    SetBaseRGB(0, 0, 0);
//    SetAltRGB(128, 128, 128);
//}
//
//Wheel::~Wheel(void)
//{
//};
//
//void Wheel::Show(int baseX, int baseY)
//{
//    Visible = true;
//    int posX = baseX + X;
//    int posY = baseY + Y;
//    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
//    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
//    SelectObject(hdc, Pen);
//    SelectObject(hdc, hBrush);
//    Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
//    DeleteObject(Pen);
//    DeleteObject(hBrush);
//    Pen = CreatePen(PS_SOLID, 2, GetAltRGB());
//    hBrush = CreateSolidBrush(GetAltRGB());
//    SelectObject(hdc, Pen);
//    SelectObject(hdc, hBrush);
//    Ellipse(hdc, posX - diskRadius, posY - diskRadius, posX + diskRadius, posY + diskRadius);
//    DeleteObject(Pen);
//    DeleteObject(hBrush);
//}
//void Wheel::Hide(int baseX, int baseY)
//{
//    Visible = false;
//    int posX = baseX + X;
//    int posY = baseY + Y;
//    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
//    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
//    SelectObject(hdc, Pen);
//    SelectObject(hdc, hBrush);
//    Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
//    DeleteObject(Pen);
//}

CarBody::CarBody(int initX, int initY, int initWidth, int initHeight) :CarPart(initX, initY)
{
    width = initWidth;
    height = initHeight;
    //PopulateParts();
}

CarBody::~CarBody()
{
    /*for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }*/
}

int CarBody::GetWidth()
{
    return width;
}

int CarBody::GetHeight()
{
    return height;
}

//void CarBody::PopulateParts()
//{
//    for (int i = 0; i < parts_quantity; i++)
//    {
//        delete parts[i];
//    }
//    parts_quantity = 0;
//    parts[parts_quantity++] = new Wheel(width / 4, height);
//    parts[parts_quantity++] = new Wheel(width * 3 / 4, height);
//}

void CarBody::Show()
{
    DrawBody();
    DrawParts();
    //DrawObjectParts();
}

void CarBody::Hide()
{
    HideBody();
    HideParts();
    //HideObjectParts();
}

// ��������� ��������� ���� ������
void CarBody::DrawBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// ��������� ������ ������ ���������� ���������� ���������
//void CarBody::DrawObjectParts()
//{
//    for (int i = 0; i < parts_quantity; i++)
//    {
//        CarPart* part = parts[i];
//        part->Show(X, Y);
//    }
//}

// ��������� ���������� ������� ������
void CarBody::DrawParts()
{
    DrawRoof();
    DrawWindow();
    DrawLights();
    DrawWheels();
}

// ��������� ����
void CarBody::DrawWindow()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, WINDOW_COLOR);
    HBRUSH hBrush = CreateSolidBrush(WINDOW_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y + height / 8, X + width * 3 / 8, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// ��������� ���
void CarBody::DrawLights()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, LIGHTS_COLOR);
    HBRUSH hBrush = CreateSolidBrush(LIGHTS_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X, Y + height * 3 / 4, X + width * 1 / 16, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void CarBody::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void CarBody::DrawWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 6;
    int diskRadius = width / 10;
    HPEN Pen;
    HBRUSH hBrush;
    for (int i = 0; i < 2; i++)
    {
        Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
        hBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, Pen);
        SelectObject(hdc, hBrush);
        Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
        Pen = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
        hBrush = CreateSolidBrush(RGB(128, 128, 128));
        SelectObject(hdc, Pen);
        SelectObject(hdc, hBrush);
        Ellipse(hdc, posX - diskRadius, posY - diskRadius, posX + diskRadius, posY + diskRadius);
        posX += width / 2;
    }
    DeleteObject(Pen);
    DeleteObject(hBrush);
}

// �������� ��������� ���� ������
void CarBody::HideBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void CarBody::HideParts()
{
    HideWindow();
    HideLights();
    HideRoof();
    HideWheels();
}

void CarBody::HideWindow()
{
}

void CarBody::HideLights()
{
}

void CarBody::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void CarBody::HideWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 6;
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    for (int i = 0; i < 2; i++)
    {
        
        Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
        posX += width / 2;
    }
    DeleteObject(Pen);
    DeleteObject(hBrush);
}

// �������� ������ ������ ���������� ���������� ���������
//void CarBody::HideObjectParts()
//{
//    for (int i = 0; i < parts_quantity; i++)
//    {
//        CarPart* part = parts[i];
//        part->Hide(X, Y);
//    }
//}

/* �������������� ������� ��� ������ ������������� ������� */

void CarBody::Drag(int Step)
{
    int FigX, FigY;

    FigX = GetX();
    FigY = GetY();

    while (true)
    {
        if (!this)
            break;

        if (KEY_DOWN(VK_ESCAPE))
            break;

        if (KEY_DOWN(VK_LEFT))
        {
            FigX -= Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_RIGHT))
        {
            FigX += Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_UP))
        {
            FigY -= Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

        if (KEY_DOWN(VK_DOWN))
        {
            FigY += Step;
            MoveTo(FigX, FigY);
            Sleep(500);
        }

    }
}

void CarBody::MoveTo(int NewX, int NewY)
{
    Hide();
    X = NewX;
    Y = NewY;
    Show();
};