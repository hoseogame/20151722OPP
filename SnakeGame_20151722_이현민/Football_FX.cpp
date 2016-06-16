#include"Football_FX.h"

Football_FX::Football_FX()
{
	Init();
	input();
}

void Football_FX::Init()
{
	int nLength, i;

	if (g_nStage == -1)
	{

		g_nStage = 0;

	}

	g_LimitTime = g_sStageInfo[g_nStage].LimitTime;  // ���� �ð� ����
	g_nGoalBallCount = g_sStageInfo[g_nStage].nGoalBall; // ��ǥ ���� ����

	g_sPlayer.nCenterX = 4;
	g_sPlayer.nCenterY = 0;
	g_sPlayer.nMoveX = 20;
	g_sPlayer.nMoveY = 22;
	g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
	g_nLength = strlen(g_strPlayer);

	// ���� �ʱ�ȭ
	g_sBall.nIsReady = 1;
	g_sBall.nMoveX = g_sPlayer.nMoveX;
	g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
	g_sBall.MoveTime = 100;

	// ��� �ʱ�ȭ
	g_sGoalDae.nMoveX = g_sStageInfo[g_nStage].nGoalDaeX;
	g_sGoalDae.nMoveY = g_sStageInfo[g_nStage].nGoalDaeY;
	g_sGoalDae.nLength = g_sStageInfo[g_nStage].nGoalDaeLength;
	g_sGoalDae.MoveTime = g_sStageInfo[g_nStage].MoveTime;
	g_sGoalDae.OldTime = clock();
	g_sGoalDae.nDist = g_sStageInfo[g_nStage].nDist;
	nLength = g_sGoalDae.nLength * 2 + 1; // Note: �迭�� �ִ� ����

	for (i = 0; i < nLength; i++)
	{
		g_sGoalDae.nLineX[i] = g_sGoalDae.nMoveX + 2 * (i + 1);
	}

	// ȿ�� 
	g_sEffect.StayTime = 2000; // 2�� ����
	g_nGoal = 0;      // �������� �Ϸ� ����
	g_UpdateOldTime = clock();
	g_nBallCount = 0;  // ������ ���� ����
}

void Football_FX::Render()
{
	char string[100] = { 0, };
	int nLength, i;

	screen.ScreenClear();

	switch (g_GameState)
	{
	case INIT:
		if (g_nStage == 0)
			screen.InitScreen();
		break;
	case READY:
		screen.ReadyScreen(&g_nStage);
		break;
	case RUNNING:
		screen.BackScreen(&g_nStage, g_sStageInfo, &g_GameStartTime);
		screen.ScreenPrint(g_sGoalDae.nMoveX, g_sGoalDae.nMoveY, "��");
		nLength = g_sGoalDae.nLength * 2 + 1;

		for (i = 0; i < nLength; i++)
			screen.ScreenPrint(g_sGoalDae.nLineX[i], g_sGoalDae.nMoveY, "��");

		screen.ScreenPrint(g_sGoalDae.nLineX[nLength - 1] + 2, g_sGoalDae.nMoveY, "��");

		// Note: ȿ�� ���  	
		if (g_nIsGoal == 1)
		{
			screen.GoalMessage(10, 10);
		}

		// Note: 2 �÷��� Ŭ���� 
		if (g_sPlayer.nX < 2)  //  ���� Ŭ���� ó��
			screen.ScreenPrint(2, g_sPlayer.nMoveY, &g_strPlayer[(g_sPlayer.nX - 2)*-1]);	 // ��ǥ�� �迭 �ε��� 
		else if (g_sPlayer.nMoveX + (g_nLength - g_sPlayer.nCenterX + 1) > 43) // ������ Ŭ���� ó��
		{
			strncat(string, g_strPlayer, g_nLength - ((g_sPlayer.nMoveX + g_sPlayer.nCenterX + 1) - 43));
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, string);
		}
		else { // 1 �÷��� �̵�
			screen.ScreenPrint(g_sPlayer.nX, g_sPlayer.nMoveY, g_strPlayer);
		}

		screen.ScreenPrint(g_sBall.nMoveX, g_sBall.nMoveY, "��");
		break;
	case SUCCESS:
		screen.SuccessScreen();
		break;
	case FAILED:
		screen.FailureScreen();
		break;
	case RESULT:
		screen.ResultScreen(&g_nStage);
		break;
	}

	// Note: ������ �� 
	screen.ScreenFlipping();
}

