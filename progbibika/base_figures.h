#pragma once
#include <windows.h>
class World;
/******************************************************************/
/*                  “ » œ €    ƒ ¿ Õ Õ € ’                        */
/******************************************************************/

/*------------------   Î‡ÒÒ Ã≈—“ŒœŒÀŒ∆≈Õ»≈ ----------------------*/
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

/*------------------   Î‡ÒÒ “Œ◊ ¿ -------------------------------*/
class Point : public Location
{
protected:
    bool Visible;
    int baseRGB[3] = { 255, 0, 0 };
    int hideRGB[3] = { 0, 0, 255 };
    World* world;
public:
    Point(int InitX, int InitY);
    ~Point();                   
    bool GetVisible();               
    void SetVisible(bool NewVisible);
    COLORREF GetBaseRGB();
    COLORREF GetHideRGB();
    void SetBaseRGB(int R, int G, int B);
    void SetHideRGB(int R, int G, int B);
    void SetWorld(World* newWorld);
    virtual void MoveTo(int NewX, int NewY);
    void Drag(int Step);
    virtual void Show();
    virtual void Hide(); 
};