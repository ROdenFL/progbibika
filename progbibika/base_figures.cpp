#include <windows.h>
#include "base_figures.h"

/***********************************************************************/
/*   � � � � � � � � � �   � � � � � � � � �  �  � � � � � � � � � �   */
/***********************************************************************/
#define CAR_CLASSES_QUANTITY 12
#define BUMP_CLASSES_QUANTITY 3

extern HDC hdc;    
extern World world;
extern Car* curCar;
extern Car* cars_array[CAR_CLASSES_QUANTITY];
extern int car_migration[CAR_CLASSES_QUANTITY][BUMP_CLASSES_QUANTITY];
extern int startx;
extern int starty;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*----------------------------------------------------------------*/
/*             � � � � � � � � � �    � � � � � � �               */
/*----------------------------------------------------------------*/

/*----------------------------------------*/
/*        ������ ������ Location          */
/*----------------------------------------*/
Location::Location(int InitX, int InitY)
{
    X = InitX;
    Y = InitY;
};

Location::~Location(void)  
{
};

int Location::GetX(void)
{
    return X;
};

int Location::GetY(void)
{
    return Y;
};

/*----------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
    Visible = false;
}

Point::~Point(void)  
{
}

COLORREF Point::GetBaseRGB()
{
    return RGB(baseRGB[0], baseRGB[1], baseRGB[2]);
}

COLORREF Point::GetHideRGB()
{
    return RGB(hideRGB[0], hideRGB[1], hideRGB[2]);
}

void Point::SetBaseRGB(int R, int G, int B)
{
    baseRGB[0] = R;
    baseRGB[1] = G;
    baseRGB[2] = B;
}

void Point::SetHideRGB(int R, int G, int B)
{
    hideRGB[0] = R;
    hideRGB[1] = G;
    hideRGB[2] = B;
}

void Point::Show(void)
{
    Visible = true;
    SetPixel(hdc, X, Y, GetBaseRGB());
    SetPixel(hdc, X + 1, Y, GetBaseRGB());
    SetPixel(hdc, X, Y + 1, GetBaseRGB());
    SetPixel(hdc, X + 1, Y + 1, GetBaseRGB());
}

void Point::Hide(void)
{
    Visible = false;

    SetPixel(hdc, X, Y, GetHideRGB());
    SetPixel(hdc, X + 1, Y, GetHideRGB());
    SetPixel(hdc, X, Y + 1, GetHideRGB());
    SetPixel(hdc, X + 1, Y + 1, GetHideRGB());
}

bool Point::GetVisible()
{
    return Visible;
}

void Point::SetVisible(bool NewVisible)
{
    Visible = NewVisible;
}

void Point::MoveTo(int NewX, int NewY)
{
    Hide();
    X = NewX;
    Y = NewY;
    Show();
};

void Point::Drag(int Step)
{
    int FigX, FigY;

    FigX = GetX();
    FigY = GetY();

    while (true)
    {
        if (KEY_DOWN(VK_ESCAPE)) 
            break;

        if (KEY_DOWN(VK_LEFT))
        {
            FigX -= Step;
            MoveTo(FigX, FigY);
            Sleep(100);
        }

        if (KEY_DOWN(VK_RIGHT))
        {
            FigX += Step;
            MoveTo(FigX, FigY);
            Sleep(100);
        }

        if (KEY_DOWN(VK_UP))
        {
            FigY -= Step;
            MoveTo(FigX, FigY);
            Sleep(100);
        }

        if (KEY_DOWN(VK_DOWN))
        {
            FigY += Step;
            MoveTo(FigX, FigY);
            Sleep(100);
        }

    }   
}


// �����������
ABCWorldObject::ABCWorldObject(int InitX, int InitY, int initWidth, int initHeight) : Point(InitX, InitY)
{
    width = initWidth;
    height = initHeight;
};

ABCWorldObject::~ABCWorldObject() {}; //������������� 

//������ ������
int ABCWorldObject::GetWidth()
{
    return width;
}

//������ �����
int ABCWorldObject::GetHeight()
{
    return height;
}

//MoveTo � ��������� ������������
void ABCWorldObject::MoveTo(int NewX, int NewY)
{
    Hide();
    X = NewX;
    Y = NewY;
    Show();
    world.check_bump(this); //�������� ������������
};
