//======================================
//	ターン制バトル メイン
//======================================
#include "Character.h"
#include "TurnBattle.h"
#include "CommandUI.h"
#include "Utility.h"  // InitRand(),GetKey()
#include <stdio.h>  // printf()
// 関数プロトタイプ
void game();

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
	Character boss;
	Character yaranaio;
	Character yaruo;
	TurnBattle btl;

	SetCharacter(&player,
		150,        // HP
		15,         // MP
		35,         // 攻撃力
		"ゆうしゃ", // 名前
		"(｀・ω・´)-|===>");        // アスキーアート
	SetCharacter(&boss,
		255,      // HP
		0,        // MP
		50,       // 攻撃力
		"まおう", // 名前
		"　　Ａ＠Ａ\n" // アスキーアート
		"ψ（▼皿▼）ψ"
	);
	/*SetCharacter(&zako,
		3,          // HP
		0,          // MP
		2,          // 攻撃力
		"スライム", // 名前
		"  ______\n"
		"／・Д・＼\n" // アスキーアート
		"～～～～～"
	);*/

	SetCharacter(&yaranaio,
		321,          // HP
		10,          // MP
		15,          // 攻撃力
		"やらない夫", // 名前
		"  ／￣￣￣＼ \n"
		"／   _ノ　  ＼ \n" // アスキーアート
		"|　 （ ●)（●） \n"
		"|　   （__人__）\n"
		" |　　 ｀ ⌒´ﾉ\n"
		"  |　　　 　 } \n"
		"  ヽ　　　  } \n"
		"   ヽ　　 ノ　\n"
		" 　/　　く　　\n"
		"　 |　　  ＼ \n"
		"   |　 |ヽ、二⌒)\n"
	);

	SetCharacter(&yaruo,
		321,          // HP
		5,          // MP
		10,          // 攻撃力
		"やる夫", // 名前
		"      ＿＿＿______\n"
	  "    ／⌒　　    ⌒＼\n"
	"  ／（ ●） 　（●）＼\n"
  "／ ::⌒（__人__）⌒:: ＼\n" 
  "|　　    |r┬--|　　　 |\n"
  "＼ 　　  `ー--´ 　  ／\n"
	);

	SetTurnBattle(&btl, &player, &boss, &yaranaio, &yaruo);
	StartTurnBattle(&btl);
	IntroTurnBattle(&btl);
	bool isEnd = false;
	Command cmd;
	while (true) {
		cmd = GetPlayerCommand(&btl);
		isEnd = ExecPlayerTurn(&btl, cmd);
		if (isEnd) {
			break;
		}
		cmd = GetEnemyCommand();
		isEnd = ExecEnemyTurn(&btl, cmd);
		if (isEnd) {
			break;
		}
		NextTurnBattle(&btl);
	}
}