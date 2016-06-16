#include "End_Screen.h"
#include <iostream>
#include <Windows.h>

using namespace std;

End_Screen::End_Screen(int _w, int _h, int _speed, int _socre) :
width(_w), high(_h), speed(_speed), score(_socre)
{}

void End_Screen::Init()
{
	system("cls");
}
bool End_Screen::Update()
{
	cout << "에엑... 죽으셨네요 화이팅!" << endl;
	cout << "가로 세로 : " << width << " " << high << endl;
	cout << "속도 : " << speed << endl;
	cout << "점수 : " << score << endl;
	cout << "Metacritic : 100 " << endl;
	Sleep(2500);
	Render();
	return false;
}
void End_Screen::Render()
{
	system("cls");
	cout << "The End" << endl;
}
void End_Screen::Release()
{
}