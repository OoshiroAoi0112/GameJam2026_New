#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE (32.0f) // オブジェクトの大きさ
#define GRAVITY (1000.0f) // 重力

enum eMobilityType
{
	Stationary,	// 静止
	Movable,		// 移動
};

class GameObject
{
public:
	class SceneBase* owner_scene; //所有するシーン情報
	Vector2D location;			// 座標
	Vector2D velocity;          // 移動量	
	Vector2D box_size;			// 当たり判定の大きさ
	CapsuleCollision collision; // 当たり判定
	eMobilityType mobility;	    // 移動タイプ

	int z_layer;				// 描画の優先順位
	
	int graphic_images;			// 描画する画像
	int flip_flag;				// 画像反転フラグ

	bool delete_flag;			// 削除フラグ


public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Initialize();
	virtual void Update(float delta_second);
	virtual void Draw(const Vector2D& screen_offset) const;
	virtual void Finalize();

public:
	// 当たり判定通知処理
	virtual void OnHitCollision(const GameObject* hit_object);

	// 座標を取得
	virtual Vector2D& GetLocation();
	// 当たり判定を取得
	const CapsuleCollision& GetCollision() const;
	// 描画の優先順位を取得
	const int GetZLayer() const;
	// 可動性を取得
	const eMobilityType GetMobility() const;

	virtual void SetLocation(const Vector2D& pos)
	{
		location = pos;
	}

	// 所有シーン情報設定
	void SetOwnerScene(class SceneBase* scene);

	// 削除フラグを取得
	const bool GetDeleteFlag() const;

};