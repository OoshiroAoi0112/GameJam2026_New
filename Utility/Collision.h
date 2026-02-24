#pragma once

#include "Vector2D.h"
#include <vector>

// オブジェクトタイプ
enum class eObjectType : unsigned char
{
	none,   // 当たり判定を持たない
	player, // プレイヤー
	enemy,  // 敵
	block,  // すり抜けの無いブロック
	item,   // 得点アイテム、装備（仮）アイテム
	gool    // ゴール地点
};

// 当たり判定クラス
class CapsuleCollision
{
public:
	bool                     is_blocking;     // すり抜けフラグ
	eObjectType              object_type;     // 自身のオブジェクトタイプ
	std::vector<eObjectType> hit_object_type; // 当たり判定を適用するオブジェクトタイプ
	float                 radius;          // 円の半径(横半径と縦半径)
	Vector2D                 point[2];        // 視点と終点

public:
	// コンストラクタ
	CapsuleCollision();
	// デストラクタ
	~CapsuleCollision();

	bool IsCheckHitTarget(eObjectType hit_object) const;
};

// 円形状クラス
class CircleCollision
{
public:
	Vector2D point;
	float radius;

public:
	CircleCollision();
	~CircleCollision();
};

// 当たり判定確認用
// 当たっていいれば true (c1 = 形状の情報１, c2 = 形状の情報２)
bool IsCheckCollision(const CircleCollision& c1, const CircleCollision& c2);
bool IsCheckCollision(const CapsuleCollision& c1, const CircleCollision& c2);
bool IsCheckCollision(const CapsuleCollision& c1, const CapsuleCollision& c2);

// 点とカプセルの線分の最近傍点を求める処理
// 最近傍点 (cap = カプセル情報, point = 円の中心点)
Vector2D NearPointCheck(const CapsuleCollision& cap, const Vector2D& point);