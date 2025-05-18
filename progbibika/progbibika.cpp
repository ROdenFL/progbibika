#include <windows.h>
#include <iostream>
using namespace std;

#include "world.h"
#include "cool_cars.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/***********************************************************************/
/*   Г Л О Б А Л Ь Н Ы Е   К О Н С Т А Н Т Ы  И  П Е Р Е М Е Н Н Ы Е   */
/***********************************************************************/

#define CAR_CLASSES_QUANTITY 12
#define BUMP_CLASSES_QUANTITY 3

HDC hdc;
//Переменная, учитывающая все объекты, которые могут участвовать в столконовениях
World world;
//Глобальный указатель на машину, с которым взайимодействуют функции мейна
Car* curCar;

int startx = 100;
int starty = 100;

Car car(startx, starty, 150, 100);
LowRider lowrider(startx, starty, 150, 100);
Gazel gazel(startx, starty, 150, 100);
LowRiderTireless lowriderTireless(startx, starty, 150, 100);
GazelTireless gazelTireless(startx, starty, 150, 100);
DoubleDeck doubledeck(startx, starty, 150, 100);
DoubleDeckTireless doubledecktireless(startx, starty, 150, 100);
GazelDD gazeldd(startx, starty, 150, 100);
LowRiderTireThree lowrider3t(startx, starty, 150, 100);
GazelTireThree gazel3t(startx, starty, 150, 100);
CarTireThree car3t(startx, starty, 150, 100);
Truck truck(startx, starty, 150, 100);

Car* cars_array[CAR_CLASSES_QUANTITY] = { &car, &lowrider, &gazel, &lowriderTireless, &gazelTireless
                                        , &doubledeck, &doubledecktireless, &gazeldd, &lowrider3t, &gazel3t, &car3t, &truck};
int car_migration[CAR_CLASSES_QUANTITY][BUMP_CLASSES_QUANTITY] =
{
    {1, 5, 10},//Car
    {3, 2, 8},//LowRider
    {1, 7, 9},//Gazel
    {3, 4, 1},//LowRiderTireless
    {3, 4, 2},//GazelTireless
    {0, 5, 5},//DoubleDeck
    {1, 6, 5},//DoubleDeckTireless
    {2, 7, 11},//GazelDD
    {1, 9, 8},//LowRiderTireThree
    {2, 11, 9},//GazelTireThree
    {0, 10, 10},//CarTireThree
    {2, 11, 11},//Truck
};
//Динамический массив (указатели на строки conflict_result_stat)
int** dym_migration = new int* [CAR_CLASSES_QUANTITY];

/***********************************************************************/
/*               О С Н О В Н А Я    П Р О Г Р А М М А                  */
/***********************************************************************/
int main()
{
    HWND hwnd = GetConsoleWindow();

    for (int i(0); i < CAR_CLASSES_QUANTITY; i++) {
        dym_migration[i] = car_migration[i];
    }

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
    //создание базового экземпляра класса
    curCar = cars_array[0];

    //создание объектов для столкновения
    Saw saw(600, 100, 100, 50);
    Roof roof(600, 200, 100, 100);
    ExtraTire tire(650, 400, 100, 100);
    Car car(800, 200, 150, 100);
    //добавление всех объектов в "мир" для учета в столкновениях
    world.add_object(curCar);
    world.add_object(&saw);
    world.add_object(&roof);
    world.add_object(&tire);
    world.add_object(&car);
    //отображение всех объектов
    curCar->Show();
    saw.Show();
    roof.Show();
    tire.Show();
    car.Show();

    cout << "/Press 1  \7";
    while (1)
        if (KEY_DOWN(49)) //цифра 1
            break;

    cout << "/Press Arrow UP, DOOWN, LEFT, RIGTH  Esc - exit  \7";
    curCar->Drag(40);  //буксировка ТОЧКИ  Выход - Esc

    return 0;
}


