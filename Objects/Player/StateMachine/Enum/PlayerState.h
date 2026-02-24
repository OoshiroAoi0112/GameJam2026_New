#pragma once

enum class ePlayerState : unsigned char
{
	IDLE = 0,  // 何もしてない
	ROLL,    // 転がる（ローリング）
	JUMP,    // ジャンプ
	CLEAR,    // ゴール
	DIE,     // 死
	NONE,    // 状態なし
};