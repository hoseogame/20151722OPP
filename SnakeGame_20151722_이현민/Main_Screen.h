#pragma once
#include "Game_Screen.h"


class Main_Screen : public Game_Screen
{
private:
	bool gameOver;
	int width, high;
	int speed;
public:
	//GameScene로 상속받은 부분
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Main_Screen(int _w, int _h, int _s);
};
