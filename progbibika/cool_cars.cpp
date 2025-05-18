#include <windows.h>
#include "cool_cars.h"

extern HDC hdc;
extern World world;
extern Car* curCar;

#define CAR_CLASSES_QUANTITY 12
#define BUMP_CLASSES_QUANTITY 3

extern Car* cars_array[CAR_CLASSES_QUANTITY];
extern int car_migration[CAR_CLASSES_QUANTITY][BUMP_CLASSES_QUANTITY];
extern int startx;
extern int starty;

const COLORREF WINDOW_COLOR = RGB(0, 128, 168);
const COLORREF LIGHTS_COLOR = RGB(250, 250, 0);
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// конструктор
DoubleDeck::DoubleDeck(int initX, int initY, int initWidth, int initHeight) : Car(initX, initY, initWidth, initHeight)
{
    index = 5;
}

void DoubleDeck::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y-height, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

//прятанье крыши
void DoubleDeck::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 4, Y - height, X + width * 3 / 4, Y + height / 2);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// конструктор
DoubleDeckTireless::DoubleDeckTireless(int initX, int initY, int initWidth, int initHeight) : DoubleDeck(initX, initY, initWidth, initHeight)
{
    index = 6;
    PopulateParts();
}

void DoubleDeckTireless::PopulateParts()
{
    parts_quantity = 0;
}

// конструктор
CarTireThree::CarTireThree(int initX, int initY, int initWidth, int initHeight) : Car(initX, initY, initWidth, initHeight)
{
    index = 10;
    PopulateParts();
}

// Сбор основных частей машины, являющихся отдельными объектами
void CarTireThree::PopulateParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
    parts_quantity = 0;
    parts[parts_quantity++] = new Wheel(width / 4, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width / 2, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width * 3 / 4, height, width / 6, width / 12);
}

//Класс лоурайдер

LowRider::LowRider(int initX, int initY, int initWidth, int initHeight) :Car(initX, initY, initWidth, initHeight)
{
    index = 1; // присвоение индекса класса лоурайдера
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
    index = 2; // присвоение индекса класса газели
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

// конструктор
LowRiderTireless::LowRiderTireless(int initX, int initY, int initWidth, int initHeight) : LowRider(initX, initY, initWidth, initHeight)
{
    index = 3;
    PopulateParts();
}

// Сбор основных частей машины, являющихся отдельными объектами
void LowRiderTireless::PopulateParts()
{
    parts_quantity = 0;
}

// конструктор
LowRiderTireThree::LowRiderTireThree(int initX, int initY, int initWidth, int initHeight) : LowRider(initX, initY, initWidth, initHeight)
{
    index = 8;
    PopulateParts();
}

// Сбор основных частей машины, являющихся отдельными объектами
void LowRiderTireThree::PopulateParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
    parts_quantity = 0;
    parts[parts_quantity++] = new Wheel(width / 4, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width / 2, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width * 3 / 4, height, width / 6, width / 12);
}

// конструктор
GazelTireless::GazelTireless(int initX, int initY, int initWidth, int initHeight) : Gazel(initX, initY, initWidth, initHeight)
{
    index = 4;
    PopulateParts();
}

// Сбор основных частей машины, являющихся отдельными объектами
void GazelTireless::PopulateParts()
{
    parts_quantity = 0;
}

// конструктор
GazelTireThree::GazelTireThree(int initX, int initY, int initWidth, int initHeight) : Gazel(initX, initY, initWidth, initHeight)
{
    index = 9;
    PopulateParts();
}

// Сбор основных частей машины, являющихся отдельными объектами
void GazelTireThree::PopulateParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
    parts_quantity = 0;
    parts[parts_quantity++] = new Wheel(width / 4, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width / 2, height, width / 6, width / 12);
    parts[parts_quantity++] = new Wheel(width * 3 / 4, height, width / 6, width / 12);
}

// конструктор
GazelDD::GazelDD(int initX, int initY, int initWidth, int initHeight) : Gazel(initX, initY, initWidth, initHeight)
{
    index = 7;
}

void GazelDD::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y - height);
    Pen = CreatePen(PS_SOLID, 2, GetAltRGB());
    hBrush = CreateSolidBrush(GetAltRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y + height / 4);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void GazelDD::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 3, Y + height / 2, X + width, Y - height);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

//Конструктор
Truck::Truck(int InitX, int InitY, int initWidth, int initHeight) : Car(InitX, InitY, initWidth, initHeight)
{
    index = 11;
    width = initWidth * 2;
    PopulateParts();
    SetBaseRGB(255, 128, 0);
}

// Отрисовка окна
void Truck::DrawWindow() 
{
    POINT triangle[3];
    triangle[0].x = X;
    triangle[0].y = Y + height / 2;
    triangle[1].x = X + width / 3;
    triangle[1].y = Y + height / 2;
    triangle[2].x = X + width / 5;
    triangle[2].y = Y;
    HPEN Pen = CreatePen(PS_SOLID, 2, WINDOW_COLOR);
    HBRUSH hBrush = CreateSolidBrush(WINDOW_COLOR);
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, triangle, 3);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

