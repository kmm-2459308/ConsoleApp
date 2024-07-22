//======================================
//      落ち物バズル 落ちブロック
//======================================
// ★ここにインクルードガード(開始)を記入してください
//
#ifndef __FALL_BLOCK_H
#define __FALL_BLOCK_H
#include "BlockShape.h"

typedef struct {
	int x, y;         // Shape左上の座標
	BlockShape shape; // 形状
} FallBlock;

// 落ちブロックの移動
void MoveFallBlock(FallBlock* fallBlock, int ofsx, int ofsy);
// 落ちブロックの回転
void RotateFallBlock(FallBlock* fallBlock);
// ランダムな落ちブロックをセット
void SetRandomFallBlock(FallBlock* fallBlock, int x, int y);
// 落ちブロックをプリント
void PrintFallBlock(FallBlock* fallBlock);

// ★ここにインクルードガード(終了)を記入してください
#endif // !__FALL_BLOCK_H