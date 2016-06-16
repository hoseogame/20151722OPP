#pragma once

class Game_Screen
{
private:
	Game_Screen(const Game_Screen& GS);
	Game_Screen& operator=(const Game_Screen& GS);

public:
	explicit Game_Screen();
	virtual ~Game_Screen();

	virtual void Init() = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;
	virtual void Release() = 0;
};