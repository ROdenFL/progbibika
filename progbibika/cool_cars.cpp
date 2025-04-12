#include <windows.h>
#include "cool_cars.h"

extern HDC hdc;

const COLORREF WINDOW_COLOR = RGB(0, 128, 168);
const COLORREF LIGHTS_COLOR = RGB(250, 250, 0);
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//Класс лоурайдер

LowRider::LowRider(int initX, int initY, int initWidth, int initHeight) :CarBody(initX, initY, initWidth, initHeight)
{
    SetBaseRGB(192, 5, 248);
    SetAltRGB(104, 88, 243);
}

LowRider::~LowRider()
{
}

// Отрисовка основного тела машины
void LowRider::DrawBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    RoundRect(hdc, X, Y + height * 5 / 8, X + width, Y + height, 20, 20);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Отрисовка окна
void LowRider::DrawWindow()
{
    // Координаты для повернутого прямоугольника
    int x1 = X + width / 4;
    int y1 = Y + height / 8;
    int x2 = X + width * 3 / 8;
    int y2 = Y + height * 5 / 8;

    // Центр прямоугольника
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;

    // Предварительно вычисленные значения sin и cos для 30 градусов
    const double sin30 = 0.5;
    const double cos30 = 0.86602540378; // √3/2
    // Поворот каждой точки
    POINT rotatedRect[4];
    // Левая верхняя точка
    int x = x1 - centerX;
    int y = y1 - centerY;
    rotatedRect[0].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[0].y = (int)(x * sin30 + y * cos30) + centerY;
    // Правая верхняя точка
    x = x2 - centerX;
    y = y1 - centerY;
    rotatedRect[1].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[1].y = (int)(x * sin30 + y * cos30) + centerY;
    // Правая нижняя точка
    x = x2 - centerX;
    y = y2 - centerY;
    rotatedRect[2].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[2].y = (int)(x * sin30 + y * cos30) + centerY;
    // Левая нижняя точка
    x = x1 - centerX;
    y = y2 - centerY;
    rotatedRect[3].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[3].y = (int)(x * sin30 + y * cos30) + centerY;
    
    HPEN Pen = CreatePen(PS_SOLID, 2, WINDOW_COLOR);
    HBRUSH hBrush = CreateSolidBrush(WINDOW_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, rotatedRect, 4);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Отрисовка фар
void LowRider::DrawLights()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetAltRGB());
    HBRUSH hBrush = CreateSolidBrush(GetAltRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    RoundRect(hdc, X - width / 16, Y + height * 3 / 4, X + width / 4, Y + height / 2, width * 3 / 16, height / 4);
    Pen = CreatePen(PS_SOLID, 2, LIGHTS_COLOR);
    hBrush = CreateSolidBrush(LIGHTS_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X - width / 32, Y + height * 23 / 32, X + width * 1 / 16, Y + height * 17 / 32);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void LowRider::DrawRoof()
{
}

void LowRider::DrawWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 7;
    int diskRadius = width / 14;
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

// Прятанье основного тела машины
void LowRider::HideBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Прятанье окна
void LowRider::HideWindow()
{
    // Координаты для повернутого прямоугольника
    int x1 = X + width / 4;
    int y1 = Y + height / 8;
    int x2 = X + width * 3 / 8;
    int y2 = Y + height * 5 / 8;
    // Центр прямоугольника
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;
    // Предварительно вычисленные значения sin и cos для 30 градусов
    const double sin30 = 0.5;
    const double cos30 = 0.86602540378; // √3/2
    // Поворот каждой точки
    POINT rotatedRect[4];
    // Левая верхняя точка
    int x = x1 - centerX;
    int y = y1 - centerY;
    rotatedRect[0].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[0].y = (int)(x * sin30 + y * cos30) + centerY;
    // Правая верхняя точка
    x = x2 - centerX;
    y = y1 - centerY;
    rotatedRect[1].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[1].y = (int)(x * sin30 + y * cos30) + centerY;
    // Правая нижняя точка
    x = x2 - centerX;
    y = y2 - centerY;
    rotatedRect[2].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[2].y = (int)(x * sin30 + y * cos30) + centerY;
    // Левая нижняя точка
    x = x1 - centerX;
    y = y2 - centerY;
    rotatedRect[3].x = (int)(x * cos30 - y * sin30) + centerX;
    rotatedRect[3].y = (int)(x * sin30 + y * cos30) + centerY;

    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, rotatedRect, 4);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Прятанье фар
void LowRider::HideLights()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    RoundRect(hdc, X - width / 16, Y + height * 3 / 4, X + width / 4, Y + height / 2, width * 3 / 16, height / 4);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void LowRider::HideRoof()
{
}

void LowRider::HideWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 7;
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

//Класс

Gazel::Gazel(int initX, int initY, int initWidth, int initHeight) :CarBody(initX, initY, initWidth, initHeight)
{
    SetBaseRGB(60, 60, 60);
    SetAltRGB(0, 0, 0);
}

Gazel::~Gazel()
{
}

// Отрисовка окна
void Gazel::DrawWindow()
{
    POINT triangle[3];
    triangle[0].x = X;
    triangle[0].y = Y + height / 2;
    triangle[1].x = X + width / 3;
    triangle[1].y = Y + height / 2;
    triangle[2].x = X + width / 3;
    triangle[2].y = Y;
    HPEN Pen = CreatePen(PS_SOLID, 2, WINDOW_COLOR);
    HBRUSH hBrush = CreateSolidBrush(WINDOW_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, triangle, 3);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Отрисовка фар
void Gazel::DrawLights()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, LIGHTS_COLOR);
    HBRUSH hBrush = CreateSolidBrush(LIGHTS_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height * 23 / 32, X + width * 1 / 16, Y + height * 17 / 32);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Gazel::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y);
    Pen = CreatePen(PS_SOLID, 2, GetAltRGB());
    hBrush = CreateSolidBrush(GetAltRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y + height / 4);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Gazel::DrawWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 5;
    int diskRadius = width / 9;
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

