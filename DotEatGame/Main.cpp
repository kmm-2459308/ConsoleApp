//======================================
//	ドットイートゲーム　メイン
//======================================
#include "StageMoveCharacter.h"
#include "Stage.h"
#include "Character.h"
#include "Utility.h"
#include "IntervalTimer.h"
#include <stdio.h>  // printf(),putchar()
// 関数プロトタイプ
void game();
void DrawGameOver();
void DrawCongratulations();

int main()
{
	InitRand();

	int c;
	do {
		game();
		printf("もう一度(y/n)?");
		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
				break;
			}
		}
	} while (c == 'y');
	return 0;
}

void game()
{
	Character player;
	Character monster1;
	Character monster2;
	Character monster3;
	Character monster4;
	Stage stage;

	InitCharacter(&player, CHARA_PLAYER, { 9, 13 });
	InitCharacter(&monster1, CHARA_RANDOM, { 1, 1 });
	InitCharacter(&monster2, CHARA_CHASE, { 17, 1 });
	InitCharacter(&monster3, CHARA_AMBUSH, { 1, 17 });
	InitCharacter(&monster4, CHARA_SIEGE, { 17, 17 });

	InitializeStage(&stage, &player);
	RegistMonster(&stage, &monster1);
	RegistMonster(&stage, &monster2);
	RegistMonster(&stage, &monster3);
	RegistMonster(&stage, &monster4);

	DrawMaze(&stage);
	WaitKey();

	IntervalTimer timer;
	StartTimer(&timer, 2); // FPS=2
	while (true) {
		if (IsInterval(&timer)) {
			MoveMonsters(&stage);
			DrawMaze(&stage);
			if (IsGameOver(&stage)) {
				DrawGameOver();
				WaitKey();
				break;
			}
		}

		if (KeyAvailable()) {
			MovePlayer(&stage);
			DrawMaze(&stage);
			if (IsComplete(&stage)) {
				DrawCongratulations();
				WaitKey();
				break;
			}
		}
	}
	FinalizeStage(&stage);
}
// 「Game Over」表示
void DrawGameOver()
{
	ClearScreen();
	//
	// ★ここをコーディングしてください。
	// Maze表示領域の中央に「ＧＡＭＥ　ＯＶＥＲ」を表示します。
	//
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		if (i == MAZE_HEIGHT / 2)
		{
			printf("　　　　　G A M E　 O V E R\n");
		}
		else
		{
			putchar('\n');
		}
	}
}
// 「Congratulations」表示
void DrawCongratulations()
{
	ClearScreen();
	//
	// ★ここをコーディングしてください。
	// Maze表示領域の中央に「ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ！」を表示します。
	//
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		if (i == MAZE_HEIGHT / 2)
		{
			printf("　　C O N G R A T U L A T I O N S\n");
		}
		else
		{
			putchar('\n');
		}
	}
}