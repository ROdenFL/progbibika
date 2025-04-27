#include <windows.h>
#include "cool_cars.h"

extern HDC hdc;
extern World world;
extern Car* curCar;

const COLORREF WINDOW_COLOR = RGB(0, 128, 168);
const COLORREF LIGHTS_COLOR = RGB(250, 250, 0);
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//Класс лоурайдер

LowRider::LowRider(int initX, int initY, int initWidth, int initHeight) :Car(initX, initY, initWidth, initHeight)
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

//Класс

Gazel::Gazel(int initX, int initY, int initWidth, int initHeight) :Car(initX, initY, initWidth, initHeight)
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

Saw::Saw(int InitX, int InitY, int initWidth, int initHeight) : BumpObject(InitX, InitY) 
{
    width = initWidth;
    height = initHeight;
}

void Saw::bump_action(BumpObject* bumpedOne)
{
    // Создаем LowRider на месте машины
    LowRider* lowRider = new LowRider(bumpedOne->GetX(), bumpedOne->GetY(),
        bumpedOne->GetWidth(), bumpedOne->GetHeight());
    world.add_object(lowRider);
    bumpedOne->Hide();
    Hide();
    world.findndelete(bumpedOne);
    world.findndelete(this);
    curCar = lowRider;
    lowRider->Show();
    lowRider->Drag(40);
}

void Saw::Show() {
    // Основная линия пилы (горизонтальная)
    MoveToEx(hdc, X, Y + height / 2, NULL);
    LineTo(hdc, X + width, Y + height / 2);

    // Зубцы пилы
    int toothWidth = width / 10;
    for (int i = 0; i < 10; i++) {
        int startX = X + i * toothWidth;
        if (i % 2 == 0) {
            // Верхний зубец
            MoveToEx(hdc, startX, Y + height / 2, NULL);
            LineTo(hdc, startX + toothWidth / 2, Y);
            LineTo(hdc, startX + toothWidth, Y + height / 2);
        }
    }
}

void Saw::Hide() {
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(WHITE_PEN));

    // Закрашиваем основную линию пилы (прямоугольник вокруг линии)
    Rectangle(hdc, X, Y + height / 2 - 2, X + width, Y + height / 2 + 2);

    // Закрашиваем зубцы пилы
    int toothWidth = width / 10;
    for (int i = 0; i < 10; i++) {
        int startX = X + i * toothWidth;
        if (i % 2 == 0) {
            // Закрашиваем треугольник зубца
            POINT triangle[3] = {
                {startX, Y + height / 2},
                {startX + toothWidth / 2, Y},
                {startX + toothWidth, Y + height / 2}
            };
            Polygon(hdc, triangle, 3);
        }
    }
}

Roof::Roof(int InitX, int InitY, int initWidth, int initHeight) : BumpObject(InitX, InitY)
{
    width = initWidth;
    height = initHeight;
}

void Roof::bump_action(BumpObject* bumpedOne)
{
    Gazel* gazel = new Gazel(bumpedOne->GetX(), bumpedOne->GetY(),
        bumpedOne->GetWidth(), bumpedOne->GetHeight());
    world.add_object(gazel);
    bumpedOne->Hide();
    Hide();
    world.findndelete(bumpedOne);
    world.findndelete(this);
    curCar = gazel;
    gazel->Show();
    gazel->Drag(40);
}


void Roof::Show()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);

    Rectangle(hdc, X, Y + height, X + width / 2, Y + height / 2);

    POINT triangle[3] = {
        {X + width / 2, Y + height / 2},
        {X + width / 2, Y + height},
        {X + width, Y + height}
    };
    Polygon(hdc, triangle, 3);
}

void Roof::Hide()
{
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(WHITE_PEN));

    // Стираем квадрат
    Rectangle(hdc, X, Y, X + width / 2, Y + height / 2);

    // Стираем треугольник (координаты те же, что и в Show)
    POINT triangle[3] = {
        {X + width / 2, Y + height / 2},
        {X + width / 2, Y + height},
        {X + width, Y + height}
    };
    Polygon(hdc, triangle, 3);
}