//======================================
//	ターン制バトル
//======================================
#include "TurnBattle.h"
#include "Utility.h"
#include <stdio.h>  // printf()

// 関数プロトタイプ
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense);

// ターンバトル設定
void SetTurnBattle(TurnBattle* btl, Character* player, Character* enemy , Character* yaranaio, Character* yaruo)
{
	btl->player = player;
	btl->enemy = enemy;
	btl->yaruo = yaruo;
	//btl->yaranaio = yaranaio;
}
// イントロ「～が現れた!!」表示
void IntroTurnBattle(TurnBattle* btl)
{
	DrawBattleScreen(btl);
	// ★ここで「(敵の名前)が　あらわれた!!」を表示してください
	//printf("%sが　あらわれた!!\n", btl->enemy->name);
	printf("%sが　あらわれた!!\n", btl->yaruo->name);
	//printf("%sが　あらわれた!!\n", btl->yaranaio->name);
	WaitKey();
}
// バトル開始
void StartTurnBattle(TurnBattle* btl)
{
	btl->turn = 1;
	StartCharacter(btl->player);
	//StartCharacter(btl->enemy);
	StartCharacter(btl->yaruo);
	//StartCharacter(btl->yaranaio);
}
// バトル画面を描画
void DrawBattleScreen(TurnBattle* btl)
{
	ClearScreen();
	IndicatePlayer(btl->player);
	putchar('\n');
	//IndicateEnemy(btl->enemy);
	//putchar('\n');
	IndicateEnemy(btl->yaruo);
	putchar('\n');
	//IndicateEnemy(btl->yaranaio);
	//putchar('\n');
}
// プレーヤのターン実行
/*bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->enemy);
	if (IsDeadCharacter(btl->enemy)) {
		SetEraseAa(btl->enemy);
		DrawBattleScreen(btl);
		// ★ここで「(敵の名前)を　たおした!」を表示してください
		printf("%sをたおした！\n", btl->enemy->name);
		WaitKey();
		return true;
	}
	return IsEscapeCharacter(btl->player);
}*/
bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->yaruo);
	if (IsDeadCharacter(btl->yaruo)) {
		SetEraseAa(btl->yaruo);
		DrawBattleScreen(btl);
		// ★ここで「(敵の名前)を　たおした!」を表示してください
		printf("%sをたおした！\n", btl->yaruo->name);
		WaitKey();
		return true;
	}

	/*execCommand(btl, cmd, btl->player, btl->yaranaio);
	if (IsDeadCharacter(btl->yaranaio)) {
		SetEraseAa(btl->yaranaio);
		DrawBattleScreen(btl);
		// ★ここで「(敵の名前)を　たおした!」を表示してください
		printf("%sをたおした！\n", btl->yaranaio->name);
		WaitKey();
		return true;
	}*/
	return IsEscapeCharacter(btl->player);
}
// 敵のターン実行
/*bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->enemy, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// ★ここで「"あなたは　しにました」を表示してください
		printf("あなたは　しにました\n");
		WaitKey();
		return true;
	}
	return false;
}*/

bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->yaruo, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// ★ここで「"あなたは　しにました」を表示してください
		printf("あなたは　しにました\n");
		WaitKey();
		return true;
	}
	/*execCommand(btl, cmd, btl->yaranaio, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		// ★ここで「"あなたは　しにました」を表示してください
		printf("あなたは　しにました\n");
		WaitKey();
		return true;
	}*/
	return false;
}
// コマンド実行(offense:攻撃キャラ defense:防御キャラ)
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense)
{
	int dmg;
	switch (cmd) {
	case COMMAND_FIGHT:
		DrawBattleScreen(btl);
		// ★ここで「(攻撃側の名前)の　こうげき!」を表示してください
		printf("%sのこうげき！\n", offense->name);
		WaitKey();

		dmg = CalcDamage(offense);
		DamageCharacter(defense, dmg);
		DrawBattleScreen(btl);
		// ★ここで「(防御側の名前)に (ダメージ値)の　ダメージ!」を表示してください
		printf("%sに%dのダメージ！\n", defense->name, dmg);
		WaitKey();

		break;
	case COMMAND_SPELL:
		if (CanSpellCharacter(offense) == false) {
			DrawBattleScreen(btl);
			// ★ここで「ＭＰが　たりない!」を表示してください
			printf("MPがたりない！\n");
			WaitKey();
			break;
		}
		UseSpellCharacter(offense);
		DrawBattleScreen(btl);
		// ★ここで「(攻撃側の名前)は　ヒールを　となえた!」を表示してください
		printf("%sはヒールをとなえた！\n", offense->name);
		WaitKey();

		RecoverCharacter(offense);
		DrawBattleScreen(btl);
		// ★ここで「(攻撃側の名前)のきずが　かいふくした!」を表示してください
		printf("%sのきずが　かいふくした！\n", offense->name);
		WaitKey();
		break;

	case COMMAND_ESCAPE:
		DrawBattleScreen(btl);
		// ★ここで「(攻撃側の名前)は　にげだした!」を表示してください
		printf("%sは　にげだした！\n", offense->name);
		WaitKey();
		SetEscapeCharacter(offense);
		break;
	}
}
// 次のターンへ
void NextTurnBattle(TurnBattle* btl)
{
	btl->turn++;
}