void Truck::PopulateParts()
{
    for (int i = 0; i < parts_quantity; i++)
    {
        delete parts[i];
    }
    parts_quantity = 0;
    parts[parts_quantity++] = new Wheel(width / 8, height, width / 12, width / 24);
    parts[parts_quantity++] = new Wheel(width / 4, height, width / 12, width / 24);
    parts[parts_quantity++] = new Wheel(width * 3 / 4, height, width / 12, width / 24);
    parts[parts_quantity++] = new Wheel(width *7/8, height, width / 12, width / 24);
}

// Отрисовка фар
void Truck::DrawLights()
{

}

// Отрисовка крыши
void Truck::DrawRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, GetBaseRGB());
    HBRUSH hBrush = CreateSolidBrush(GetBaseRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 5, Y + height / 2, X + width/2, Y);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

// Прятанье окна
void Truck::HideWindow()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    POINT triangle[3];
    triangle[0].x = X;
    triangle[0].y = Y + height / 2;
    triangle[1].x = X + width / 3;
    triangle[1].y = Y + height / 2;
    triangle[2].x = X + width / 5;
    triangle[2].y = Y;
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Polygon(hdc, triangle, 3);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}
// Прятанье фар
void Truck::HideLights()
{

}

// Прятанье крыши
void Truck::HideRoof()
{
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255,255,255));
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, X + width / 5, Y + height / 2, X + width / 2, Y);
    DeleteObject(hBrush);
    DeleteObject(Pen);
}

//конструктор
Saw::Saw(int InitX, int InitY, int initWidth, int initHeight) : ABCWorldObject(InitX, InitY, initWidth, initHeight)
{
    index = 0;
}

void Saw::Show() {
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    // Основная линия пилы (горизонтальная)
    MoveToEx(hdc, X, Y + height, NULL);
    LineTo(hdc, X + width, Y + height);

    // Зубцы пилы
    int toothWidth = width / 10;
    for (int i = 0; i < 10; i++) {
        int startX = X + i * toothWidth;
        if (i % 2 == 0) {
            // Верхний зубец
            MoveToEx(hdc, startX, Y + height, NULL);
            LineTo(hdc, startX + toothWidth / 2, Y);
            LineTo(hdc, startX + toothWidth, Y + height);
        }
    }
}

void Saw::Hide() {
    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(WHITE_PEN));

    // Закрашиваем основную линию пилы (прямоугольник вокруг линии)
    Rectangle(hdc, X, Y - height / 2 - 2, X + width, Y + height / 2 + 2);

    // Закрашиваем зубцы пилы
    int toothWidth = width / 10;
    for (int i = 0; i < 10; i++) {
        int startX = X + i * toothWidth;
        if (i % 2 == 0) {
            // Закрашиваем треугольник зубца
            POINT triangle[3] = {
                {startX, Y - height / 2},
                {startX + toothWidth / 2, Y},
                {startX + toothWidth, Y - height / 2}
            };
            Polygon(hdc, triangle, 3);
        }
    }
}

// действие, вызывающееся в момент аварии
void Saw::bump_action(ABCWorldObject* bumpedOne)
{
    //проверка является ли столкнувшийся объект, объектом подходящим для взаимодействия
    if (bumpedOne != curCar)
        return;
    //прячем старую машину
    bumpedOne->MoveTo(startx, starty);
    bumpedOne->Hide();
    //удаление из списка объектов для столкновеня
    world.findndelete(bumpedOne);
    //переназначение указателя на новую машину
    curCar = cars_array[car_migration[curCar->GetIndex()][index]];
    curCar->Show();
    Show();
    curCar->Drag(40);
};

Roof::Roof(int InitX, int InitY, int initWidth, int initHeight) : Saw(InitX, InitY, initWidth, initHeight)
{
    index = 1;
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

//конструктор
ExtraTire::ExtraTire(int InitX, int InitY, int initWidth, int initHeight) : Saw(InitX, InitY, initWidth, initHeight)
{
    index = 2;
}

void ExtraTire::Show() {
    Visible = true;
    HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X - width/2, Y - width/2, X + width/2, Y + width/2);
    DeleteObject(Pen);
    DeleteObject(hBrush);
    Pen = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
    hBrush = CreateSolidBrush(RGB(128, 128, 128));
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X - width/4, Y - width/4, X + width/4, Y + width/4);
    DeleteObject(Pen);
    DeleteObject(hBrush);
}

void ExtraTire::Hide() {
    Visible = false;
    HPEN Pen = CreatePen(PS_SOLID, 2, GetHideRGB());
    HBRUSH hBrush = CreateSolidBrush(GetHideRGB());
    SelectObject(hdc, Pen);
    SelectObject(hdc, hBrush);
    Ellipse(hdc, X - width/2, Y - width/2, X + width/2, Y + width/2);
    DeleteObject(Pen);
}