#include <windows.h>
#include <iostream>
using namespace std;

#include "world.h"
#include "cool_cars.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/***********************************************************************/
/*   Г Л О Б А Л Ь Н Ы Е   К О Н С Т А Н Т Ы  И  П Е Р Е М Е Н Н Ы Е   */
/***********************************************************************/

HDC hdc;
World world;

/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
int main()
{
    int x0 = 200;
    int y0 = 200;

    HWND hwnd = GetConsoleWindow();

    //если дескриптор НЕ существует
    if (hwnd == NULL)
    {
        cout << "Console Window Descriptor NOT FOUND !\n";
        return 1;
    }

    hdc = GetWindowDC(hwnd);

    //если контекст НЕ существует
    if (hdc == 0)
    {
        cout << "Handle Device Context NOT FOUND !\n";
        return 2; 
    }

    CarBody *car1 = new CarBody(x0, y0);

    Saw car2(600, 200, 200, 200);
    world.add_object(car1);
    world.add_object(& car2);
    car1->Show();
    car2.Show();

    cout << "/Press 1  \7";
    while (1)
        if (KEY_DOWN(49)) //цифра 1
            break;

    cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    car1->Drag(40);  //буксировка ТОЧКИ  Выход - Esc
    cout << "/Press 2   \7";
    while (1)
        if (KEY_DOWN(50)) //цифра 2
            break;
    car1->Hide();

    return 0;
}


