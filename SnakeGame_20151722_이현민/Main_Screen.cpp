#include <iostream>
#include <Windows.h>
#include "Main_Screen.h"
#include "Snake_Game.h"
#include "End_Screen.h"
#include "Field.h"

using namespace std;

Main_Screen::Main_Screen(int _w, int _h, int _s) :
Game_Screen(), gameOver(true), width(_w), high(_h), speed(_s)
{}

void Main_Screen::Init()
{
	Field::GetInstance()->SetWalls(width, high);
	Field::GetInstance()->SetSnake();
}
bool Main_Screen::Update()
{
	while (gameOver)
	{
		Field::GetInstance()->SetItems();
		Field::GetInstance()->UpdateSnake();
		Main_Screen::Render();
		gameOver = Field::GetInstance()->CollisionCheck();
		Sleep(speed);
	}

	return true;
}
void Main_Screen::Render()
{
	Field::GetInstance()->RenderObjects();
}
void Main_Screen::Release()
{
	Snake_Game::setScene(new End_Screen(width, high, speed, Field::GetInstance()->GetCcore() / 25));
	Field::ReleaseInstace();
}