// Прятанье основного тела машины
void Gazel::HideBody()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X, Y + height / 2, X + width, Y + height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Gazel::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}


// Отрисовка окна
void Gazel::HideWindow()
{
    POINT triangle[3];
    triangle[0].x = X;
    triangle[0].y = Y + height / 2;
    triangle[1].x = X + width / 3;
    triangle[1].y = Y + height / 2;
    triangle[2].x = X + width / 3;
    triangle[2].y = Y;
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, triangle, 3);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}


void Gazel::HideWheels()
{
    int posX = X + width / 4;
    int posY = Y + height;
    int tireRadius = width / 5;
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

/* ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ РАБОТЫ НЕВИРТУАЛЬНЫХ ФУНКЦИЙ */

void LowRider::Show()
{
    DrawBody();
    DrawParts();
}

void LowRider::Hide()
{
    HideBody();
    HideParts();
}

void LowRider::DrawParts()
{
    DrawRoof();
    DrawWindow();
    DrawLights();
    DrawWheels();
}

void LowRider::HideParts()
{
    HideWindow();
    HideLights();
    HideRoof();
    HideWheels();
}

void LowRider::MoveTo(int NewX, int NewY)
{
    Hide();
    X = NewX;
    Y = NewY;
    Show();
};

void LowRider::Drag(int Step)
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

void Gazel::Show()
{
    DrawBody();
    DrawParts();
}

void Gazel::Hide()
{
    HideBody();
    HideParts();
}

void Gazel::DrawParts()
{
    DrawRoof();
    DrawWindow();
    DrawLights();
    DrawWheels();
}

void Gazel::HideParts()
{
    HideWindow();
    HideLights();
    HideRoof();
    HideWheels();
}

void Gazel::MoveTo(int NewX, int NewY)
{
    Hide();
    X = NewX;
    Y = NewY;
    Show();
};

void Gazel::Drag(int Step)
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