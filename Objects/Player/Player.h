#pragma once

#include "../GameObject.h"
#include "../../Utility/InputControl.h"
#include "../../Scenes/InGameScene.h"
#include "StateMachine/PlayerStateBase.h"
#include "StateMachine/Enum/PlayerState.h"
#include "../../Utility/ResourceManager.h"
#include "StateMachine/Factory/PlayerStateFactory.h"
#include <vector>

#define D_PLAYER_SPEED (400.0f) // プレイヤーの移動速度
#define D_PLAYER_MAX_SPEED (400.0f) // プレイヤーの最大移動速度
#define D_JUMP_POWER (500.0f) // ジャンプの強さ

class Player : public GameObject
{
public:
	bool on_ground;    // 地面にいるかどうか

private:
	InputControl* input;  // 入力情報
	InGameScene* ingame_s;  //ゲームメインの情報
	float gravity;        // 重力
	float scroll;  //スクロール値
	
	class PlayerStateBase* state;
	ePlayerState next_state;  // 次の状態
	

	// 画像配列 ： 今後、プレイヤーの状態に応じて画像を切り替えるために使用
	
	std::vector<int> player_normal_img;  // 通常時
	std::vector<int> player_rolling_img; // ローリング状態
	std::vector<int> player_knight_img;  // 騎士状態

public:
	// コンストラクタ
	Player();
	// デストラクタ
	virtual ~Player();

	// 初期化
	void Initialize() override;
	// 更新
	void Update(float delta_second) override;
	// 描画
	void Draw(const Vector2D& screen_offset) const override;
	// 終了処理
	void Finalize() override;
	// 移動処理
	void Movement(float delta_second);
	// アニメーション処理
	virtual void Animation(float delta_second);
	// 状態遷移処理
	void SetNextState(ePlayerState state);

	// 当たり判定通知処理
	void OnHitCollision(const GameObject* hit_object) override;

	//位置情報取得処理
	Vector2D& GetLocation() override;
	//位置情報取得処理
	const Vector2D& GetVelocity() const;
	// カメラ視点の値を受け取る
	void SetScroll(float scrollX);
};