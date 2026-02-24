#pragma once

#include "../GameObject.h"
#include <vector>

// ブロックのタイプ
enum class BlockType
{
	Snow,  // 雪
	Soil   // 土
};

class Block : public GameObject
{
private:

	int image;
	BlockType type;
	float start_x;         // 初期位置

public:
	Block();
	 ~Block();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	// 当たり判定通知処理
	void OnHitCollision(GameObject* hit_object) override;
	//位置情報取得処理
	const Vector2D& GetLocation() const;
	//位置情報設定処理
	void SetLocation(const Vector2D& pos) override;
	// ブロックのタイプを設定する
	void SetBlockType(BlockType t);
};