void Football_FX::input()
{
	while (1)
	{
		if (_kbhit())
		{
			if (g_GameState == RESULT)
				break;

			nKey = _getch();

			switch (nKey)
			{
			case 'j':
				if (g_sPlayer.nMoveX > 2) // ���� �浹 ��� ��ǥ üũ
				{
					g_sPlayer.nMoveX--;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1;
					if (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2 || g_sPlayer.nMoveX + nRemain > 43)
						g_sPlayer.nMoveX--;

					g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
				}
				break;
			case 'l':
				if (g_sPlayer.nMoveX + 1 < 43) // ������ �浹 ��� ��ǥ üũ
				{
					g_sPlayer.nMoveX++;
					nRemain = g_nLength - g_sPlayer.nCenterX + 1;
					if (g_sPlayer.nMoveX + nRemain > 43 || (g_sPlayer.nMoveX - g_sPlayer.nCenterX < 2))
						g_sPlayer.nMoveX++;

					g_sPlayer.nX = g_sPlayer.nMoveX - g_sPlayer.nCenterX;
				}
				break;
			case 'k':
				if (g_sBall.nIsReady && g_GameState == RUNNING)
				{
					g_sBall.nMoveX = g_sPlayer.nMoveX;
					g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
					g_sBall.OldTime = clock();
					g_sBall.nIsReady = 0;
				}
				break;

			case 'y':
			case 'Y':
				if (g_GameState == FAILED)
				{
					Init();
					g_GameState = READY;
				}
				break;
			case 'n':
			case 'N':
				if (g_GameState == FAILED)
				{
					g_GameState = RESULT;
				}
				break;

			case ' ':
				if (g_GameState == INIT && g_nStage == 0)
				{
					g_GameState = READY;
					g_UpdateOldTime = clock();
				}
				break;
			}
		}

		Update();    // ������ ����
		Render();
	}

	Release();
	screen.ScreenRelease();
}

void Football_FX::Update()
{
	{
		clock_t CurTime = clock();
		int nLength = g_sGoalDae.nLength * 2 + 1;
		int i;


		switch (g_GameState)
		{
		case READY:
			if (CurTime - g_UpdateOldTime > 2000)
			{
				g_GameState = RUNNING;
				g_GameStartTime = CurTime;

			}
			break;
		case RUNNING:
			if (CurTime - g_GameStartTime > g_LimitTime)
			{
				g_GameState = STOP;
				return;
			}
			else {

				if (CurTime - g_sGoalDae.OldTime > g_sGoalDae.MoveTime)
				{
					g_sGoalDae.OldTime = CurTime;
					if (g_sGoalDae.nMoveX + g_sGoalDae.nDist >= 2 && ((g_sGoalDae.nLineX[nLength - 1] + 3) + g_sGoalDae.nDist) <= 43)
					{
						g_sGoalDae.nMoveX += g_sGoalDae.nDist;
						for (i = 0; i < nLength; i++)
						{
							g_sGoalDae.nLineX[i] = g_sGoalDae.nMoveX + 2 * (i + 1);
						}
					}
					else {
						g_sGoalDae.nDist = g_sGoalDae.nDist * -1;
					}
				}

				if (g_sBall.nIsReady == 0)
				{
					if ((CurTime - g_sBall.OldTime) > g_sBall.MoveTime)
					{
						if (g_sBall.nMoveY - 1 > 0)
						{
							g_sBall.nMoveY--;
							g_sBall.OldTime = CurTime;

							// ��� ���� �浹
							if (g_sBall.nMoveX >= g_sGoalDae.nLineX[0] && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 1)
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // �� �ʱ�ȭ
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
									g_nBallCount++;  // ������ ���� ����										

									if (g_nBallCount == g_nGoalBallCount)
									{
										g_GameState = STOP;
										g_nGoal = 1;
										return;
									}

									// ȿ�� ���
									if (g_nIsGoal == 0)
									{
										g_nIsGoal = 1;
										g_sEffect.StratTime = CurTime;
									}

								}
								// ��� �浹 
							}
							else if ((g_sBall.nMoveX >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[0] - 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[0] - 1) ||
								(g_sBall.nMoveX >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX <= g_sGoalDae.nLineX[nLength - 1] + 3) ||
								(g_sBall.nMoveX + 1 >= g_sGoalDae.nLineX[nLength - 1] + 2 && g_sBall.nMoveX + 1 <= g_sGoalDae.nLineX[nLength - 1] + 3))
							{
								if (g_sBall.nMoveY <= g_sGoalDae.nMoveY)
								{   // �� �ʱ�ȭ
									g_sBall.nIsReady = 1;
									g_sBall.nMoveX = g_sPlayer.nMoveX;
									g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
								}
							}
						}
						else { // �� �ʱ�ȭ
							g_sBall.nIsReady = 1;
							g_sBall.nMoveX = g_sPlayer.nMoveX;
							g_sBall.nMoveY = g_sPlayer.nMoveY - 1;
						}
					}
				}
				else {
					g_sBall.nMoveX = g_sPlayer.nMoveX;
				}

				// ȿ�� 
				if (g_nIsGoal == 1)
				{
					if (CurTime - g_sEffect.StratTime > g_sEffect.StayTime)
						g_nIsGoal = 0;
				}
			}
			break;
		case STOP:
			if (g_nGoal == 1)
			{
				g_GameState = SUCCESS;
				g_UpdateOldTime = CurTime;

			}
			else {
				g_GameState = FAILED;

			}
			break;
		case SUCCESS:
			if (CurTime - g_UpdateOldTime > 3000)
			{
				g_UpdateOldTime = CurTime;
				++g_nStage;
				Init();
				g_GameState = READY;

			}
			break;
		}
	}
}

void Football_FX::Release()
{
	int i;
}