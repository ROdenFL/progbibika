#include <windows.h>
#include <iostream>
using namespace std;

#include "world.h"

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
    int x0 = 300;
    int y0 = 300;

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

    CarBody car1(200, 200);
    CarBody car2(600, 200);
    world.add_car(&car1);
    car1.Show();
    world.add_car(&car2);
    car2.Show();

    cout << "/Press 1  \7";
    while (1)
        if (KEY_DOWN(49)) //цифра 1
            break;

    cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    car1.Drag(40);  //буксировка ТОЧКИ  Выход - Esc
    cout << "/Press 2   \7";
    while (1)
        if (KEY_DOWN(50)) //цифра 2
            break;

    ////**********  КРУГ  ***************
    //Circle ACircle(x0, y0, Radius0); //инициализация КРУГА

    //ACircle.Show();   //показать КРУГ
    ////переместить КРУГ по вертикали вниз
    //ACircle.MoveTo(x0, y0 + 2 * Radius0);
    //cout << "/Press 3  \7";
    //while (1)
    //    if (KEY_DOWN(51)) //цифра 3
    //        break;

    //ACircle.Expand(DeltaRad); //увеличить радиус КРУГА

    //cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    //ACircle.Drag(50); //буксировка КРУГА  Выход - Esc

    //ACircle.Reduce(DeltaRad); //уменьшить радиус КРУГА
    //cout << "/Press 4  \7";
    //while (1)
    //    if (KEY_DOWN(52)) //цифра 4
    //        break;

    ////**********  КОЛЬЦО  ***************
    //Ring ARing(x0, 2 * y0, Radius0, RingW0);
    //ARing.Show();   //показать КОЛЬЦО
    //cout << "/Press 5  \7";
    //while (1)
    //    if (KEY_DOWN(53)) //цифра 5
    //        break;

    //cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    //ARing.Drag(40);  //буксировка КОЛЬЦА  Выход - Esc
    //cout << "/Press 6  \7";
    //while (1)
    //    if (KEY_DOWN(54)) //цифра 6
    //        break;

    //ARing.Hide();  //спрятать КОЛЬЦО
    //cout << "/Press 7  \7";
    //while (1)
    //    if (KEY_DOWN(55))   //цифра 7
    //        break;

    //ARing.Expand(2 * DeltaRad);//увеличить радиус КОЛЬЦА на 2*DeltaRad

    //cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    //ARing.Drag(80);  //буксировка КОЛЬЦА  Выход - Esc
    //cout << "/Press 8  \7";
    //while (1)
    //    if (KEY_DOWN(56)) //цифра 8
    //        break;

    //ARing.Reduce(DeltaRad);//уменьшить радиус КОЛЬЦА на DeltaRad
    //cout << "/Press 9     \7";
    //while (1)
    //    if (KEY_DOWN(57)) //цифра 9
    //        break;

    //cout << "/Press +  Esc exit  \7";
    //ARing.Wide(10);   //увеличить толщину КОЛЬЦА Серый +, Esc
    //Sleep(1000);

    //cout << "/Press -  Esc exit  \7";
    //ARing.Slim(10);   //уменьшить толщину КОЛЬЦА Серый -, Esc

    //cout << "/Press 0     \7";
    //while (1)
    //    if (KEY_DOWN(48)) //цифра 0
    //        break;

    //cout << "\nExample ExOOP_05 DONE   \7\n";

    return 0;
}


