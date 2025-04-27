#include <windows.h>
#include <iostream>
#include "base_car.h"
#include "base_figures.cpp"

extern HDC hdc;
extern World world;
extern Car* curCar;
using namespace std;

const COLORREF WINDOW_COLOR = RGB(0, 128, 168);
const COLORREF LIGHTS_COLOR = RGB(250, 250, 0);

CarPart::CarPart(int InitX, int InitY) :BumpObject(InitX, InitY)
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

void CarPart::Show(int baseX, int baseY) 
{
    world.check_bump(this);
}
void CarPart::Hide(int baseX, int baseY) {}

Wheel::Wheel(int initX, int initY, int initTireRadius, int initDiskRadius) :CarPart(initX, initY)
{
    tireRadius = initTireRadius;
    diskRadius = initDiskRadius;
    width = tireRadius * 2;
    height = width;
    SetBaseRGB(0, 0, 0);
    SetAltRGB(128, 128, 128);
}

Wheel::~Wheel(void)
{
};

void Wheel::Show(int baseX, int baseY)
{
    Visible = true;
    int posX = baseX + X;
    int posY = baseY + Y;
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
    DeleteObject(Pen);
    DeleteObject(hBrush);
    Pen = CreatePen(PS_SOLID, 2, GetAltRGB());
    hBrush = CreateSolidBrush(GetAltRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, posX - diskRadius, posY - diskRadius, posX + diskRadius, posY + diskRadius);
    DeleteObject(Pen);
    DeleteObject(hBrush);
}

void Wheel::Hide(int baseX, int baseY)
{
    Visible = false;
    int posX = baseX + X;
    int posY = baseY + Y;
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, posX - tireRadius, posY - tireRadius, posX + tireRadius, posY + tireRadius);
    DeleteObject(Pen);
}

Car::Car(int initX, int initY, int initWidth, int initHeight) :CarPart(initX, initY)
{
    width = initWidth;
    height = initHeight;
    PopulateParts();
}

Car::~Car()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
}

// Создание частей машины являющихся отдельными объектами
void Car::PopulateParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
    parts_quantity = 0;
    parts[parts_quantity++] = new Wheel(width / 4, height, width/6, width/12);
    parts[parts_quantity++] = new Wheel(width * 3 / 4, height, width / 6, width / 12);
}

void Car::bump_action(BumpObject* bumpedOne)
{
    int left = min(bumpedOne->GetX(), GetX());
    int right = max(bumpedOne->GetX() + bumpedOne->GetWidth(), GetX() + GetWidth());
    int bottom = min(bumpedOne->GetY(), GetY());
    int top = max(bumpedOne->GetY() + bumpedOne->GetHeight(), GetY() + GetHeight());

    bumpedOne->Hide();
    Hide();
    world.make_explode(right, top, left, bottom);
    world.findndelete(bumpedOne);
    world.findndelete(this);
}

void Car::Show()
{
    DrawBody();
    DrawParts();
    DrawObjectParts();
}

void Car::Hide()
{
    HideBody();
    HideParts();
    HideObjectParts();
}

// Отрисовка основного тела машины
void Car::DrawBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Отрисовка частей машины являющихся отдельными объектами
void Car::DrawObjectParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        CarPart* part = parts[i];
        part->Show(X, Y);
    }
}

// Отрисовка монолитных деталей машины
void Car::DrawParts()
{
    DrawRoof();
    DrawWindow();
    DrawLights();
}

// Отрисовка окна
void Car::DrawWindow()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, WINDOW_COLOR);
    HBRUSH hBrush = CreateSolidBrush(WINDOW_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y + height / 8, X + width * 3 / 8, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Отрисовка фар
void Car::DrawLights()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, LIGHTS_COLOR);
    HBRUSH hBrush = CreateSolidBrush(LIGHTS_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X, Y + height * 3 / 4, X + width * 1 / 16, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Car::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Прятанье основного тела машины
void Car::HideBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Car::HideParts()
{
    HideWindow();
    HideLights();
    HideRoof();
}

void Car::HideWindow()
{
}

void Car::HideLights()
{
}

void Car::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Прятанье частей машины являющихся отдельными объектами
void Car::HideObjectParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        CarPart* part = parts[i];
        part->Hide(X, Y);
    }
}