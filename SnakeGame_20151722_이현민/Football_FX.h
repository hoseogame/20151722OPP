#pragma once
#ifndef _FOOTBALL_FX_H_
#define  _FOOTBALL_FX_H_

#include"Football.h"
#include"Football_Screen.h"

class Football_FX :public Football
{
public:
	Football_FX();

	void Init();
	void Update();
	void Render();
	void Release();
	void input();
public:
	F_Screen screen;
	Football Football;
};

#endif