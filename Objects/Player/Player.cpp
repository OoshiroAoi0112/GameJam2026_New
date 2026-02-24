#include "Player.h"
#include "DxLib.h"

Player::Player() :
	input(nullptr),
	ingame_s(nullptr),
	gravity(0.0f),
	scroll(0.0f),
	prev_location(0.0f, 0.0f),
	has_ground_candidate(false),
	ground_top_y(0.0f),
	on_ground(false),
	state(nullptr),
	next_state(ePlayerState::NONE)
{
	
}

Player::~Player()
{

}

void Player::Initialize()
{
	input = InputControl::GetInstance();
	ResourceManager* rm = ResourceManager::GetInstance();

	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type = { eObjectType::enemy,
								  eObjectType::block,
								  eObjectType::item,
								  eObjectType::gool };
	
	collision.radius = D_OBJECT_SIZE / 2.0f;

	z_layer = 5;

	mobility = eMobilityType::Movable;
	state = PlayerStateFactory::Get(*this, ePlayerState::IDLE);
	next_state = ePlayerState::IDLE;

	velocity = Vector2D(0.0f, 0.0f);


	box_size = Vector2D(110.0f, 150.0f);
}

void Player::Update(float delta_second)
{
	state->Update(delta_second);

	// ----- 移動処理 ----- //
	Movement(delta_second);

	// ----- 状態遷移処理 ----- //
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get(*this, next_state);
		next_state = ePlayerState::NONE;
	}

	state->Animation(delta_second);

	// ----- カメラ視点の値 ----- //
	SetScroll(scroll);
}

void Player::Draw(const Vector2D& screen_offset) const
{
	DrawBox(location.x + 10, location.y + 10,
		location.x - 10, location.y - 10,
		GetColor(255, 255, 255), TRUE);

	DrawBox(location.x + box_size.x / 2, location.y + box_size.y / 2,
		location.x - box_size.x / 2, location.y - box_size.y / 2,
		GetColor(255, 0, 0), FALSE);
	
	DrawFormatString(400, 50, GetColor(255, 255, 255), "PlayerLocationY: %f", location.y);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "scroll = %f", scroll);
	
	// デバッグ：プレイヤーの状態を表示
	DrawFormatString(0, 150, GetColor(255, 255, 255), "Player State: %d", state->GetState());
	DrawFormatString(0, 170, GetColor(255, 255, 255), "Player State: %d", input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT));
}

void Player::Finalize()
{
}

void Player::Movement(float delta_second)
{
	// 前フレームの位置を保存
	prev_location = location;
	// 地面候補のリセット
	has_ground_candidate = false;
	// 地面候補の上端のY座標のリセット
	ground_top_y = 0.0f;
	// 地面にいるかどうかのリセット
	on_ground = false;

	// 左端制限
	if (location.x <= 20.0f)
	{
		location.x = 20.0f;
	}

	if (scroll <= -4540.0f)
	{
		// ステージ右端
		if (location.x >= 1270.0f)
		{
			location.x = 1270.0f;
		}
	}
	else
	{
		// 通常（中央固定）
		if (velocity.x > 0 && location.x >= 1280.0f / 2)
		{
			location.x = 1280.0f / 2;
		}
	}

	// 移動量上限
	if (velocity.x > D_PLAYER_MAX_SPEED)
	{
		velocity.x = D_PLAYER_MAX_SPEED;
	}
	else if (velocity.x < -D_PLAYER_MAX_SPEED)
	{
		velocity.x = -D_PLAYER_MAX_SPEED;
	}

	// ----- 位置の更新 ----- //
	// 重力の適用
	velocity.y += GRAVITY * delta_second;

	// y軸の移動
	location.y += velocity.y * delta_second;

	// y軸の地面との当たり判定

	// x軸の移動
	location.x += velocity.x * delta_second;

	// x軸の当たり判定

	if (location.y >= 600.0f)
	{
		location.y = 600.0f;
		velocity.y = 0.0f;
		on_ground = true;
	}
}

void Player::SetNextState(ePlayerState state)
{
	this->next_state = state;
}

void Player::OnHitCollision(GameObject* hit_object)
{
	if(hit_object->GetCollision().object_type == eObjectType::block)
	{
		// --- ヒットしたブロックの上端のy座標を求める --- //
		// ブロックの高さの半分を求める
		const float blockHalfY = hit_object->GetBoxSize().y / 2.0f;
		// ブロックの上端のy座標を求める
		const float blockTop = hit_object->GetLocation().y - blockHalfY;

		// 床候補の上端のy座標を保存
		if (!has_ground_candidate || blockTop < ground_top_y && velocity.y > 0.0f)
		{
			// 床候補の上端のy座標を保存
			ground_top_y = blockTop;
			// 地面候補があるフラグを立てる
			has_ground_candidate = true;
		}
	}
	else if(hit_object->GetCollision().IsCheckHitTarget(eObjectType::enemy))
	{
		// 敵に当たったときの処理
	}
	else if(hit_object->GetCollision().IsCheckHitTarget(eObjectType::item))
	{
		// アイテムに当たったときの処理
	}
	else if(hit_object->GetCollision().IsCheckHitTarget(eObjectType::gool))
	{
		// ゴールに当たったときの処理
	}
}

void Player::PostCollision(float delta_second)
{
	// 地面候補がない場合は、地面との当たり判定を行わない
	if (!has_ground_candidate) return;

	// ----- 地面との当たり判定 ----- //
	// プレイヤーの下端のy座標を求める
	const float playerHalfY = box_size.y / 2.0f;
	// 前フレームのプレイヤーの下端のy座標
	const float prevBottom = prev_location.y + playerHalfY;
	// 今フレームのプレイヤーの下端のy座標
	const float nowBottom = location.y + playerHalfY;
	// ブロックの上端のy座標
	const float blockTop = ground_top_y;

	// 上からブロックに当たったときに突き抜けた分押し戻す
	if (velocity.y > 0.0f && prevBottom <= blockTop && nowBottom > blockTop)
	{
		location.y = blockTop - playerHalfY;
		velocity.y = 0.0f;
		on_ground = true;
	}
}

Vector2D& Player::GetLocation()
{
	return this->location;
}

const Vector2D& Player::GetVelocity() const
{
	return velocity;
}
// カメラ視点の値を受け取る
void Player::SetScroll(float scrollX)
{
	scroll = scrollX;
}

