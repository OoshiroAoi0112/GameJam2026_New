#include "Player.h"
#include "DxLib.h"
#include "../../Utility/GameDataManager.h"

Player::Player() :
	input(nullptr),
	ingame_s(nullptr),
	gravity(0.0f),
	scroll(0.0f),
	prev_location(0.0f, 0.0f),
	has_ground_candidate(false),
	ground_top_y(0.0f),
	has_wall_candidate_left(false),
	wall_right_x(0.0f),
	has_wall_candidate_right(false),
	wall_left_x(0.0f),
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


	box_size = Vector2D(D_OBJECT_SIZE * 2, D_OBJECT_SIZE * 3);
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
	// プレイヤーサイズ
	const int width = 32;
	const int height = 64;

	// 画面に描画する座標（←ここが超重要）
	int drawX = static_cast<int>(location.x + screen_offset.x);
	int drawY = static_cast<int>(location.y + screen_offset.y);


	state->Draw(screen_offset);

}

void Player::Finalize()
{
}

void Player::Movement(float delta_second)
{
	prev_location = location;         // 前フレームの位置を保存
	has_ground_candidate = false;     // 地面候補のリセット
	has_wall_candidate_left = false;  // 左の壁候補のリセット
	has_wall_candidate_right = false; // 右の壁候補のリセット
	ground_top_y = 0.0f;              // 地面候補の上端のY座標のリセット
	wall_left_x = 0.0f;               // 右の壁候補の左端のX座標のリセット
	wall_right_x = 0.0f;              // 左の壁候補の右端のX座標のリセット
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

	if (location.y >= 640.0f)
	{
		location.y = 640.0f;
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
		// ----- 上方向の当たり判定 ----- //
		// --- ヒットしたブロックの上端のy座標を求める --- //
		// ブロックの高さの半分を求める
		const float blockHalfY = hit_object->GetBoxSize().y / 2.0f;
		// ブロックの上端のy座標を求める
		const float blockTop = hit_object->GetLocation().y - blockHalfY;

		// 床候補の上端のy座標を保存
		if (velocity.y > 0.0f && (!has_ground_candidate || blockTop > ground_top_y))
		{
			// 床候補の上端のy座標を保存
			ground_top_y = blockTop;
			// 地面候補があるフラグを立てる
			has_ground_candidate = true;
		}

		// 誤差許容値（プレイヤーとブロックがほぼ同じ位置にある場合の判定のため）
		const float eps = 5.0f;

		// ブロックの縦範囲（top/bottom）
		const float blockBottom = hit_object->GetLocation().y + blockHalfY;

		// プレイヤーの縦範囲（壁判定用に上下を縮める）
		const float playerHalfY = box_size.y / 2.0f;
		const float nowTopE = (location.y - playerHalfY) + eps;
		const float nowBottomE = (location.y + playerHalfY) - eps;

		// 壁として扱うかどうかの判定
		const bool yOverlapForWall = (nowTopE < blockBottom) && (nowBottomE > blockTop);

		// ----- x方向の当たり判定 ----- //
		// --- 左の壁に当たったときは壁の右端のx座標を求める --- //
		// ブロックの幅の半分を求める
		const float blockHalfX_left = hit_object->GetBoxSize().x / 2.0f;
		// ブロックの右端のx座標を求める
		const float blockRight = hit_object->GetLocation().x + blockHalfX_left;
		// プレイヤーの元左端のx座標を求める
		const float prevLeft = prev_location.x - box_size.x / 2.0f;
		// プレイヤーの左端のx座標を求める
		const float nowLeft = location.x - box_size.x / 2.0f;

		// 壁候補の右端のx座標を保存
		if (yOverlapForWall &&
			velocity.x < 0.0f &&
			prevLeft >= blockRight && nowLeft < blockRight &&
			(!has_wall_candidate_left || blockRight > wall_right_x))
		{
			// 左の壁候補の右端のx座標を保存
			wall_right_x = blockRight;
			// 左の壁候補があるフラグを立てる
			has_wall_candidate_left = true;
		}

		// --- 右の壁に当たったときは壁の左端のx座標を求める --- //
		// ブロックの幅の半分を求める
		const float blockHalfX_right = hit_object->GetBoxSize().x / 2.0f;
		// ブロックの左端のx座標を求める
		const float blockLeft = hit_object->GetLocation().x - blockHalfX_right;
		// プレイヤーの元右端のx座標を求める
		const float prevRight = prev_location.x + box_size.x / 2.0f;
		// プレイヤーの右端のx座標を求める
		const float nowRight = location.x + box_size.x / 2.0f;

		// 壁候補の左端のx座標を保存
		if (yOverlapForWall &&
			velocity.x > 0.0f &&
			prevRight <= blockLeft && nowRight > blockLeft &&
			(!has_wall_candidate_right || blockLeft < wall_left_x))
		{
			// 右の壁候補の左端のx座標を保存
			wall_left_x = blockLeft;
			// 右の壁候補があるフラグを立てる
			has_wall_candidate_right = true;
		}
	}
	else if(hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		// 敵に当たったときの処理
		owner_scene->DestroyObject(hit_object);

	}
	else if(hit_object->GetCollision().object_type == eObjectType::item)
	{
		// アイテムに当たったときの処理
		owner_scene->DestroyObject(hit_object);
		auto& mg = GameDataManager::GetInstance();
		int score = mg.GetScore();
		score += 100;
		mg.SetScore(score);
	}
	else if(hit_object->GetCollision().object_type == eObjectType::gool)
	{
		// ゴールに当たったときの処理
	}
}

