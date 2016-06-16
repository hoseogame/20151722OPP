#pragma once
class Object;
class Snake;

class Field
{
private:
	explicit Field();
	~Field();
	Field(const Field&);
	Field& operator=(const Field&);

private:
	static Field* instnace;
	Object* Walls;
	Object* Heart;
	Snake* snake;
	int width, hight;
	int wallsCount;
	int score;
	bool isWallsDraw;
	bool isHaertDraw;
	bool isMenuDraw;

public:
	static Field* GetInstance();
	static void ReleaseInstace();

	bool CollisionCheck();
	bool CompareRect(int x1, int x2, int y1, int y2);
	void SetWalls(int width, int hight);
	void SetItems();
	void SetSnake();
	void UpdateSnake();
	void RenderObjects();
	inline int GetCcore()
	{
		return score;
	}
};