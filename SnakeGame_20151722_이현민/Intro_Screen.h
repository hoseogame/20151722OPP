#pragma once
#include "Game_Screen.h"

class Intro_Screen : public Game_Screen
{
private:
	int width, high;
	int speed;
public:
	//GameScene�� ��ӹ��� �κ�
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Intro_Screen();

};