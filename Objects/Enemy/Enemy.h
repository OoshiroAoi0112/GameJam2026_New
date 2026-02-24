#pragma once

#include "../GameObject.h"
#include <vector>

enum EnemyState
{
	WALK,
	DIE,
};

class Enemy : public GameObject
{
private:
	std::vector<int> move_animation;   //移動のアニメーション

	//アニメーション用
	const int animation_num[3] = { 0,1, 2 };
	int animation_count;
	float animation_time;

	int image;  
	int walk_image;  //エネミーの画像(WALK)
	int die_image;  //エネミーの画像(DIE)

	float speed;           // 移動速度
	float move_range;      // 移動範囲（片側）
	float start_x;         // 初期位置
	int direction = -1;         // 移動方向（1 or -1）
	int angle;  // エネミーの角度	
	int hp;  // エネミーの体力

public:
	EnemyState enemy_state;

	Enemy();

	virtual ~Enemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void AnimeCount(float delta_second);
	// 当たり判定通知処理
	void OnHitCollision(GameObject* hit_object) override;
	//位置情報取得処理
	const Vector2D& GetLocation() const;
	//位置情報設定処理
	void SetLocation(const Vector2D& pos) override;
	//位置情報取得処理
	const Vector2D& GetVelocity() const;

};
