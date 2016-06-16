#include <iostream>
#include "Snake_Game.h"
#include "Gotoxy.h"

using namespace std;

int Snakemain(void)
{
	Snake_Game EX;
	EX.Init();
	EX.Update();
	EX.Release();



	return 0;
}