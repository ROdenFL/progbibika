#pragma once
#include <windows.h>
class World;
/******************************************************************/
/*                  Т И П Ы    Д А Н Н Ы Х                        */
/******************************************************************/

/*------------------  Класс МЕСТОПОЛОЖЕНИЕ ----------------------*/
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

/*------------------  Класс ТОЧКА -------------------------------*/
class Point : public Location
{
protected:
    bool Visible;
    //Основной цвет объекта
    int baseRGB[3] = { 255, 0, 0 };
    //Цвет спрятанного объекта
    int hideRGB[3] = { 255, 255, 255 };
    
public:
    Point(int InitX, int InitY); // конструктор
    ~Point(); //деконструктор     
    bool GetVisible(); //геттер для Visible    
    void SetVisible(bool NewVisible); //сеттер для Visible 
    COLORREF GetBaseRGB(); //геттер основного цвета объекта
    COLORREF GetHideRGB(); //геттер цвета спрятонного объекта
    void SetBaseRGB(int R, int G, int B); // сеттер основного цвета объекта
    void SetHideRGB(int R, int G, int B); // сеттер цвета спрятонного объекта
    void Drag(int Step); // функция перемещения объекта на стрелки
    
    virtual void MoveTo(int NewX, int NewY);
    virtual void Show();
    virtual void Hide(); 
};

//объект столкновения
class ABCWorldObject : public Point
{
protected:
    int width = 0; //ширина
    int height = 0; //длина
public:
    ABCWorldObject(int InitX, int InitY, int initWidth, int initHeight); // конструктор
    ~ABCWorldObject(); //деконструктор 
    virtual void bump_action(ABCWorldObject* bumpedOne) = 0; // действие, вызывающееся в момент аварии
    void MoveTo(int NewX, int NewY); // перегрузка MoveTo для объектов столкновения

    int GetWidth(); // гетер для ширины
    int GetHeight(); // гетер для высоты 
};