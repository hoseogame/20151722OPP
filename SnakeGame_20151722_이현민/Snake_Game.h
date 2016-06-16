#pragma once
#include "Game_Screen.h"


class Snake_Game : public Game_Screen
{
private:
	static Game_Screen* GS;
	bool isGameRun;
public:
	//GameScene�� ��ӹ��� �κ�
	void Init() override;
	bool Update() override;
	void Render() override;
	void Release() override;

public:
	explicit Snake_Game();
	~Snake_Game();

	static void setScene(Game_Screen* cur);

};
