#include "Snake_Game.h"
#include "Intro_Screen.h"

Game_Screen* Snake_Game::GS;

Snake_Game::Snake_Game() : Game_Screen(), isGameRun(true)
{}

Snake_Game::~Snake_Game()
{}

void Snake_Game::Init()
{
	setScene(nullptr);
}

bool Snake_Game::Update()
{
	if (!GS)
		return false;

	while (isGameRun)
	{
		GS->Init();
		isGameRun = GS->Update();
		GS->Release();
	}

	return true;
}
void Snake_Game::Render()
{ }

void Snake_Game::Release()
{
	delete GS;
}

void Snake_Game::setScene(Game_Screen* cur)
{
	if (GS == nullptr)
		GS = new Intro_Screen();
	else if (cur != nullptr)
	{
		delete GS;
		GS = cur;
	}
}