#include <iostream>
#include "Intro_Screen.h"
#include "Snake_Game.h"
#include "Main_Screen.h"
#include <Windows.h>

using namespace std;

Intro_Screen::Intro_Screen() : width(0), high(0), speed(0)
{}

void Intro_Screen::Init()
{

	while (width < 10 || width > 30 || high < 10 || high > 30 || width & 1 || high & 1)
	{
		cout << "===============================================================================" << endl;
		cout << "===================S===N===A===K===E===G===A===M===E==========================="<< endl;
		cout << "                   ---------------------------------" << endl << endl;
		cout << "\t맵의 크기를 입력하세요(짝수로 10 * 10 이상 , 30 * 30 이하)" << endl;
		cout << "\n WIDTH >> ";
		cin >> width;
		cout << " HIGH  >> ";
		cin >> high;

		system("cls");
	}

	cout << "===============================================================================" << endl;
	cout << "===================S===N===A===K===E===G===A===M===E===========================" << endl;
	cout << "                   ---------------------------------" << endl << endl;
	cout << "\t\t1~16까지 스피드를 설정해주세요 (클스록 느립니다)" << endl;
	cout << "\n  >>";

	while (speed < 1 || speed > 16)
	{
		cin >> speed;
		system("cls");
	}
}
bool Intro_Screen::Update()
{
	Render();
	return true;
}
void Intro_Screen::Render()
{
	system("cls");
}
void Intro_Screen::Release()
{
	system("cls");
	Snake_Game::setScene(new Main_Screen(width, high, speed * 25));
}