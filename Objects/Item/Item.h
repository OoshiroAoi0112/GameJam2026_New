#pragma once

#include "../GameObject.h"
#include "../../Utility/InputControl.h"
#include <vector>

class Item : public GameObject
{
private:
	InputControl* input;
private:
	std::vector<int> item_animation_move;   //アイテムのアニメーション
	
	const int item_animation_num[3] = { 0,1,2 };
	int item_animation_count;
	float item_animation_time;

	int item_image;

	float start_x;         // アイテムの初期位置

public:
	Item();
	virtual ~Item();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;
	void AnimeCount(float delta_second);
	// 当たり判定通知処理
	void OnHitCollision(const GameObject* hit_object) override;
	// 位置情報取得処理
	const Vector2D& GetLocation() const;
	// 位置情報設定処理
	void SetLocation(const Vector2D& pos) override;
	// 位置情報取得処理
	const Vector2D& GetVelocity() const;

};

