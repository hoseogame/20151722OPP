#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "Field.h"
#include "Wall.h"
#include "Item.h"
#include "Snake.h"
#include "Input.h"
#include "Gotoxy.h"

using namespace std;

Field* Field::instnace = new Field();

Field::Field() :
Walls(nullptr), Heart(nullptr), snake(nullptr),
width(0), hight(0), wallsCount(0), score(0),
isWallsDraw(false), isHaertDraw(false), isMenuDraw(false)
{
}

Field::~Field()
{
	if (Walls)
		delete[]Walls;
	if (Heart)
		delete Heart;
	if (snake)
		delete snake;
}

Field*  Field::GetInstance()
{
	if (instnace)
		return instnace;
	else
	{
		instnace = new Field();
		return instnace;
	}
}

void Field::ReleaseInstace()
{
	if (instnace)
		delete instnace;
}

bool Field::CollisionCheck()
{
	//벽과 뱀의 머리 체크
	for (int i = 0; i < wallsCount; i++)
	{
		if (CompareRect(Walls[i].GetX(), snake->GetBodys()[0].GetX(),
			Walls[i].GetY(), snake->GetBodys()[0].GetY()))
		{
			return false;
		}
	}

	//뱀과 하트 아이템 체크
	if (Heart)
	{
		if (CompareRect(snake->GetBodys()[0].GetX(), Heart->GetX(),
			snake->GetBodys()[0].GetY(), Heart->GetY()))
		{
			snake->AddTail();
			score += 100;
			delete Heart;
			Heart = nullptr;
			isHaertDraw = false;
			isMenuDraw = false;
		}
	}

	//내 몸통에 부딛치는 경우 체크
	for (int i = 0; i < snake->GetSize() - 1; i++)
		for (int j = i + 1; j < snake->GetSize() - 1; j++)
			if (CompareRect(snake->GetBodys()[i].GetX(), snake->GetBodys()[j].GetX(),
				snake->GetBodys()[i].GetY(), snake->GetBodys()[j].GetY()))
				return false;

	return true;
}

bool Field::CompareRect(int x1, int x2, int y1, int y2)
{
	if ((x1 == x2) && (y1 == y2))
		return true;
	else
		return false;
}

void Field::SetWalls(int width, int hight)
{
	wallsCount = (width + hight - 2) * 2;
	Walls = new Wall[wallsCount];

	this->width = width;
	this->hight = hight;

	int index = 0;

	for (int w = 0; w < width; w++, index++)
		Walls[index].SetPotion(w * 2, 0);

	for (int w = 0; w < width; w++, index++)
		Walls[index].SetPotion(w * 2, hight - 1);

	for (int h = 1; h < hight - 1; h++, index++)
		Walls[index].SetPotion(0, h);

	for (int h = 1; h < hight - 1; h++, index++)
		Walls[index].SetPotion((width - 1) * 2, h);

}

void Field::SetItems()
{
	if (Heart)
		return;

	srand(time(NULL));
	int x = ((rand() % (width - 2)) + 2) * 2;
	int y = rand() % (hight - 2) + 2;

	Heart = new Item(x, y);
}

void Field::SetSnake()
{
	if (snake)
		return;

	snake = new Snake(width, hight / 2);
}

void Field::UpdateSnake()
{
	snake->UpdateTail();
	Input::KeyInput(snake);
}

void Field::RenderObjects()
{
	// 벽은 딱 한번만 그리면 된다.
	if (!isWallsDraw)
	{
		for (int i = 0; i < wallsCount; i++)
		{
			gotoxy(Walls[i].GetX(), Walls[i].GetY());
			cout << Walls[i].GetShape();
		}

		isWallsDraw = true;
	}

	if (Heart && !isHaertDraw)
	{
		gotoxy(Heart->GetX(), Heart->GetY());
		cout << Heart->GetShape();

		isHaertDraw = true;
	}

	if (snake)
	{
		for (int i = 0; i < snake->GetSize(); i++)
		{
			gotoxy(snake->GetBodys()[i].GetX(), snake->GetBodys()[i].GetY());
			cout << snake->GetBodys()[i].GetShape();
		}
	}
	if (!isMenuDraw)
	{
		gotoxy((width * 2) + 2, 2);
		cout << "만든이 : 이현민";
		gotoxy((width * 2) + 2, 3);
		cout << "맵크기 : " << width << "  *  " << hight;;
		gotoxy((width * 2) + 2, 4);
		cout << "점수 : " << score;
		isMenuDraw = true;
	}
}