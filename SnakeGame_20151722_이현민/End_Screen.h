#pragma once
#include "Game_Screen.h"


class End_Screen : public Game_Screen
{
private:
	int width, high;
	int speed;
	int score;

public:
	//GameScene로 상속받은 부분
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit End_Screen(int _w, int _h, int _speed, int _socre);
};