//======================================
//	コマンドUI
//======================================
// ★ここにインクルードガード(開始)を記入してください。
#ifndef __COMMAND_UI_H
#define __COMMAND_UI_H
#include "Command.h"
#include "TurnBattle.h"

// プレーヤのコマンド取得
Command GetPlayerCommand(TurnBattle* btl);
// 敵のコマンド取得
Command GetEnemyCommand();

// ★ここにインクルードガード(終了)を記入してください。
#endif