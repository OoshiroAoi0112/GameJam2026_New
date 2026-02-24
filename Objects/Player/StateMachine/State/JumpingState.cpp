#include "JumpingState.h"

#include "DxLib.h"
#include "../../../../Utility/InputControl.h"
#include "../../Player.h"
#include "../../../../Utility/ResourceManager.h"
#include "../../../../Utility/Vector2D.h"

//#endif // !


JumpingState::JumpingState(class Player* p) :
	jumping_animation(),
	PlayerStateBase(p),
	jumping_animation_count(0),
	jumping_animation_time(0.0f),
	input(nullptr)
{
	start_x = 0;
	ResourceManager* rm = ResourceManager::GetInstance();
	jumping_animation = rm->GetImages("Resource/image/Player/Normal/Jump/Normal_Jump.png", 1, 1, 1, 276, 452);
	jumping_image = jumping_animation[0];
}

JumpingState::~JumpingState()
{
}

void JumpingState::Initialize()
{
	input = InputControl::GetInstance();

	player->velocity.y = -D_JUMP_POWER;
	player->on_ground = false;
}

void JumpingState::Update(float delta_second)
{
	if (player->on_ground == true)
	{
		player->SetNextState(ePlayerState::IDLE);
	}

	jump_angle += 9.0f * delta_second; // ジャンプ中の回転角度を更新
}

void JumpingState::Draw(const Vector2D& screen_offset) const
{
	//座標情報を整数値に変換
	int x = 0, y = 0;
	player->GetLocation().ToInt(&x, &y);

	DrawRotaGraph(x + static_cast<int>(screen_offset.x), y + static_cast<int>(screen_offset.y), 0.06, jump_angle, jumping_image, TRUE);
}

void JumpingState::Finalize()
{
}

void JumpingState::Animation(float delta_second)
{
	jumping_animation_time += delta_second;
	if (jumping_animation_time >= 0.5f)
	{
		jumping_animation_time = 0.0f;
		jumping_animation_count++;
		// 修正: jumping_animation.size() を正しく呼び出す
		if (jumping_animation_count >= static_cast<int>(jumping_animation.size()))
		{
			jumping_animation_count = 0;
		}
		jumping_image = jumping_animation[jumping_animation_count];
	}
}

ePlayerState JumpingState::GetState() const
{
	return ePlayerState::JUMP;
}