void Player::PostCollision(float delta_second)
{
	// ----- 地面との当たり判定 ----- //
	// --- 上から踏んだ時だけ --- //
	if (has_ground_candidate)
	{
		// ----- 地面との当たり判定 ----- //
		// --- 必要な値を求める --- //
		// - プレイヤーの下端のy座標を求める - //
		const float playerHalfY = box_size.y / 2.0f;
		// 前フレームのプレイヤーの下端のy座標
		const float prevBottom = prev_location.y + playerHalfY;
		// 今フレームのプレイヤーの下端のy座標
		const float nowBottom = location.y + playerHalfY;
		// ブロックの上端のy座標
		const float blockTop = ground_top_y;

		if(velocity.y > 0.0f && prevBottom <= blockTop && nowBottom > blockTop)
		{
			location.y = blockTop - playerHalfY;
			velocity.y = 0.0f;
			on_ground = true;
		}
	}
	// ----- x方向の当たり判定（左） ----- //
	// --- 左から当たったときは壁の右端を見る --- //
	if (has_wall_candidate_left)
	{
		// ----- x方向の当たり判定（左） ----- //
		// --- 必要な値を求める --- //
		// - プレイヤーの左端のx座標を求める - //
		const float playerHalfX = box_size.x / 2.0f;
		// 前フレームのプレイヤーの左端のx座標
		const float prevLeft = prev_location.x - playerHalfX;
		// 今フレームのプレイヤーの左端のx座標
		const float nowLeft = location.x - playerHalfX;
		// ブロックの右端のx座標
		const float blockRight = wall_right_x;

		if (velocity.x < 0.0f && prevLeft >= blockRight && nowLeft < blockRight)
		{
			location.x = blockRight + playerHalfX;
			velocity.x = 0.0f;
		}
	}
	// ----- x方向の当たり判定（右） ----- //
	// --- 右から当たったときは壁の左端を見る --- //
	if (has_wall_candidate_right)
	{
		// ----- x方向の当たり判定（右） ----- //
		// --- 必要な値を求める --- //
		// - プレイヤーの右端のx座標を求める - //
		const float playerHalfX = box_size.x / 2.0f;
		// 前フレームのプレイヤーの右端のx座標
		const float prevRight = prev_location.x + playerHalfX;
		// 今フレームのプレイヤーの右端のx座標
		const float nowRight = location.x + playerHalfX;
		// ブロックの左端のx座標
		const float blockLeft = wall_left_x;
		if (velocity.x > 0.0f && prevRight <= blockLeft && nowRight > blockLeft)
		{
			location.x = blockLeft - playerHalfX;
			velocity.x = 0.0f;
		}
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

