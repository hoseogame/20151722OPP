#include"Football.h"
#include"Football_FX.h"
#include"Football_Screen.h"

#include <iostream>
#include "Snake_Game.h"
#include "Gotoxy.h"


using namespace std;

void main()
{
	int a;
	cout << "1 : 축구 // 2 : 스네이크" << endl << ">>";
	cin >> a;

	if (a == 1)
		Football_FX football_game;

	else if (a == 2)
	{
		Snake_Game EX;
		EX.Init();
		EX.Update();
		EX.Release();
	}

	else
	{
		cout << "잘못된 숫자입니다..." << endl;
		exit(0);
	}

}