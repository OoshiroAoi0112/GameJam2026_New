#include "Collision.h"
#include <math.h>

CapsuleCollision::CapsuleCollision() :
	is_blocking(false),
	object_type(eObjectType::none),
	hit_object_type(),
	radius(0.0f)
{
	point[0] = Vector2D(0.0f, 0.0f);
	point[1] = Vector2D(0.0f, 0.0f);
}

CapsuleCollision::~CapsuleCollision()
{

}

bool CapsuleCollision::IsCheckHitTarget(eObjectType hit_object) const
{
	// 適用するオブジェクトタイプなら true
	for (eObjectType type : hit_object_type)
	{
		// hitしたオブジェクトが当たり判定を適用するオブジェクトタイプなら true
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

// 円形同士の当たり判定を確認する処理
// 必要な情報①：円の中心点 (point)
// 必要な情報②：円の半径 (radius)
// 必要な情報③：お互いの距離の2乗 (len)
// 必要な情報④：当たり判定の条件（距離の2乗 <= 半径の和2乗）
bool IsCheckCollision(const CircleCollision& c1, const CircleCollision& c2)
{
	// ----- 円の中心点 (必要な情報①＆②) ----- //
	// point は円の中心座標を表すベクトル
	// c1.point - c2.point で、c2の中心点からc1の中心点へのベクトルを求める
	Vector2D diff = (c1.point - c2.point);

	// ----- 当たり判定の条件 (必要な情報③＆④) ----- //
	// ベクトルの長さを求める2乗の値を求める (必要な情報③)
	// ※処理を短くするため、平方根を求めないで距離の2乗を求める
	float len = diff.SqrLength();

	// 半径の和の長さを求める (必要な情報④)
	// ※処理を短くするため、平方根を使わず比較用に2乗にする
	float r = (c1.radius + c2.radius) * (c1.radius + c2.radius);

	// お互いの距離の2乗が、半径の和の2乗より小さい場合は、当たっていると判断する
	if (len <= r)
	{
		return true;
	}

	// すべての条件が成立していない場合は、当たっていない
	return false;
}

// カプセルと円の当たり判定を確認する処理
bool IsCheckCollision(const CapsuleCollision& c1, const CircleCollision& c2)
{
	// 仮の円を用意
	CircleCollision circle;
	// 最近傍点を求める
	circle.point = NearPointCheck(c1, c2.point);
	// 半径情報の設定
	circle.radius = c1.radius;

	// 最近傍点と円の当たり判定を確認する（円形同士の当たり判定）
	return IsCheckCollision(circle, c2);
}

// カプセル同士の当たり判定を確認する処理
bool IsCheckCollision(const CapsuleCollision& c1, const CapsuleCollision& c2)
{
	CircleCollision circle;

	// c2のっ始点を円形として扱って、
	// c1カプセルと当たっているか確認する
	circle.radius = c2.radius;
	circle.point = c2.point[0];
	if(IsCheckCollision(c1, circle))
	{
		return true;
	}

	// c2の終点を円形として扱って、
	// c1カプセルと当たっているか確認する
	circle.radius = c2.radius;
	circle.point = c2.point[1];
	if(IsCheckCollision(c1, circle))
	{
		return true;
	}

	// c1の始点を円形として扱って、
	// c2カプセルと当たっているか確認する
	circle.radius = c1.radius;
	circle.point = c1.point[0];
	if(IsCheckCollision(c2, circle))
	{
		return true;
	}

	// c1の終点を円形として扱って、
	// c2カプセルと当たっているか確認する
	circle.radius = c1.radius;
	circle.point = c1.point[1];
	if(IsCheckCollision(c2, circle))
	{
		return true;
	}

	// すべての条件が成立していない場合は、当たっていない
	return false;
}

/// 点とカプセルの線分の最近傍点を求める処理
Vector2D NearPointCheck(const CapsuleCollision& cap, const Vector2D& point)
{
	// 線分の向きを表すベクトル
	Vector2D line = cap.point[1] - cap.point[0];
	// 線分の始点から点にベクトルを計算する
	Vector2D a1 = point - cap.point[0];
	// 線分の終点から点にベクトルを計算する
	Vector2D a2 = point - cap.point[1];

	// 点とカプセルの線分の最近傍点を求める
	if(Vector2D::Dot(line, a1) <= 0.0f)
	{
		return cap.point[0];
	}
	if(Vector2D::Dot(line, a2) >= 0.0f)
	{
		return cap.point[1];
	}
	
	// 線分との最近傍点を求める
	Vector2D n = line.Normalize();
	float dot = Vector2D::Dot(n, a1);
	return (cap.point[0] + n * dot);
}

CircleCollision::CircleCollision() :
	point(0.0f), radius(0.0f)
{
}

CircleCollision::~CircleCollision()
{
}
